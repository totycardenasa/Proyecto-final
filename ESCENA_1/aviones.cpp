#include "aviones.h"

Aviones::Aviones(const QString &filePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), imagenAvion(filePath)
{
    setPixmap(imagenAvion);
    setScale(1);
    setPos(0, 0);

    animacion = new QPropertyAnimation(this, "x");
    animacion->setDuration(5000); // Duración del vuelo del avión
    animacion->setStartValue(0);
    animacion->setEndValue(1350); // Asumiendo que la pantalla tiene 1350 de ancho
}

QPropertyAnimation* Aviones::getAnimacion() const {
    return animacion;
}

void Aviones::setYPosition(qreal y) {
    setPos(0, y);
}

void Aviones::setX(qreal x)
{
    setPos(x, pos().y());
}
