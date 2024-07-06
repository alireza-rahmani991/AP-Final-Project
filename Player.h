#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "bodyobject.h"
#include "Platform.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsView>
#include <QList>
#include <QTimer>
#include <vector>

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
    int runLeftFrame{};
    QPixmap standRightImg;
    QPixmap standLeftImg;
    QList<QPixmap*> jumpFrames{};
    QList<QPixmap*> jumpLeftFrames{};
    QList<QPixmap*> runFrames{};
    QList<QPixmap*> leftRunFrames{};
    QTimer* jumpAnimTimer;
    QTimer* runAnimTimer;
    QTimer* leftRunAnimTimer;
    QTimer* platformCheckerTimer;
    bool jumped{};
    bool isRunningLeft;
    bool falling{};
    QGraphicsScene* scene;
    int sceneX{};
    std::vector<Platform*> platforms;


public:
    Player(int Width, int Height, Position _position, QGraphicsPixmapItem* standRightImage,QGraphicsPixmapItem* standLeftImage, int Speed, Position Velocity, int groundY, QGraphicsScene* scene,const std::vector<Platform*>& platforms);
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
    void leftRunAnim();
    void handleGravity();
    void setStandingImage();
    void checkOnPlatform();

};

#endif // PLAYER_H
