#include "player.h"
#include "platform.h"
#include "position.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>



Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity, QGraphicsScene* _scene) :
    BodyObject(Width, Height, _position, Image), imageIndex(0), scene(_scene)
{
    speed = Speed;
    velocity = Velocity;

    runningImages.push_back(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/Player_standing.png").scaled(100, 100)));
    runningImages.push_back(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/running1.png").scaled(100, 100)));
    runningImages.push_back(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/running2.png").scaled(100, 100)));
    runningImages.push_back(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/running3.png").scaled(100, 100)));
    runningImages.push_back(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/running4.png").scaled(100, 100)));
    runningImages.push_back(new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/running5.png").scaled(100, 100)));








}

void Player::draw(QGraphicsScene &scene) {
    if (image){
        scene.removeItem(image);
    }
    image = runningImages[imageIndex];
    image->setPos(position.getX(), position.getY());
    scene.addItem(image);
}

void Player::handleMovement(QKeyEvent* event){
    if (event->key() == Qt::Key_Left) {
        // handleLeftMovement();
        std::cout<<"Left\n";
    } else if (event->key() == Qt::Key_Right) {
        handleRightMovement();
        std::cout<<"Right\n";
    } else if (event->key() == Qt::Key_Up) {
        // handleUpMovement();
        std::cout<<"UP\n";
    } else if (event->key() == Qt::Key_Down) {
        // handleDownMovement();
        std::cout<<"Down\n";
    }
}

void Player::handleKeyRelease(QKeyEvent* event) {
    if (event->key() == Qt::Key_Right || event->key() == Qt::Key_Left) {
        imageIndex = 0; // Set to standing image
        this->draw(*scene);
    }
}


void Player::handleRightMovement() {
    position.setX(position.getX() + 10);
    position.setY(510);
    imageIndex = (imageIndex + 1) % runningImages.size(); // Cycle through the running images
    width = 100;
    height = 100;
    this->draw(*scene);
}
