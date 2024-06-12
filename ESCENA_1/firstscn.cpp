#include "firstscn.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QDebug>
#include <QLCDNumber>
#include <QTimer>

firstScn::firstScn(MainWindow *parent)
    : QGraphicsScene(0, 0, 1350, 750), mainWindow(parent), remainingClicks(50), avionActual(nullptr), misilActual(nullptr), valHumos(false)
{
    resetScene();
}

firstScn::~firstScn() {
    // Limpia todos los elementos de la escena
    for (auto item : items()) {
        removeItem(item);
        delete item;
    }
}

void firstScn::resetScene() {
    clear();
    remainingClicks = 50;
    avionActual = nullptr;
    misilActual = nullptr;
    valHumos = false;

    // Lista de detalles para los objetos Buque (posición, escala y ruta de la imagen)
    QList<BuqueDetalles> detallesBuques = {
        {QPointF(66, 3), 0.39, ":/buque_vertical.png", 6},
        {QPointF(378, 160), 0.32, ":/buque_horizontal.png", 5},
        {QPointF(1191, 153), 0.39, ":/buque_vertical.png", 6},
        {QPointF(304, 379), 0.39, ":/buque_horizontal.png", 6},
        {QPointF(891, 228), 0.39, ":/buque_vertical.png", 6},
        {QPointF(314, 527), 0.19, ":/buque_vertical.png", 3},
        {QPointF(904, 23), 0.19, ":/buque_horizontal.png", 3}
    };

    // Crear y agregar múltiples objetos Buque (atrás del telón)
    for (const auto &detalles : detallesBuques) {
        Buque *buque = new Buque(detalles.rutaImagen); // Usar la ruta de la imagen
        buque->setPos(detalles.posicion);
        buque->setScale(detalles.escala);
        buque->setZValue(-1); // Colocar buques debajo del telón, el Zvalue sirve para establecer jerarquía de aparición
        addItem(buque);
        buques.append({buque, detalles});
    }

    // Añadir el telón
    QPixmap telonPixmap(":/fondo_azul.jpg");
    telonPixmap = telonPixmap.scaled(1350, 750, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    telon = new QGraphicsPixmapItem(telonPixmap);
    telon->setZValue(0); // Establecer ZValue del telón
    addItem(telon);

    // Añadir la cuadrícula sobre el telón
    for (int i = 0; i < 10; i = i + 1) { // Los cuadrados en y
        for (int j = 0; j < 18; j = j + 1) { // Los cuadrados en x
            QGraphicsRectItem *rect = addRect(j * 75, i * 75, 75, 75, QPen(Qt::white));
            rect->setZValue(1); // Colocar la cuadrícula sobre el telón
            cuadricula.append(rect);
        }
    }

    if (mainWindow) {
        QLCDNumber *balas = mainWindow->findChild<QLCDNumber*>("balas");
        if (balas) {
            balas->display(50);
        }
    }

    if (mainWindow) {
        QLCDNumber *barcos = mainWindow->findChild<QLCDNumber *>("barcos");
        if (barcos) {
            barcos->display(countRemainingBuques()); // Mostrar la cantidad de buques restantes
        }
    }

    connect(this, &firstScn::comprobarImpacto, this, &firstScn::comprobarImpacto);
}

void firstScn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Mouse press event at:" << event->scenePos();

    if (!avionActual) {
        clickPos = event->scenePos();
        qDebug() << "Click position:" << clickPos;

        // Verificar si el recuadro ya está revelado
        for (QGraphicsRectItem *rect : cuadricula) {
            if (rect->contains(rect->mapFromScene(clickPos))) {
                if (rect->brush().color() == QColor("#004C84") || rect->brush().color() == Qt::red) {
                    qDebug() << "Recuadro ya revelado, no se puede hacer clic nuevamente.";
                    return;
                }
            }
        }

        // Verificar si se han agotado los clics válidos
        if (remainingClicks <= 0) {
            return;
        }
        if (countRemainingBuques() <= 0) {
            emit gameWon(); // Emitir la señal
            return;
        }

        if (!avionActual && !misilActual) {
            misilActual = new Misil(":/misil.png");
            misilActual->setXyYPosition(clickPos.x(), clickPos.y());

            avionActual = new Aviones(":/avion.png");
            qreal avionY = (static_cast<int>(clickPos.y()) / 75) * 75 + 5;
            avionActual->setYPosition(avionY-90); // Ajustar la posición Y del avión
            avionActual->setZValue(5);
            addItem(avionActual);
            qDebug() << "Avion añadido en la posición:" << avionActual->pos();

            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [this]() {
                if (avionActual) {
                    comprobarImpacto(avionActual->x());
                }
            });
            timer->start(50); // Comprueba el impacto cada 50ms

            connect(avionActual, &Aviones::animacionTerminada, this, [this, timer] {
                qDebug() << "Animación del avión terminada";
                removeItem(avionActual);

                delete avionActual;
                avionActual = nullptr;
                timer->stop();
                timer->deleteLater();
            });
        }
    }
}


