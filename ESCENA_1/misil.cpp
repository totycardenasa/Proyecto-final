#include "misil.h"

Misil::Misil(const QString &filePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), imagenMisil(filePath)
{
    setPixmap(imagenMisil);
    setScale(1);
    setPos(0, 0);

    animacion = new QPropertyAnimation(this, "scale");
    animacion->setDuration(200); // Duración de la animación del misil
    animacion->setStartValue(1.0);
    animacion->setEndValue(0.1); // Tamaño final del misil
}

QPropertyAnimation* Misil::getAnimacion() const {
    return animacion;
}

void Misil::setXyYPosition(qreal x, qreal y) {
    setPos(x, y);
}
