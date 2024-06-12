#include "humo.h"

Humo::Humo(const QString &filePath, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), imagenHumo(filePath)
{
    setPixmap(imagenHumo);
    setScale(0.2); // Tamaño de la imagen del humo
}
