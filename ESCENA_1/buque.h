#ifndef BUQUE_H
#define BUQUE_H
#include <QGraphicsPixmapItem>

class Buque : public QGraphicsPixmapItem
{
public:
    Buque(const QString &filePath,QGraphicsItem *parent=nullptr); // definición del constructor clase buque
    void posicion_buque(); // crea el buque.
private:
    QPixmap imagenbuque; // creando una variable que contiene la iamgen del buque.
};

#endif // BUQUE_H
