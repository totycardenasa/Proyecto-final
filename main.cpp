
/*
Tutorial Topics:
-parents
-QGraphi#include "Player.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTimer>
-QGraphiscsScene>
-QGraphicsItem (QGraphicsRectItem)
-QGraphiscView
-events(keyPressEvent() and QkeyEvent)
-event propagation system
-QDebug
-QTimer
-signals and slots (conncet function)
-QObject and Q_OBJECT macro
-QGraphicsScene's sceneRect
-QGraphicsView's sceneRect
-QGraphicView coordinates vs QGraphicsScene coordinates vs QGraphicItem coordinates
*/
#include <QApplication>
#include "Game.h"

Game * game;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    game = new Game();
    game->show();

    return a.exec();
}
