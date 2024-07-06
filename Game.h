#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QGraphicsView>
#include "Decorator.h"
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include <vector>
#include <QGraphicsItem>


class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void checkPlayerYPos();
    void handleGameOver();
    void startGame();
    void checkCollisions();



private:
    std::vector<Platform*> platforms;
    std::vector<Decorator*> decorators;
    std::vector<Enemy*> enemies;
    QTimer* gameOverTimer;
    Player *player;
    QGraphicsScene* scene;
};

#endif