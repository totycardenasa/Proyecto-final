#include "aviones.h"

Aviones::Aviones(const QString &filePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), imagenAvion(filePath), velocidad(3), aceleracion(0.1) // Ajusta la aceleración según sea necesario
{
    setPixmap(imagenAvion);
    setScale(1);
    setPos(-210, 0);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Aviones::actualizarPosicion);
    timer->start(16); // Actualiza aproximadamente 60 veces por segundo (1000ms / 60 ≈ 16ms)
}

void Aviones::setYPosition(qreal y) {
    setPos(pos().x(), y);
}

void Aviones::actualizarPosicion() {
    qreal x = pos().x() + velocidad;
    setPos(x, pos().y());

    // Incrementar la velocidad con la aceleración
    velocidad += aceleracion;

    // Si el avión ha salido de la pantalla, detén el timer y elimina el avión
    if (x > 1350) {
        timer->stop();
        emit animacionTerminada();
    }
}
