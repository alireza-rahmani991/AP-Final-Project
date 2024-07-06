#ifndef ENEMY_H
#define ENEMY_H

#include "BodyObject.h"
#include <QTimer>


class Enemy : public BodyObject{
    Q_OBJECT

private:
    int speed;
    int direction;
    int leftMax;
    int rightMax;
    QTimer* moveTimer;
    QPixmap rightImg;
    QPixmap leftImg;
public:
    Enemy(int width, int height, const Position &positionz, QGraphicsPixmapItem *image, int speed, int leftMax, int rightMax);
    ~Enemy();
    void draw(QGraphicsScene &scene);
    QGraphicsItem* getGraphicsItem() const;

public slots:
    void move();
};


#endif
