#ifndef BUQUE_H
#define BUQUE_H

#include <QGraphicsPixmapItem>

class Buque : public QGraphicsPixmapItem
{
public:
    Buque(const QString &filePath, QGraphicsItem *parent = nullptr); // Definición del constructor clase Buque
    void posicion_buque(); // Crea el buque.
private:
    QPixmap imagenbuque; // Variable que contiene la imagen del buque.
};

#endif // BUQUE_H
