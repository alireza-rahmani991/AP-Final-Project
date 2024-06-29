#ifndef BODYOBJECT_H
#define BODYOBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <position.h>

class BodyObject
{
private:
    int width;
    int height;
    Position position;
    // QGraphicsPixmapItem image;
    QGraphicsPixmapItem* image = nullptr;

public:
    BodyObject(int Width, int Height, Position _position, QGraphicsPixmapItem* Image);
    virtual void draw(QGraphicsScene &scene) = 0;
};

#endif // BODYOBJECT_H
