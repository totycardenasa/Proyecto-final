#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include "Player.h"
#include "Score.h"
#include "Health.h"

Game::Game(QWidget *parent) : QGraphicsScene(0, 0, 1360, 760, parent), gameRunning(true) {
    // Set the background
    setBackgroundBrush(QBrush(QPixmap(":/background.jpg")));

    // Create the player
    player = new Player(this);
    player->setPos(0, 0); // Start at the top-left corner
    // Make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // Add the player to the scene
    addItem(player);

    // Create the score and health
    score = new Score(this); // Pasar la referencia de Game al constructor de Score
    addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y() + 25);
    addItem(health);

    // Spawn enemies
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), player, SLOT(spawn()));
    timer->start(2000);
}

void Game::stopGame() {
    gameRunning = false;
    player->setFlag(QGraphicsItem::ItemIsFocusable, false); // Desactivar la capacidad de recibir eventos
}

bool Game::isGameRunning() const {
    return gameRunning;
}
