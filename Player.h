#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "bodyobject.h"
#include <QKeyEvent>
#include <vector>


class Player : public BodyObject
{
private:
    int speed;
    Position velocity;
    int imageIndex;
    std::vector<QGraphicsPixmapItem*> runningImages;
    QGraphicsScene* scene;
public:
    Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity, QGraphicsScene* scene);
    void draw(QGraphicsScene &scene) override;
    void handleGravity();
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement(QKeyEvent* event);
    void handleKeyRelease(QKeyEvent* event);

};

#endif // PLAYER_H
