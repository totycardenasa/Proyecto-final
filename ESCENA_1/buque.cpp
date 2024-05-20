#include "buque.h"

Buque::Buque(const QString &filePath,QGraphicsItem *parent)
    : QGraphicsPixmapItem (parent),
    imagenbuque(filePath)
{
    setPixmap(imagenbuque);
    setScale(1); //tamaño de la imagen del buque

}
