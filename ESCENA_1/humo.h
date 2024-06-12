#ifndef HUMO_H
#define HUMO_H

#include <QGraphicsPixmapItem>

class Humo : public QGraphicsPixmapItem
{
public:
    Humo(const QString &filePath, QGraphicsItem *parent = nullptr);

private:
    QPixmap imagenHumo; // Variable que contiene la imagen del humo
};

#endif // HUMO_H
