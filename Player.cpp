#include "player.h"
#include "Platform.h"
#include "position.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

Player::Player(int Width, int Height, Position _position, QGraphicsPixmapItem* standRightImage, QGraphicsPixmapItem* standLeftImage, int Speed, Position Velocity, int groundY,QGraphicsScene* scene,const std::vector<Platform*>& platforms) :
    BodyObject(Width, Height, _position, standRightImage), scene(scene), platforms(platforms)
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



    //Adding animation for jumping while running right
    auto pixmap = new QPixmap(":/img/running21.png");
    auto scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpFrames.append(new QPixmap(scaledPixmap));

    pixmap = new QPixmap(":/img/running22.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpFrames.append(new QPixmap(scaledPixmap));



    //Adding animation for jumping while running left
    pixmap = new QPixmap(":/img/runLeft21.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpLeftFrames.append(new QPixmap(scaledPixmap));

    pixmap = new QPixmap(":/img/runLeft22.png");
    scaledPixmap = pixmap->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
    jumpLeftFrames.append(new QPixmap(scaledPixmap));

    jumpAnimTimer = new QTimer(this);
    jumpAnimTimer->setInterval(0);
    connect(jumpAnimTimer, &QTimer::timeout, this, &Player::jumpAnim);



    //Connecting to gravity
    heightAnimator = new QPropertyAnimation(this, "height", this);
    connect(heightAnimator, &QPropertyAnimation::finished, this, &Player::handleGravity);



    //Adding animation for running right
    for (int i = 1; i <= 30; i++) {
        auto pixmapPath = QString(":/img/running%1.png").arg(i);
        auto pixmap2 = new QPixmap(pixmapPath);
        if (pixmap2->isNull()) {
            std::cerr << "Failed to load " << pixmapPath.toStdString() << std::endl;
        } else {
            auto scaledPixmap2 = pixmap2->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
            runFrames.append(new QPixmap(scaledPixmap2));
        }
    }
    //Connecting the animation
    runAnimTimer = new QTimer(this);
    runAnimTimer->setInterval(200 / speed);
    connect(runAnimTimer, &QTimer::timeout, this, &Player::runAnim);



    //Adding animation for running left
    for (int i = 1; i <= 30; i++) {
        auto pixmapPath = QString(":/img/runLeft%1.png").arg(i);
        auto pixmap3 = new QPixmap(pixmapPath);
        if (pixmap3->isNull()) {
            std::cerr << "Failed to load " << pixmapPath.toStdString() << std::endl;
        } else {
            auto scaledPixmap3 = pixmap3->scaled(animWidth, animHeight, Qt::KeepAspectRatioByExpanding);
            leftRunFrames.append(new QPixmap(scaledPixmap3));
        }
    }
    //Connecting the animation
    leftRunAnimTimer = new QTimer(this);
    leftRunAnimTimer->setInterval(200 / speed);
    connect(leftRunAnimTimer, &QTimer::timeout, this, &Player::leftRunAnim);
    runLeftFrame = 0;

    //Checking if player is still on platform or above it
    platformCheckerTimer = new QTimer(this);
    connect(platformCheckerTimer, &QTimer::timeout, this, &Player::checkOnPlatform);
    platformCheckerTimer->start(50);
}



void Player::draw(QGraphicsScene &scene) {
    if (image) {
        image->setPixmap(image->pixmap().scaled(width, height, Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}

void Player::handleMovement(QKeyEvent* event) {
    // Handling left movement
    if (event->key() == Qt::Key_Left) {
        // Check if the player is at the left edge of the screen
        if (position.getX() <= 0) {
            // Stop the left run animation and set the standing image
            leftRunAnimTimer->stop();
            setStandingImage();
        } else {
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
    }
    // Handling right movement
    else if (event->key() == Qt::Key_Right) {
        // Handle key press and release events for right movement
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
    }
    // Handling up movement
    else if (event->key() == Qt::Key_Space && position.getY() >= 320) {
        handleUpMovement();
    }
    // Handling down movement
    else if (event->key() == Qt::Key_Down) {
        std::cout << position.getX() << "   " << position.getY() << "  " << sceneX << std::endl;
    }
}

void Player::handleGravity() {
    if (position.getX() + sceneX + width >= 1960 && position.getX() + sceneX <= 2400 && position.getY() <= 400) {
        heightAnimator->stop();

        // Set up a new animation to move the player up
        heightAnimator->setStartValue(position.getY());
        heightAnimator->setEndValue(330);
        heightAnimator->setDuration(700);
        heightAnimator->setEasingCurve(QEasingCurve::InQuad);
        heightAnimator->start();
    } else {
        heightAnimator->stop();

        // Set up a new animation to move the player to the ground level
        heightAnimator->setStartValue(position.getY());
        heightAnimator->setEndValue(groundY);
        heightAnimator->setDuration(700);
        heightAnimator->setEasingCurve(QEasingCurve::InQuad);
        heightAnimator->start();
    }

    // If the player has jumped, set the standing image
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
    heightAnimator->setEndValue(groundY - 300);
    heightAnimator->setDuration(1000);
    heightAnimator->setEasingCurve(QEasingCurve::OutQuad);
    connect(heightAnimator, &QPropertyAnimation::valueChanged, this, [this](const QVariant &value) {
        position.setY(value.toInt());
        image->setPos(position.getX(), position.getY());
    });
    heightAnimator->start();
    platformCheckerTimer->stop();
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
    // Setting the standing left image
    if(isRunningLeft){
        image->setPixmap(standLeftImg.scaled(width, height, Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        jumped = false;
    }
    // Setting the standing left image
    else{
        image->setPixmap(standRightImg.scaled(width, height, Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        jumped = false;
    }
    platformCheckerTimer->start();
}


void Player::handleRightMovement() {
    if (position.getX() >= (scene->width() - width) / 2) {
        // Moving the scene while the player's moving
        sceneX += speed;
        for (auto item : scene->items()) {
            if (item != this->image) {
                item->moveBy(-static_cast<qreal>(speed), 0);
            }
        }
    } else {
        int newX = position.getX() + speed;
        position.setX(newX);
        image->setPos(newX, position.getY());
    }
}

void Player::handleLeftMovement() {
    if (position.getX() <= 50 && sceneX >= 10) {
        // Moving the scene while the player's moving
        sceneX -= speed;
        for (auto item : scene->items()) {
            if (item != this->image) {
                item->moveBy(static_cast<qreal>(speed), 0);
            }
        }
    } else {
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


void Player::checkOnPlatform() {
    bool onPlat = false;
    int tolerance = 2;

    for (auto platform : platforms) {
        // Check if the player overlaps with the platform
        if ((position.getX() + sceneX + width > platform->getPosition().getX() - tolerance) &&
            (position.getX() + sceneX < platform->getPosition().getX() + platform->getWidth() + tolerance)) {
            onPlat = true;
            break;

        }
    }
    if(!onPlat && !falling){
        heightAnimator->stop();
        heightAnimator->setStartValue(position.getY());
        heightAnimator->setEndValue(3000);
        heightAnimator->setDuration(2000);
        heightAnimator->setEasingCurve(QEasingCurve::InQuad);
        heightAnimator->start();
        falling = true;
    }
    if(onPlat && falling){
        falling = false;
        handleGravity();
    }
}


Player::~Player() {
    delete heightAnimator;
    delete jumpAnimTimer;
    delete runAnimTimer;
    delete leftRunAnimTimer;
    delete platformCheckerTimer;
    qDeleteAll(jumpLeftFrames);
    qDeleteAll(leftRunFrames);
    qDeleteAll(jumpFrames);
    qDeleteAll(runFrames);
}

int Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(int speed) {
    this->speed = speed;
}

QTimer *Player::getRunAnimTimer() const {
    return runAnimTimer;
}

QTimer *Player::getLeftRunAnimTimer() const {
    return leftRunAnimTimer;
}

int Player::getSceneX() const {
    return sceneX;
}
