#ifndef BODYOBJECT_H
#define BODYOBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "position.h"

class BodyObject
{
protected:
    int width;
    int height;
    Position position;
    QGraphicsPixmapItem* image = nullptr;

public:
    BodyObject(int Width, int Height, Position _positionz, QGraphicsPixmapItem* Image);
    virtual void draw(QGraphicsScene &scene) = 0;
};

#endif // BODYOBJECT_H
