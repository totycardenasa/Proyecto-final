#ifndef AVIONES_H
#define AVIONES_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QTimer>

class Aviones : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Aviones(const QString &filePath, QGraphicsItem *parent = nullptr);
    QPropertyAnimation* getAnimacion() const;
    void setYPosition(qreal y);

signals:
    void animacionTerminada();

public slots:
    void actualizarPosicion();

private:
    QPixmap imagenAvion;
    QTimer *timer;
    qreal velocidad;
    qreal aceleracion;
};

#endif // AVIONES_H
