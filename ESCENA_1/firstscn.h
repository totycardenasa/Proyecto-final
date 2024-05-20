#ifndef FIRSTSCN_H
#define FIRSTSCN_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include "buque.h"

class MainWindow;

// Estructura personalizada para almacenar los detalles del buque
struct BuqueDetalles {
    QPointF posicion;
    qreal escala;
    QString rutaImagen;
    int vida;
};

class firstScn : public QGraphicsScene
{
    Q_OBJECT
public:
    firstScn(MainWindow *parent = nullptr);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    MainWindow *mainWindow;
    QGraphicsPixmapItem *telon;  // Puntero al telón
    QList<Buque*> buques; // Declaración correcta para contener múltiples objetos Buque
    QList<QGraphicsRectItem*> cuadricula; // crear una lista de rectángulos (son cuadrados porque miden lo mismo de lado y lado)
};

#endif // FIRSTSCN_H
