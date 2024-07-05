#include "player.h"
#include "platform.h"
#include "position.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* standRightImage, QGraphicsPixmapItem* standLeftImage, int Speed, Position Velocity, int groundY,QGraphicsScene* scene) :
        BodyObject(Width, Height, _position, standRightImage), scene(scene)
{
    this->groundY = groundY;
    speed = Speed;
    velocity = Velocity;
    this->standRightImg = image->pixmap();
    this->standLeftImg = standLeftImage->pixmap();
    setFlag(GraphicsItemFlag::ItemIsFocusable);
    setFocus();

    animWidth = 2 * width;
    animHeight = 2 * height;

    //adding animation for jumping
    auto pixmap = new QPixmap(":/new/prefix1/img/running21.png");
    auto scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpFrames.append(new QPixmap(scaledPixmap));

    pixmap = new QPixmap(":/new/prefix1/img/running22.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpFrames.append(new QPixmap(scaledPixmap));

    pixmap = new QPixmap(":/new/prefix1/img/runLeft21.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpLeftFrames.append(new QPixmap(scaledPixmap));

    pixmap = new QPixmap(":/new/prefix1/img/runLeft22.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpLeftFrames.append(new QPixmap(scaledPixmap));

    jumpAnimTimer = new QTimer(this);
    jumpAnimTimer->setInterval(0); // Set an appropriate interval for the jump animation
    connect(jumpAnimTimer, &QTimer::timeout, this, &Player::jumpAnim);

    //connecting to gravity
    heightAnimator = new QPropertyAnimation(this, "height", this);
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);

    //adding animation for running right
    for (int i = 1; i <= 30; i++) {
        auto pixmapPath = QString(":/new/prefix1/img/running%1.png").arg(i);
        auto pixmap2 = new QPixmap(pixmapPath);
        if (pixmap2->isNull()) {
            std::cerr << "Failed to load " << pixmapPath.toStdString() << std::endl;
        } else {
            auto scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
            runFrames.append(new QPixmap(scaledPixmap2));
        }
    }
    runAnimTimer = new QTimer(this);
    runAnimTimer->setInterval(40);
    connect(runAnimTimer, &QTimer::timeout, this, &Player::runAnim);

    //adding animation for running left
    for (int i = 1; i <= 30; i++) {
        auto pixmapPath = QString(":/new/prefix1/img/runLeft%1.png").arg(i);
        auto pixmap3 = new QPixmap(pixmapPath);
        if (pixmap3->isNull()) {
            std::cerr << "Failed to load " << pixmapPath.toStdString() << std::endl;
        } else {
            auto scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
            leftRunFrames.append(new QPixmap(scaledPixmap3));
        }
    }
    leftRunAnimTimer = new QTimer(this);
    leftRunAnimTimer->setInterval(40);
    connect(leftRunAnimTimer, &QTimer::timeout, this, &Player::leftRunAnim);
    runLeftFrame = 0;
}

void Player::draw(QGraphicsScene &scene) {
    if (image) {
        image->setPixmap(image->pixmap().scaled(width, height, Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}

void Player::handleMovement(QKeyEvent* event) {
    if (event->key() == Qt::Key_Left) {
        if(position.getX() <= 0){
            leftRunAnimTimer->stop();
            setStandingImage();
        }
        else{
            if (event->type() == QEvent::KeyPress) {
                handleLeftMovement();
                isRunningLeft = true;
                if (!leftRunAnimTimer->isActive()) {
                    runLeftFrame = 0;
                    leftRunAnimTimer->start();
                }
            } else if (event->type() == QEvent::KeyRelease) {
                leftRunAnimTimer->stop();
                setStandingImage();
            }
        }
    } else if (event->key() == Qt::Key_Right) {
        if (event->type() == QEvent::KeyPress) {
            handleRightMovement();
            isRunningLeft = false;
            if (!runAnimTimer->isActive()) {
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
    if (jumped) {
        setStandingImage();
    }
}

void Player::handleUpMovement() {
    jumpFrame = 0;
    jumpAnimTimer->start();

    // jumping then activating gravity
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
    QList<QPixmap*>* currentJumpFrames = isRunningLeft ? &jumpLeftFrames : &jumpFrames;

    if (!currentJumpFrames->isEmpty() && jumpFrame < currentJumpFrames->size()) {
        image->setPixmap(*currentJumpFrames->at(jumpFrame));
        jumpFrame++;
    }

    // Stop the timer when the last frame is reached
    if (jumpFrame >= currentJumpFrames->size()) {
        jumpAnimTimer->stop();
        jumped = true;
    }
}

void Player::setStandingImage() {
    if(isRunningLeft){
        image->setPixmap(standLeftImg.scaled(width, height, Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        jumped = false;
    }
    else{
        image->setPixmap(standRightImg.scaled(width, height, Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        jumped = false;
    }
}


void Player::handleRightMovement() {
    if(position.getX() >= (scene->width() - width)/2){
        sceneX += 10;
        for(auto item : scene->items()){
            if(item != this->image){
                item->moveBy(-10, 0);

            }
        }
    }
    else{
        int newX = position.getX() + speed;
        position.setX(newX);
        image->setPos(newX, position.getY());
    }

}

void Player::handleLeftMovement() {

    if(position.getX() <= 50 && sceneX >= 10 ){
        sceneX -= 10;
        for(auto item : scene->items()){
            if(item != this->image){
                item->moveBy(10, 0);
            }
        }
    }
    else{
        int newX = position.getX() - speed;
        position.setX(newX);
        image->setPos(newX, position.getY());
    }
}

void Player::runAnim() {
    if (runFrame >= runFrames.size()) {
        runFrame = 0;
    }
    image->setPixmap(*runFrames.at(runFrame));
    runFrame++;
}

void Player::leftRunAnim() {
    if (runLeftFrame >= leftRunFrames.size()) {
        runLeftFrame = 0;
    }
    image->setPixmap(*leftRunFrames.at(runLeftFrame));
    runLeftFrame++;
}

Player::~Player() {
    delete heightAnimator;
    delete jumpAnimTimer;
    delete runAnimTimer;
    delete leftRunAnimTimer;
    qDeleteAll(jumpLeftFrames);
    qDeleteAll(leftRunFrames);
    qDeleteAll(jumpFrames);
    qDeleteAll(runFrames);
}
