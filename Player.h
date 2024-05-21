#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class scene2;
}
QT_END_NAMESPACE

class scene2 : public QMainWindow
{
    Q_OBJECT

public:
    scene2(QWidget *parent = nullptr);
    ~scene2();

private:
    Ui::scene2 *ui;
};
class Player:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
};

#endif // PLAYER_H
