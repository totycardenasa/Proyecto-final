#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

// Declaración anticipada de la clase Game
class Game;

class Score : public QGraphicsTextItem {
public:
    Score(Game *game, QGraphicsItem *parent = nullptr);
    void increase();
    int getScore();
private:
    int score;
    Game *game; // Referencia a la clase Game
};

#endif // SCORE_H
