#ifndef BODYOBJECT_H
#define BODYOBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "position.h"
#include <QObject>

class BodyObject : public QObject, public QGraphicsPixmapItem
{
protected:
    int width;
    int height;
    Position position;
    QGraphicsPixmapItem* image = nullptr;

public:
    BodyObject(int Width, int Height, Position _positionz, QGraphicsPixmapItem* Image);
    virtual void draw(QGraphicsScene &scene) = 0;
    int getWidth() const;
    int getHeight() const;
    const Position &getPosition() const;
    QGraphicsPixmapItem *getImage() const;
    void setPosition(const Position &position);
};

#endif // BODYOBJECT_H
