#ifndef DECORATOR_H
#define DECORATOR_H



#include "BodyObject.h"
#include <QGraphicsPixmapItem>

class Decorator : public BodyObject {
public:
    Decorator(int Width, int Height, Position _position, QGraphicsPixmapItem* Image = nullptr);
    void draw(QGraphicsScene &scene);
};



#endif