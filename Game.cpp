#include "Game.h"
#include <QMessageBox>

Game::Game() :
    // Setting the timer
    gameOverTimer(new QTimer(this)),boostTimer(new QTimer(this)) {
    connect(gameOverTimer, &QTimer::timeout, this, &Game::checkPlayerYPos);
    connect(gameOverTimer, &QTimer::timeout, this, &Game::checkCollisions);
    connect(gameOverTimer, &QTimer::timeout, this, &Game::handleVictory);
    connect(boostTimer, &QTimer::timeout, this, &Game::endBoost);
    startGame();
}

void Game::keyPressEvent(QKeyEvent *event) {
    player->handleMovement(event);
}

void Game::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) return;
    player->handleMovement(event);
}

void Game::checkPlayerYPos() {
    if (player->getPosition().getY() > 1000) {
        QTimer::singleShot(500, this, &Game::handleGameOver);
    }
}

void Game::handleGameOver() {
    gameOverTimer->stop();

    // Clearing all the objects in the game
    scene->clear();

    delete player;
    player = nullptr;

    for (auto plt : platforms) {
        delete plt;
    }
    platforms.clear();

    for (auto decorator: decorators) {
        delete decorator;
    }
    decorators.clear();

    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    for (auto booster : boosters) {
        delete booster;
    }
    boosters.clear();

    // Re-starting the game
    startGame();
}



void Game::startGame() {
    int platformHeight = 110;

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, width(), height());
    scene->setBackgroundBrush(QBrush(QColor("white")));
    setScene(scene);

    int screenHeight = height();
    int screenWidth = width();

    int hillHeight = screenHeight / 3;
    int hillWidth = screenWidth / 3;


    //Adding decorations
    Position backgroundPosition(0, 0);
    auto backgroundImage = new QGraphicsPixmapItem(QPixmap(":/img/background.png"));
    Decorator *background = new Decorator(width(), height(), backgroundPosition, backgroundImage);
    background->draw(*scene);
    decorators.push_back(background);

    auto hillImage1 = new QGraphicsPixmapItem(QPixmap(":/img/hill1.png"));
    Position hillPos1(100, screenHeight - (platformHeight + 1.5 * hillHeight + 25));
    Decorator *hill1 = new Decorator(hillWidth , hillHeight + 50, hillPos1, hillImage1);
    hill1->draw(*scene);
    decorators.push_back(hill1);

    auto hillImage2 = new QGraphicsPixmapItem(QPixmap(":/img/hill3.png"));
    Position hillPos2(2500, screenHeight - (platformHeight + 1.5 * hillHeight + 20));
    Decorator *hill2 = new Decorator(hillWidth, hillHeight, hillPos2, hillImage2);
    hill2->draw(*scene);
    decorators.push_back(hill2);

    auto hillImage3 = new QGraphicsPixmapItem(QPixmap(":/img/hill5.png"));
    Position hillPos3(1200, screenHeight - (platformHeight + 1.5 * hillHeight + 20));
    Decorator *hill3 = new Decorator(hillWidth / 2, hillHeight / 2, hillPos3, hillImage3);
    hill3->draw(*scene);
    decorators.push_back(hill3);

    auto hillImage4 = new QGraphicsPixmapItem(QPixmap(":/img/hill1.png"));
    Position hillPos4(4000, screenHeight - (platformHeight + 1.5 * hillHeight + 25));
    Decorator *hill4 = new Decorator(hillWidth , hillHeight + 50, hillPos4, hillImage4);
    hill4->draw(*scene);
    decorators.push_back(hill4);


    //Adding platforms
    int platformWidth = screenWidth / 3;

    auto img1 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos1(0, screenHeight - platformHeight);
    Platform *plt1 = new Platform(platformWidth + 2, platformHeight, pos1, img1);
    platforms.push_back(plt1);

    auto img2 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos2(platformWidth, screenHeight - platformHeight);
    Platform *plt2 = new Platform(platformWidth + 2, platformHeight, pos2, img2);
    platforms.push_back(plt2);

    auto img3 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos3(platformWidth * 2, screenHeight - platformHeight);
    Platform *plt3 = new Platform(platformWidth + 2, platformHeight, pos3, img3);
    platforms.push_back(plt3);

    auto img4 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos4(platformWidth * 3.5, screenHeight - platformHeight);
    Platform *plt4 = new Platform(platformWidth + 2, platformHeight, pos4, img4);
    platforms.push_back(plt4);
    auto img5 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos5(platformWidth * 4.5, screenHeight - platformHeight);
    Platform *plt5 = new Platform(platformWidth + 2, platformHeight, pos5, img5);
    platforms.push_back(plt5);
    auto img6 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos6(platformWidth * 5.5, screenHeight - platformHeight);
    Platform *plt6 = new Platform(platformWidth + 2, platformHeight, pos6, img6);
    platforms.push_back(plt6);

    auto img7 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos7(platformWidth * 3.8, screenHeight - 3 * platformHeight);
    Platform *plt7 = new Platform(platformWidth + 2, platformHeight, pos7, img7);
    platforms.push_back(plt7);

    auto img8 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos8(platformWidth * 7.1, screenHeight - platformHeight);
    Platform *plt8 = new Platform(platformWidth + 2, platformHeight, pos8, img8);
    platforms.push_back(plt8);

    auto img9 = new QGraphicsPixmapItem(QPixmap(":/img/platform.png"));
    Position pos9(platformWidth * 8.1, screenHeight - platformHeight);
    Platform *plt9 = new Platform(platformWidth + 2, platformHeight, pos9, img9);
    platforms.push_back(plt9);

    for (auto platform : platforms) {
        platform->draw(*scene);
    }

    int playerWidth = platformWidth / 5;
    int playerHeight = platformHeight / 3;
    int groundY = screenHeight - 3 * platformHeight;
    Position playerPosition(10, groundY);

    //Adding the player to the scene
    auto playerImage = new QGraphicsPixmapItem(QPixmap(":/img/Player_standing.png"));
    auto standLeftImg = new QGraphicsPixmapItem(QPixmap(":/img/standingLeft.png"));

    player = new Player(playerWidth, playerHeight, playerPosition, playerImage, standLeftImg, 10, Position(0, 0), groundY, scene, platforms);
    player->draw(*scene);
    int boostWidth = 70;
    int boostHeight = 70;

    //Adding boosters to the scene
    auto boosterImage = new QGraphicsPixmapItem(QPixmap(":/img/boost"));
    Position boosterPos(600,groundY + 150);
    boosters.push_back(new Booster(boostWidth, boostHeight, boosterPos, boosterImage));

    auto boosterImage2 = new QGraphicsPixmapItem(QPixmap(":/img/boost"));
    Position boosterPos2(3000,groundY + 150);
    boosters.push_back(new Booster(boostWidth, boostHeight, boosterPos2, boosterImage2));

    for(auto booster:boosters){
        booster->draw(*scene);
    }


    //Adding enemies
    int enemyWidth = 100;
    int enemyHeight = 100;
    auto enemyImage2 = new QGraphicsPixmapItem(QPixmap(":/img/enemyLeft"));
    Position enemyPos2(400, groundY + 140);
    enemies.push_back(new Enemy(enemyWidth, enemyHeight, enemyPos2, enemyImage2, 5, 300, 500));

    for (auto enemy : enemies) {
        enemy->draw(*scene);
    }

    gameOverTimer->start(50);
}