void firstScn::comprobarImpacto(qreal x)
{
    QRectF rectBounds(clickPos.x() - 75 / 2, clickPos.y() - 75 / 2, 75, 75);

    if (rectBounds.contains(x, clickPos.y())) {
        manejarImpactoMisil();
    }
}

void firstScn::manejarImpactoMisil()
{
    if (!misilActual) return;

    misilActual->setZValue(3);
    addItem(misilActual);
    misilActual->getAnimacion()->start();

    connect(misilActual->getAnimacion(), &QPropertyAnimation::finished, this, [this] {
        if (misilActual) {
            removeItem(misilActual);
            delete misilActual;
            misilActual = nullptr;
        }
    });

    // Cambiar el color del rectángulo y comprobar impacto con buques
    for (QGraphicsRectItem *rect : cuadricula) {
        if (rect->contains(rect->mapFromScene(clickPos))) {
            if (rect->brush().color() == QColor("#004C84") || rect->brush().color() == Qt::red) {
                auto currentClickPos = clickPos; // Capturar la posición actual del clic

                if(rect->brush().color() == QColor("#004C84")){
                    // Calcular la posición ajustada del humo
                    qreal humoX = (static_cast<int>(currentClickPos.x()) / 75) * 75 + 5;
                    qreal humoY = (static_cast<int>(currentClickPos.y()) / 75) * 75 + 5;

                    // Añadir humo en la posición ajustada
                    Humo *humo = new Humo(":/humo.png");
                    humo->setPos(humoX, humoY);
                    humo->setScale(0.15); // Escala del humo
                    humo->setZValue(4);
                    addItem(humo);
                }
                return;
            }

            bool buqueEncontrado = false;

            for (auto &buqueConDetalles : buques) {
                Buque *buque = buqueConDetalles.buque;
                BuqueDetalles &detalles = buqueConDetalles.detalles;
                if (buque->collidesWithItem(rect)) {
                    detalles.vida--;
                    qDebug() << "Vida del buque: " << detalles.vida;
                    rect->setBrush(QBrush(QColor("#004C84")));

                    if (detalles.vida <= 0) {
                        buque->setZValue(2);
                        valHumos = true;
                        // Eliminar humos en los recuadros del buque destruido
                        for (QGraphicsRectItem *rectHumo : cuadricula) {
                            if (buque->collidesWithItem(rectHumo)) {
                                QList<QGraphicsItem*> itemsInRect = items(rectHumo->rect().translated(rectHumo->pos()));
                                for (QGraphicsItem *item : itemsInRect) {
                                    Humo *humo = dynamic_cast<Humo*>(item);
                                    if (humo) {
                                        removeItem(humo);
                                        delete humo;
                                    }
                                }
                            }
                        }
                    }
                    buqueEncontrado = true;
                    break;
                }
            }

            if (!buqueEncontrado) {
                rect->setBrush(QBrush(Qt::red));
            }

            remainingClicks--;

            if (mainWindow) {
                QLCDNumber *balas = mainWindow->findChild<QLCDNumber*>("balas");
                if (balas) {
                    balas->display(remainingClicks);
                }
            }

            if (mainWindow) {
                QLCDNumber *barcos = mainWindow->findChild<QLCDNumber *>("barcos");
                if (barcos) {
                    barcos->display(countRemainingBuques());
                }
            }
        }
    }
}

int firstScn::countRemainingBuques() const {
    int count = 0;
    for (const auto &buqueConDetalles : buques) {
        if (buqueConDetalles.detalles.vida > 0) {
            count++;
        }
    }
    return count;
}
