#ifndef BOOSTER_H
#define BOOSTER_H

#include "BodyObject.h"

class Booster : public BodyObject{
public:
    void draw(QGraphicsScene &scene) override;

public:
    Booster(int width, int height, const Position &positionz, QGraphicsPixmapItem *image);
    QGraphicsItem* getGraphicsItem() const;
};


#endif
