#include "firstscn.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QMainWindow>
#include "mainwindow.h"
#include <QDebug>

firstScn::firstScn(MainWindow *parent)
    : QGraphicsScene(0, 0, 1350, 750, parent), mainWindow(parent), remainingClicks(50)
{
    // Lista de detalles para los objetos Buque (posición, escala y ruta de la imagen)
    QList<BuqueDetalles> detallesBuques = {
        {QPointF(66, 3), 0.39, ":/buque_vertical.png", 6},
        {QPointF(378, 160), 0.32, ":/buque_horizontal.png", 5},
        {QPointF(1191, 153), 0.39, ":/buque_vertical.png", 6},
        {QPointF(304, 379), 0.39, ":/buque_horizontal.png", 6},
        {QPointF(891, 300), 0.39, ":/buque_vertical.png", 6},
        {QPointF(314, 525), 0.19, ":/buque_vertical.png", 3},
        {QPointF(904, 23), 0.19, ":/buque_horizontal.png", 3}
    };

    // Crear y agregar múltiples objetos Buque (atrás del telón)
    for (const auto &detalles : detallesBuques) {
        Buque *buque = new Buque(detalles.rutaImagen); // Usar la ruta de la imagen
        buque->setPos(detalles.posicion);
        buque->setScale(detalles.escala);
        buque->setZValue(-1); // Colocar buques debajo del telón, el Zvalue sirve para establecer jerarquia de aparición
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
    for (int i = 0; i < 10; i = i + 1) { // los cuadrados en y
        for (int j = 0; j < 18; j = j + 1) { // los cuadrados en x
            QGraphicsRectItem *rect = addRect(j * 75, i * 75, 75, 75, QPen(Qt::white));
            rect->setZValue(1); // Colocar la cuadrícula sobre el telón
            cuadricula.append(rect);
        }
    }
}

void firstScn::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF clickPos = event->scenePos();
    bool buqueEncontrado = false;

    // Verificar si se han agotado los clics válidos
    if (remainingClicks <= 0) {
        return;
    }

    // Encontrar el rectángulo en la cuadrícula que corresponde a la posición del clic
    for (QGraphicsRectItem *rect : cuadricula) {
        if (rect->contains(rect->mapFromScene(clickPos))) {
            // Si el rectángulo ya es gris o rojo, no hacer nada
            if (rect->brush().color() == Qt::gray || rect->brush().color() == Qt::red) {
                return;
            }

            // Verificar si hay un buque en cualquier parte dentro del rectángulo de la cuadrícula
            QRectF rectBounds = rect->sceneBoundingRect();
            for (auto &buqueConDetalles : buques) {
                Buque *buque = buqueConDetalles.buque;
                BuqueDetalles &detalles = buqueConDetalles.detalles;
                if (buque->collidesWithItem(rect)) {
                    // Reducir la vida del buque en 1
                    detalles.vida--;
                    qDebug() << "Vida del buque: " << detalles.vida;

                    // Cambiar el color del rectángulo a gris
                    rect->setBrush(QBrush(Qt::gray));

                    // Si la vida del buque llega a 0, cambiar su ZValue a 1
                    if (detalles.vida <= 0) {
                        buque->setZValue(2); // Colocar el buque sobre la cuadrícula
                    }
                    buqueEncontrado = true;
                    break;
                }
            }

            // Si no se encontró ningún buque en la posición del clic, cambiar el color del rectángulo a rojo
            if (!buqueEncontrado) {
                rect->setBrush(QBrush(Qt::red));
            }

            // Disminuir el contador de clics válidos
            remainingClicks--;
            return;
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
