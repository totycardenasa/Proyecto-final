#include "firstscn.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMainWindow>
#include "mainwindow.h"
#include <QDebug>

firstScn::firstScn(MainWindow *parent)
    : QGraphicsScene(0, 0, 1350, 750, parent), mainWindow(parent)
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

    // Crear y agregar múltiples objetos Buque (debajo del telón)
    for (const auto &detalles : detallesBuques) {
        Buque *buque = new Buque(detalles.rutaImagen); // Usar la ruta de la imagen
        buque->setPos(detalles.posicion);
        buque->setScale(detalles.escala);
        buque->setZValue(-1); // Colocar buques debajo del telón
        addItem(buque);
        buques.append(buque);
    }

    // Añadir el telón
    /*QPixmap telonPixmap(":/fondo_azul.jpg");
    telonPixmap = telonPixmap.scaled(1350, 750, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    telon = new QGraphicsPixmapItem(telonPixmap);
    telon->setZValue(0); // Establecer ZValue del telón
    addItem(telon);
*/
    // Añadir la cuadrícula sobre el telón
    for (int i = 0; i < 10; i = i + 1) { // los cuadrados en y
        for (int j = 0; j < 18; j = j + 1) { // los cuadrados en x
            QGraphicsRectItem *rect = addRect(j * 75, i * 75, 75, 75, QPen(Qt::white));
            rect->setZValue(1); // Colocar la cuadrícula sobre el telón
            cuadricula.append(rect);
        }
    }
}

void firstScn::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();
    mainWindow->updateMousePosition(mousePos); // Llamar al método para actualizar la posición del mouse
    QGraphicsScene::mouseMoveEvent(event);
}

