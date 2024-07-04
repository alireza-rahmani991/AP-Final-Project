#include "player.h"
#include "platform.h"
#include "position.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>



Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity, int groundY) :
    BodyObject(Width, Height, _position, Image)
{
    isRunningLeft = false;
    standLeftImg = QPixmap(":/new/prefix1/img/standingLeft.png");


    this->groundY = groundY;
    speed = Speed;
    velocity = Velocity;
    this->standImg = image->pixmap();
    setFlag(GraphicsItemFlag::ItemIsFocusable);
    setFocus();

    animWidth = 2 * width;
    animHeight = 2 * height;

    //adding animation for jumping
    auto pixmap = new QPixmap(":/new/prefix1/img/jump_anim1.png");
    auto scaledPixmap = pixmap->scaled(animWidth,animHeight , Qt::KeepAspectRatioByExpanding);

    pixmap = new QPixmap(":/new/prefix1/img/jump_anim5.png");
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







    //adding animation for running right
    auto pixmap2 = new QPixmap(":/new/prefix1/img/running1.png");
    auto scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running2.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running3.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running4.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running5.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running6.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running7.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running8.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running9.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running10.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running11.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running12.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running13.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running14.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running15.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running16.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running17.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running18.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running19.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running20.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running21.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running22.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running23.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running24.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running25.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running26.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running28.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running29.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    pixmap2 = new QPixmap(":/new/prefix1/img/running30.png");
    scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    runFrames.append(new QPixmap(scaledPixmap2));
    runAnimTimer = new QTimer();
    runAnimTimer->setInterval(40);
    connect(runAnimTimer, &QTimer::timeout, this, &Player::runAnim);


    //adding animation for running left
    auto pixmap3 = new QPixmap(":/new/prefix1/img/runLeft1.png");
    auto scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft2.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft3.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft4.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft5.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft6.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft7.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft8.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft9.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft10.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft11.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft12.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft13.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft14.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft15.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft16.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft17.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft18.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft19.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft20.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft21.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft22.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft23.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft24.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft25.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft26.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft27.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft28.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft29.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    pixmap3 = new QPixmap(":/new/prefix1/img/runLeft30.png");
    scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    leftRunFrames.append(new QPixmap(scaledPixmap3));

    leftRunAnimTimer = new QTimer();
    leftRunAnimTimer->setInterval(40);
    connect(leftRunAnimTimer, &QTimer::timeout, this, &Player::leftRunAnim);
    runLeftFrame = 0;

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
        if (event->type() == QEvent::KeyPress) {
            handleLeftMovement();
            if(!leftRunAnimTimer->isActive()){
                runLeftFrame = 0;
                leftRunAnimTimer->start();
                isRunningLeft = true;
            }
        } else if (event->type() == QEvent::KeyRelease) {
            leftRunAnimTimer->stop(); // Stop the timer when the key is released
            setStandingLeftImage(); // Set the standing left image
        }
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

void Player::setStandingLeftImage() {
    image->setPixmap(standLeftImg.scaled(width, height, Qt::KeepAspectRatioByExpanding));
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
    if (!leftRunAnimTimer->isActive()) {
        runLeftFrame = 0;
        leftRunAnimTimer->start();
    }
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
        runAnimTimer->stop();
        setStandingImage(); // Set the standing right image when animation finishes
    } else {
        image->setPixmap(*runFrames.at(runFrame));
        runFrame++;
    }
}


void Player::leftRunAnim() {
    if (runLeftFrame >= leftRunFrames.size()) {
        runLeftFrame = 0; // Reset frame index when reaching the end
        leftRunAnimTimer->stop();
        isRunningLeft = false; // Set the flag to false when animation stops
        setStandingLeftImage(); // Set the standing left image when animation finishes
    } else {
        image->setPixmap(*leftRunFrames.at(runLeftFrame));
        runLeftFrame++;
    }
}