#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "bodyobject.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QList>
#include <QTimer>


class Player : public BodyObject
{
    Q_OBJECT
    Q_PROPERTY(qreal height READ y WRITE setY)
private:
    int speed;
    int groundY{};
    int animHeight;
    int animWidth;
    Position velocity;
    QPropertyAnimation *heightAnimator;
    int jumpFrame{};
    int runFrame{};
    QPixmap standImg;
    QList<QPixmap*> jumpFrames{};
    QList<QPixmap*> runFrames{};
    QTimer* jumpAnimTimer;
    QTimer* runAnimTimer;
    bool runAnimStarted{};

public:
    Player(int Width, int Height, Position _position, QGraphicsPixmapItem* Image, int Speed, Position Velocity, int groundY);
    void draw(QGraphicsScene &scene) override;
    ~Player();
    void handleRightMovement();
    void handleLeftMovement();
    void handleUpMovement();
    void handleDownMovement();
    void handleMovement(QKeyEvent* event);

    qreal y() const { return position.getY(); }
    void setY(qreal h) { position.setY(h); }

public slots:
            void jumpAnim();
    void runAnim();
    void handleGravity();
    void setStandingImage();


};

#endif // PLAYER_H