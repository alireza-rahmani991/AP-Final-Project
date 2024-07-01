#include "player.h"
#include "platform.h"
#include "position.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>



Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity) :
    BodyObject(Width, Height, _position, Image)
{
    speed = Speed;
    velocity = Velocity;
}

void Player::draw(QGraphicsScene &scene) {
    if (image){
        image->setPixmap(image->pixmap().scaled(width, height,Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}

void Player::handleMovement(QKeyEvent* event){
    if (event->key() == Qt::Key_Left) {
        // handleLeftMovement();
        std::cout<<"Left\n";
    } else if (event->key() == Qt::Key_Right) {
        // handleRightMovement();
        std::cout<<"Right\n";
    } else if (event->key() == Qt::Key_Up) {
        // handleUpMovement();
        std::cout<<"UP\n";
    } else if (event->key() == Qt::Key_Down) {
        // handleDownMovement();
        std::cout<<"Down\n";
    }
}


// void Player::handleRightMovement(){

// }