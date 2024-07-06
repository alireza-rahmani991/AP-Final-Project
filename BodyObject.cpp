#include "bodyobject.h"
#include <QGraphicsPixmapItem>

BodyObject::BodyObject(int Width, int Height, Position _position, QGraphicsPixmapItem *Image = nullptr)
{
    width = Width;
    height = Height;
    position = _position;
    image = Image;
}

int BodyObject::getWidth() const {
    return width;
}

int BodyObject::getHeight() const {
    return height;
}

QGraphicsPixmapItem *BodyObject::getImage() const {
    return image;
}

const Position &BodyObject::getPosition() const {
    return position;
}

void BodyObject::setPosition(const Position &position) {
    BodyObject::position = position;
}

