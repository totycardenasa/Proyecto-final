#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QSet>
#include <QTimer>

// Declaración anticipada de la clase Game
class Game;

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player(Game *game, QGraphicsItem *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
public slots:
    void spawn();
    void updatePosition();
    void handleCollisions();  // Nueva ranura para manejar las colisiones
private:
    Game *game;
    QSet<int> keysPressed;
    QTimer *timer;
    qreal speedX;
    qreal speedY;
};

#endif // PLAYER_H
