#ifndef MISIL_H
#define MISIL_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class Misil : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)

public:
    Misil(const QString &filePath, QGraphicsItem *parent = nullptr);

    QPropertyAnimation* getAnimacion() const;
    void setXyYPosition(qreal x, qreal y);

private:
    QPixmap imagenMisil;
    QPropertyAnimation *animacion;
};

#endif // MISIL_H
