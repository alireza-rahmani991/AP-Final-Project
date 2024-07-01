#include "player.h"
#include "position.h"


Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity) :
    BodyObject(Width, Height, _position, Image)
{
    speed = Speed;
    velocity = Velocity;
}