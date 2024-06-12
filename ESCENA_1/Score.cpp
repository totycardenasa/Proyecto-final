#include "Score.h"
#include <QFont>
#include "Game.h"

Score::Score(Game *game, QGraphicsItem *parent) : QGraphicsTextItem(parent), game(game), score(0) {
    // draw the text
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 0
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times", 16));
}

void Score::increase() {
    score++;
    setPlainText(QString("Score: ") + QString::number(score)); // Score: 1

    if (score == 20) {
        game->stopGame();
    }
}

int Score::getScore() {
    return score;
}
