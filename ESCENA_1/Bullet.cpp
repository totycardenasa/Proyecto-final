#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include <QtMath>

Bullet::Bullet(Game *game, qreal startX, qreal startY, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), game(game), angle(15), velocity(100), gravity(70), time(0), startX(startX), startY(startY) {
    // drew the bullet
    setPixmap(QPixmap(":/rocket.png"));
    setScale(0.2);

    // set the initial position of the bullet
    setPos(startX, startY);

    // make/connect a timer to move() the bullet every so often
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // start the timer
    timer->start(50);
}

void Bullet::move() {
    if (!game->isGameRunning()) return;
    time += 0.05; // incrementa el tiempo (ajusta según la frecuencia del temporizador)

    // movimiento parabólico
    qreal dx = velocity * qCos(qDegreesToRadians(angle)) * time;
    qreal dy = -(velocity * qSin(qDegreesToRadians(angle)) * time - 0.5 * gravity * time * time);

    setPos(startX + dx, startY + dy);

    // detectar colisiones con enemigos
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            game->score->increase();
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
    }

    // si la bala sale de la pantalla, eliminarla
    if (pos().x() > 1364 || pos().y() > 760) {
        scene()->removeItem(this);
        delete this;
    }
}


