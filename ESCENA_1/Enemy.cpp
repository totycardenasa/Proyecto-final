#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int

Enemy::Enemy(Game *game, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), game(game) {
    // establecer una posición y aleatoria entre 100 y 700
    int random_number = 100 + rand() % (700 - 100);
    setPos(1360, random_number);

    // establecer la imagen
    setPixmap(QPixmap(":/enemyplane.png"));
    setScale(0.1); // escala reducida

    // conectar el temporizador para mover al enemigo
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));

    // iniciar el temporizador
    timer->start(50);
}

void Enemy::move() {
    if (!game->isGameRunning()) return; // Si el juego no está en curso, no hacer nada

    // mover enemigo a la izquierda
    setPos(x() - 5, y());

    // destruir enemigo cuando salga de la pantalla
    if (pos().x() < 0) {
        // disminuir la salud
        game->health->decrease();
        scene()->removeItem(this);
        delete this;
    }
}
