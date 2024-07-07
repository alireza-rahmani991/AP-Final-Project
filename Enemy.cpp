#include "Enemy.h"

Enemy::Enemy(int width, int height, const Position &positionz, QGraphicsPixmapItem *leftImage, int speed, int leftMax, int rightMax) :
    BodyObject(width, height, positionz, leftImage), speed(speed), leftMax(leftMax), rightMax(rightMax), direction(1)
{
    if (leftImage) {
        this->leftImg = leftImage->pixmap().scaled(width, height, Qt::KeepAspectRatioByExpanding);
    }
    this->rightImg = QPixmap(":/img/enemyRight").scaled(width, height, Qt::KeepAspectRatioByExpanding);

    image->setPixmap(leftImg);


    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Enemy::move);
    moveTimer->setInterval(50);
    moveTimer->start();
}

void Enemy::draw(QGraphicsScene &scene) {
    if (image){
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}

void Enemy::move() {
    int newX = position.getX() + direction * speed;

    // Check if the enemy has reached the edge of the screen
    if (newX <= leftMax || newX + width >= rightMax) {
        direction *= -1;
        newX = position.getX() + direction * speed;
        // Update the enemy's image to face the correct direction
        if (direction == 1) {
            image->setPixmap(rightImg);
        } else {
            image->setPixmap(leftImg);
        }
    }

    position.setX(newX);

    image->setPos(newX, position.getY());
}

Enemy::~Enemy(){
    delete moveTimer;
}

QGraphicsItem*  Enemy::getGraphicsItem() const {
    return image;
}
