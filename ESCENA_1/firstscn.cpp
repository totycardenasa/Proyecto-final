#include "firstscn.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMainWindow>
#include "mainwindow.h"
#include <QDebug>
#include <QLCDNumber>

firstScn::firstScn(MainWindow *parent)
    : QGraphicsScene(0, 0, 1350, 750, parent), mainWindow(parent), remainingClicks(50), avionActual(nullptr)
{
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
    clickPos = event->scenePos();

    // Verificar si se han agotado los clics válidos
    if (remainingClicks <= 0) {
        return;
    }

    if (!avionActual) {
        avionActual = new Aviones(":/avion.png");
        avionActual->setYPosition(clickPos.y() - 141); // Ajustar la posición Y del avión
        addItem(avionActual);
        avionActual->getAnimacion()->start();
        connect(avionActual->getAnimacion(), &QPropertyAnimation::valueChanged, this, [this](const QVariant &value){
            comprobarImpacto(value.toReal());
        });
        connect(avionActual->getAnimacion(), &QPropertyAnimation::finished, this, [this]{
            removeItem(avionActual);
            delete avionActual;
            avionActual = nullptr;
        });
    }
}

void firstScn::comprobarImpacto(qreal x)
{
    QRectF rectBounds(clickPos.x() - 75 / 2, clickPos.y() - 75 / 2, 75, 75);

    if (rectBounds.contains(x, clickPos.y())) {
        // Cambiar el color del rectángulo y comprobar impacto con buques
        for (QGraphicsRectItem *rect : cuadricula) {
            if (rect->contains(rect->mapFromScene(clickPos))) {
                if (rect->brush().color() == Qt::gray || rect->brush().color() == Qt::red) {
                    return;
                }

                bool buqueEncontrado = false;

                for (auto &buqueConDetalles : buques) {
                    Buque *buque = buqueConDetalles.buque;
                    BuqueDetalles &detalles = buqueConDetalles.detalles;
                    if (buque->collidesWithItem(rect)) {
                        detalles.vida--;
                        qDebug() << "Vida del buque: " << detalles.vida;
                        rect->setBrush(QBrush(Qt::gray));

                        if (detalles.vida <= 0) {
                            buque->setZValue(2);
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
                return;
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
