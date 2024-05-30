#ifndef AVIONES_H
#define AVIONES_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Aviones : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)

public:
    Aviones(const QString &filePath, QGraphicsItem *parent = nullptr);

    QPropertyAnimation* getAnimacion() const;
    void setYPosition(qreal y); // Método para establecer la posición Y del avión

public slots:
    void setX(qreal x);

private:
    QPixmap imagenAvion;
    QPropertyAnimation *animacion;
};

#endif // AVIONES_H
