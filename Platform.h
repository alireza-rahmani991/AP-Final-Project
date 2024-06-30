#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <position.h>
#include "bodyobject.h"

class Platform : public BodyObject
{
public:
    Platform(int Width, int Height, Position _position, QGraphicsPixmapItem* Image);
    void draw(QGraphicsScene &scene) override;
};

#endif // PLATFORM_H
