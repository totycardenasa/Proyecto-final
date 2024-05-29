#include "Player.h"
#include "ui_scene2.h"
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include "Bullet.h"
#include "Enemy.h"

scene2::scene2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::scene2)
{
    ui->setupUi(this);
}

scene2::~scene2()
{
    delete ui;
}
Player::Player(QGraphicsItem *parent): QGraphicsRectItem(parent){

}

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if (pos().x()> 0)
        setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x()+100 < 800)
        setPos(x()+10,y());
    }
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }
}

void Player::spawn(){
    //Create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}

