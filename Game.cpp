#include "Game.h"

Game::Game() : gameOverTimer(new QTimer(this)),boostTimer(new QTimer(this)) {
    connect(gameOverTimer, &QTimer::timeout, this, &Game::checkPlayerYPos);
    connect(gameOverTimer, &QTimer::timeout, this, &Game::checkCollisions);
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
    if (player->getPosition().getY() > 2000) {
        QTimer::singleShot(500, this, &Game::handleGameOver);
    }
}

void Game::handleGameOver() {
    gameOverTimer->stop(); // Stop the timer before restarting the game
    scene->clear();

    delete player;
    player = nullptr;

    for (auto plt : platforms) {
        delete plt;
    }
    platforms.clear();

    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
    for (auto booster : boosters) {
        delete booster;
    }
    boosters.clear();


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

    Position backgroundPosition(0, 0);
    auto backgroundImage = new QGraphicsPixmapItem(QPixmap(":/img/background.png"));
    Decorator *background = new Decorator(width(), height(), backgroundPosition, backgroundImage);
    background->draw(*scene);

    auto hillImage1 = new QGraphicsPixmapItem(QPixmap(":/img/hill1.png"));
    Position hillPos1(100, screenHeight - (platformHeight + 1.5 * hillHeight + 20));
    Decorator *hill1 = new Decorator(hillWidth, hillHeight, hillPos1, hillImage1);
    hill1->draw(*scene);

    auto hillImage3 = new QGraphicsPixmapItem(QPixmap(":/img/hill3.png"));
    Position hillPos3(900, screenHeight - (platformHeight + 1.5 * hillHeight + 20));
    Decorator *hill3 = new Decorator(hillWidth, hillHeight, hillPos3, hillImage3);
    hill3->draw(*scene);

    auto hillImage5 = new QGraphicsPixmapItem(QPixmap(":/img/hill5.png"));
    Position hillPos5(600, screenHeight - (platformHeight + 1.5 * hillHeight + 20));
    Decorator *hill5 = new Decorator(hillWidth / 2, hillHeight / 2, hillPos5, hillImage5);
    hill5->draw(*scene);

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

    for (auto platform : platforms) {
        platform->draw(*scene);
    }

    int playerWidth = platformWidth / 5;
    int playerHeight = platformHeight / 3;
    int groundY = screenHeight - 3 * platformHeight;
    Position playerPosition(10, groundY);

    auto playerImage = new QGraphicsPixmapItem(QPixmap(":/img/Player_standing.png"));
    auto standLeftImg = new QGraphicsPixmapItem(QPixmap(":/img/standingLeft.png"));

    player = new Player(playerWidth, playerHeight, playerPosition, playerImage, standLeftImg, 10, Position(0, 0), groundY, scene, platforms);
    player->draw(*scene);
    int boostWidth = 70;
    int boostHeight = 70;
    auto boosterImage = new QGraphicsPixmapItem(QPixmap(":/img/boost"));
    Position boosterPos(900,groundY + 150);
    boosters.push_back(new Booster(boostWidth, boostHeight, boosterPos, boosterImage));

    for(auto booster:boosters){
        booster->draw(*scene);
    }

    int enemyWidth = 100;
    int enemyHeight = 100;
    auto enemyImage2 = new QGraphicsPixmapItem(QPixmap(":/img/enemyLeft"));
    Position enemyPos2(500, groundY + 140);
    enemies.push_back(new Enemy(enemyWidth, enemyHeight, enemyPos2, enemyImage2, 5, 400, 600));

    for (auto enemy : enemies) {
        enemy->draw(*scene);
    }

    gameOverTimer->start(50);
}

void Game::checkCollisions() {
    for (auto it = enemies.begin(); it != enemies.end();) {
        Enemy* enemy = *it;

        if (player->getPosition().getX() + player->getWidth() >= enemy->getPosition().getX()
            && player->getPosition().getX() <= enemy->getPosition().getX() + enemy->getWidth()) {
            if(isBoosted){
                scene->removeItem(enemy->getGraphicsItem());
                delete enemy;
                it = enemies.erase(it);
                continue;
            }
            if(!isBoosted){
            if (player->getPosition().getY() <= 530 && player->getPosition().getY() >= 450) {

                scene->removeItem(enemy->getGraphicsItem());
                delete enemy;
                it = enemies.erase(it);
                continue;
            } else if (player->getPosition().getY() == 534) {
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
    for (auto it = boosters.begin(); it != boosters.end();) {
        Booster *booster = *it;
        if (player->getPosition().getX() + player->getWidth() + player->getSceneX() >= booster->getPosition().getX() &&
                player->getPosition().getX() + player->getWidth() + player->getSceneX() <= booster->getPosition().getX() + booster->getWidth() ) {
            if (player->getPosition().getY() == 534) {
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
    player->setSpeed(player->getSpeed() / 2);
    player->getRunAnimTimer()->setInterval(200/player->getSpeed());
    player->getLeftRunAnimTimer()->setInterval(200/player->getSpeed());
    boostTimer->stop();

}

void Game::activateBoost() {
    isBoosted = true;
    player->setSpeed(player->getSpeed() * 2);
    player->getRunAnimTimer()->setInterval(200/player->getSpeed());
    player->getLeftRunAnimTimer()->setInterval(200/player->getSpeed());
    boostTimer->start(5000);
}
