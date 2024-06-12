#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"
#include "Score.h"
#include "Health.h"

class Game : public QGraphicsScene {
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void stopGame(); // Nuevo método para detener el juego
    bool isGameRunning() const; // Nuevo método para verificar si el juego está en curso

    Player *player;
    Score *score;
    Health *health;
    bool gameRunning; // Bandera para indicar si el juego está en curso
};

#endif // GAME_H
