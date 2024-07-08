#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QGraphicsView>
#include "Decorator.h"
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Booster.h"
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
    void activateBoost();
    void handleVictory();

public slots:
    void endBoost();

private:
    std::vector<Platform*> platforms;
    std::vector<Decorator*> decorators;
    std::vector<Enemy*> enemies;
    std::vector<Booster*> boosters;
    QTimer* gameOverTimer;
    QTimer* boostTimer;
    Player *player;
    QGraphicsScene* scene;
    bool isBoosted{};
    bool gameOver{};

};

#endif