void Game::checkCollisions() {
    // Iterate through the list of enemies
    for (auto it = enemies.begin(); it != enemies.end();) {
        Enemy* enemy = *it;

        // Check if the player has collided with the enemy horizontally
        if (player->getPosition().getX() + player->getWidth() >= enemy->getPosition().getX()
            && player->getPosition().getX() <= enemy->getPosition().getX() + enemy->getWidth()) {

            if (isBoosted) {
                scene->removeItem(enemy->getGraphicsItem());
                delete enemy;
                it = enemies.erase(it);
                continue;
            }

            if (!isBoosted) {
                // Check if the player is in a vertical range
                if (player->getPosition().getY() <= 530 && player->getPosition().getY() >= 450) {
                    // Destroy the enemy
                    scene->removeItem(enemy->getGraphicsItem());
                    delete enemy;
                    it = enemies.erase(it);
                    continue;
                } else if (player->getPosition().getY() == 534) {
                    // Destroy all enemies and restart the game
                    for (auto enemy : enemies) {
                        scene->removeItem(enemy->getGraphicsItem());
                        delete enemy;
                    }
                    enemies.clear();
                    startGame();
                    return;
                }
            }
        }

        ++it;
    }

    // Iterate through the list of boosters
    for (auto it = boosters.begin(); it != boosters.end();) {
        Booster *booster = *it;
        // Check if the player has collided with the booster horizontally
        if (player->getPosition().getX() + player->getWidth() + player->getSceneX() >= booster->getPosition().getX() &&
            player->getPosition().getX() + player->getWidth() + player->getSceneX() <= booster->getPosition().getX() + booster->getWidth() ) {
            // Check if the player is in a vertical position
            if (player->getPosition().getY() == 534) {
                // Destroy the booster and activate the boost
                scene->removeItem(booster->getGraphicsItem());
                delete booster;
                it = boosters.erase(it);
                activateBoost();
                continue;
            }
        }

        it++;
    }
}

void Game::endBoost() {
    isBoosted = false;

    // Reducing the player's speed
    player->setSpeed(player->getSpeed() / 2);

    // Updating the player's animation timers to match the new speed
    player->getRunAnimTimer()->setInterval(200/player->getSpeed());
    player->getLeftRunAnimTimer()->setInterval(200/player->getSpeed());

    boostTimer->stop();
}


void Game::activateBoost() {
    isBoosted = true;

    // Increasing the player's speed
    player->setSpeed(player->getSpeed() * 2);

    // Update the player's animation timers to match the new speed
    player->getRunAnimTimer()->setInterval(200/player->getSpeed());
    player->getLeftRunAnimTimer()->setInterval(200/player->getSpeed());

    boostTimer->start(5000);
}

void Game::handleVictory() {
    if (player->getPosition().getX() + player->getSceneX() == 3000) {// Reaching the end of the last platform
        QMessageBox msgBox;
        msgBox.setText("Congratulations! You won!");
        msgBox.exec();
        close();
    }
}
