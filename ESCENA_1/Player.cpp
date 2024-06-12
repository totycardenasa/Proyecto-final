#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Health.h"
#include "Game.h"

Player::Player(Game *game, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), game(game), speedX(10), speedY(10) {
    setPixmap(QPixmap(":/planeplayer.png"));
    setPos(0, 0);
    setScale(0.3); // Ajustar el scale a 0.3
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::updatePosition);
    timer->start(50);
}

void Player::keyPressEvent(QKeyEvent *event) {
    if (!game->isGameRunning()) return; // Si el juego no está en curso, no hacer nada

    keysPressed.insert(event->key());
    if (event->key() == Qt::Key_Space) {
        // Crear una bala en la posición actual del jugador
        Bullet *bullet = new Bullet(game, x(), y() + 70);
        scene()->addItem(bullet);
    }
}

void Player::keyReleaseEvent(QKeyEvent *event) {
    if (!game->isGameRunning()) return; // Si el juego no está en curso, no hacer nada

    keysPressed.remove(event->key());
}

void Player::updatePosition() {
    if (!game->isGameRunning()) return; // Si el juego no está en curso, no hacer nada

    if (keysPressed.contains(Qt::Key_W) && pos().y() > 0) {
        setPos(x(), y() - speedY);
    }
    if (keysPressed.contains(Qt::Key_S) && pos().y() + pixmap().height() < 850) {
        setPos(x(), y() + speedY);
    }
    if (keysPressed.contains(Qt::Key_A) && pos().x() > 0) {
        setPos(x() - speedX, y());
    }
    if (keysPressed.contains(Qt::Key_D) && pos().x() + pixmap().width() < 1560) {
        setPos(x() + speedX, y());
    }

    handleCollisions(); // Llamar a la función para manejar las colisiones
}

void Player::spawn() {
    if (!game->isGameRunning()) return; // Si el juego no está en curso, no hacer nada

    // Crear un enemigo
    Enemy *enemy = new Enemy(game);
    scene()->addItem(enemy);
}

void Player::handleCollisions() {
    // Obtener una lista de todos los elementos que colisionan con el jugador
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Enemy)) {
            // Restar vida
            game->health->decrease();

            // Eliminar el enemigo de la escena y del heap
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];
        }
    }
}
