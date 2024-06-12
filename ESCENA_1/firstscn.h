#ifndef FIRSTSCN_H
#define FIRSTSCN_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QLCDNumber>
#include <QTimer>
#include "mainwindow.h"
#include "aviones.h"
#include "misil.h"
#include "buque.h"
#include "humo.h"

class firstScn : public QGraphicsScene
{
    Q_OBJECT

public:
    firstScn(MainWindow *parent = nullptr);
    ~firstScn();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void gameWon(); // Definir la señal

private:
    MainWindow *mainWindow;
    int remainingClicks;
    Aviones *avionActual;
    Misil *misilActual;
    QList<QGraphicsRectItem *> cuadricula;
    QList<QGraphicsPixmapItem *> telones;
    QGraphicsPixmapItem *telon;
    QPointF clickPos;
    bool valHumos;


    struct BuqueDetalles {
        QPointF posicion;
        qreal escala;
        QString rutaImagen;
        int vida;
    };

    struct BuqueConDetalles {
        Buque *buque;
        BuqueDetalles detalles;
    };

    QList<BuqueConDetalles> buques;

    void resetScene();
    void comprobarImpacto(qreal x);
    void manejarImpactoMisil();
    int countRemainingBuques() const;
};

#endif // FIRSTSCN_H
