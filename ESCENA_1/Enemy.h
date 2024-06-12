#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Game.h"

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(Game *game, QGraphicsItem *parent = nullptr);
public slots:
    void move();
private:
    Game *game;
};

#endif // ENEMY_H
