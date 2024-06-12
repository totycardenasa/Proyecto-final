#include "Health.h"
#include "Game.h"  // Incluir el encabezado de Game
#include <QFont>

Health::Health(QGraphicsItem *parent) : QGraphicsTextItem(parent), health(3) {
    // draw the text
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Health::decrease() {
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2

    if (health == 0) {
        dynamic_cast<Game *>(scene())->stopGame();
    }
}

int Health::getHealth() {
    return health;
}
