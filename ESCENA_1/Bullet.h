#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include "Game.h"

class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(Game *game, qreal startX, qreal startY, QGraphicsItem *parent = nullptr);
public slots:
    void move();
private:
    Game *game;
    qreal angle; // ángulo de lanzamiento
    qreal velocity; // velocidad inicial
    qreal gravity; // gravedad
    qreal time; // tiempo transcurrido
    qreal startX; // posición inicial X
    qreal startY; // posición inicial Y
};

#endif // BULLET_H
