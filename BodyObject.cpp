#include "bodyobject.h"
#include <QGraphicsPixmapItem>

BodyObject::BodyObject(int Width, int Height, Position _position, QGraphicsPixmapItem *Image = nullptr)
{
    width = Width;
    height = Height;
    position = _position;
    image = Image;
}
