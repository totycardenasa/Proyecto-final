#ifndef FIRSTSCN_H
#define FIRSTSCN_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
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

// Estructura para asociar el buque con sus detalles
struct BuqueConDetalles {
    Buque* buque;
    BuqueDetalles detalles;

    bool operator==(const BuqueConDetalles &other) const {
        return buque == other.buque;
    }
};

class firstScn : public QGraphicsScene
{
    Q_OBJECT
public:
    firstScn(MainWindow *parent = nullptr);
    int countRemainingBuques() const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    MainWindow *mainWindow;
    QGraphicsPixmapItem *telon;  // Puntero al telón
    QList<BuqueConDetalles> buques; // Lista que contiene los buques y sus detalles
    QList<QGraphicsRectItem*> cuadricula; // Crear una lista de rectángulos (son cuadrados porque miden lo mismo de lado y lado)
    int remainingClicks; // Contador para los clics válidos

};

#endif // FIRSTSCN_H
