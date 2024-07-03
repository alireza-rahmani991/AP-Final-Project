#include "player.h"
#include "platform.h"
#include "position.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>



Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity, int groundY) :
        BodyObject(Width, Height, _position, Image)
{
    this->groundY = groundY;
    speed = Speed;
    velocity = Velocity;
    this->standImg = image->pixmap();
    setFlag(GraphicsItemFlag::ItemIsFocusable);
    setFocus();

    animWidth = 2 * width;
    animHeight = 2 * height;

    //adding animation for jumping
    auto pixmap = new QPixmap(":/new/prefix1/img/jump/jump_anim1.png");
    auto scaledPixmap = pixmap->scaled(animWidth,animHeight , Qt::KeepAspectRatioByExpanding);

    pixmap = new QPixmap(":/new/prefix1/img/jump/jump_anim5.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpFrames.append(new QPixmap(scaledPixmap));

    jumpAnimTimer = new QTimer();
    jumpAnimTimer->setInterval(0);
    connect(jumpAnimTimer, &QTimer::timeout, this, &Player::jumpAnim);


    //connecting to gravity
    heightAnimator = new QPropertyAnimation(this, "height", this);
    heightAnimator->setStartValue(groundY);
    heightAnimator->setEndValue(groundY);
    heightAnimator->setDuration(500);
    heightAnimator->start();
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::setStandingImage);







    //adding animation for running
    auto pixmap2 = new QPixmap(":/new/prefix1/img/running/running1.png");
    auto scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running2.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running3.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running4.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running5.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running6.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running7.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running8.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running9.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running10.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running11.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running12.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running13.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running14.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running15.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running16.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running17.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running18.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running19.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running20.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running21.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running22.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running23.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running24.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running25.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running26.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running28.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running29.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running/running30.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    runAnimTimer = new QTimer();
    runAnimTimer->setInterval(40);
    connect(runAnimTimer, &QTimer::timeout, this, &Player::runAnim);


}
void Player::draw(QGraphicsScene &scene) {
    if (image){
        image->setPixmap(image->pixmap().scaled(width, height,Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}

void Player::handleMovement(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        handleLeftMovement();
    } else if (event->key() == Qt::Key_Right) {
        if (event->type() == QEvent::KeyPress) {
            handleRightMovement();
            if(!runAnimTimer->isActive()){
                runFrame = 0;
                runAnimTimer->start();
            }

        } else if (event->type() == QEvent::KeyRelease) {
            runAnimTimer->stop();
            setStandingImage();
            runAnimStarted = false;
        }
    } else if (event->key() == Qt::Key_Up) {
        handleUpMovement();
    } else if (event->key() == Qt::Key_Down) {
        // handleDownMovement();
        std::cout << "Down\n";
    }
}



void Player::handleGravity() {
    heightAnimator->stop();
    heightAnimator->setStartValue(position.getY());
    heightAnimator->setEndValue(groundY);
    heightAnimator->setDuration(700);
    heightAnimator->setEasingCurve(QEasingCurve::InQuad);

    heightAnimator->start();
}

void Player::handleUpMovement() {
    jumpFrame = 0;
    jumpAnimTimer->start();


    //jumping then activating gravity
    heightAnimator->stop();
    heightAnimator->setStartValue(position.getY());
    heightAnimator->setEndValue(groundY - 150);
    heightAnimator->setDuration(500);
    heightAnimator->setEasingCurve(QEasingCurve::OutQuad);
    connect(heightAnimator, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        position.setY(value.toInt());
        image->setPos(position.getX(), position.getY());
    });
    heightAnimator->start();
}

void Player::jumpAnim() {
    if (!jumpFrames.isEmpty() && jumpFrame < jumpFrames.size()) {
        image->setPixmap(*jumpFrames.at(jumpFrame));
        jumpFrame++;
    }

    // Stop the timer when the last frame is reached
    if (jumpFrame >= jumpFrames.size()) {
        jumpAnimTimer->stop();
    }
}

void Player::setStandingImage() {
    image->setPixmap(standImg.scaled(width, height, Qt::KeepAspectRatioByExpanding));
    image->setPos(position.getX(), position.getY());

}

Player::~Player() {
    delete heightAnimator;
    delete jumpAnimTimer;
    delete runAnimTimer;
    qDeleteAll(jumpFrames);
    qDeleteAll(runFrames);
}


void Player::handleLeftMovement() {
    // Move the player left
    int newX = position.getX() - speed;  // Adjust speed as needed
    position.setX(newX);
    image->setPos(newX, position.getY());
}

void Player::handleRightMovement() {
    // Move the player right
    int newX = position.getX() + speed;  // Adjust speed as needed
    position.setX(newX);
    image->setPos(newX, position.getY());
}

void Player::runAnim() {
    if (runFrame >= runFrames.size()) {
        runFrame = 0; // Reset frame index when reaching the end
    }
    image->setPixmap(*runFrames.at(runFrame));
    runFrame++;

}
