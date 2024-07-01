#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "bodyobject.h"


class Player : public BodyObject
{
private:
    int speed;
    Position velocity;
public:
    Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity);
    void handleGravity();
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement();

};

#endif // PLAYER_H