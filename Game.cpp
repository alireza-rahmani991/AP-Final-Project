#include "Game.h"



Game::Game()
{

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

    Position backgroundPosition(0,0);
    auto backgroundImage = new QGraphicsPixmapItem( QPixmap(":/new/prefix1/img/background.png"));
    Decorator *background = new Decorator(width(), height(), backgroundPosition, backgroundImage);
    background->draw(*scene);

    auto hillImage1 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/hill1.png"));
    Position hillPos1(100, screenHeight - (platformHeight + 1.5 * hillHeight + 20)); // Position above platform
    Decorator *hill1 = new Decorator(hillWidth, hillHeight, hillPos1, hillImage1);
    hill1->draw(*scene);

    auto hillImage3 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/hill3.png"));
    Position hillPos3(900, screenHeight - (platformHeight + 1.5 * hillHeight + 20)); // Position above platform
    Decorator *hill3 = new Decorator(hillWidth, hillHeight, hillPos3, hillImage3);
    hill3->draw(*scene);

    auto hillImage5 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/hill5.png"));
    Position hillPos5(600, screenHeight - (platformHeight + 1.5 * hillHeight + 20)); // Position above platform
    Decorator *hill5 = new Decorator(hillWidth / 2, hillHeight / 2, hillPos5, hillImage5);
    hill5->draw(*scene);



    int platformWidth = screenWidth / 3;

    // Building the ground


    auto img1 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos1(0, screenHeight - platformHeight);  // Position the first platform at the bottom of the screen
    Platform *plt1 = new Platform(platformWidth+2, platformHeight, pos1, img1);

    auto img2 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos2(platformWidth, screenHeight - platformHeight);  // Position the second platform next to the first
    Platform *plt2 = new Platform(platformWidth+2, platformHeight, pos2, img2);

    auto img3 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos3((platformWidth * 2 ), screenHeight - platformHeight);  // Position the third platform next to the second
    Platform *plt3 = new Platform(platformWidth+2, platformHeight, pos3, img3);

    plt1->draw(*scene);
    plt2->draw(*scene);
    plt3->draw(*scene);


    int playerWidth = platformWidth / 5;
    int playerHeight = platformHeight / 3;
    int groundY = screenHeight - 3 * platformHeight;
    Position playerPosition(10, groundY);
    auto playerImage = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/Player_standing.png"));
    auto standLeftImg = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/standingLeft.png"));
    player = new Player(playerWidth, playerHeight, playerPosition, playerImage,standLeftImg,  5, Position(0, 0), groundY, scene);

    player->draw(*scene);



}

void Game::keyPressEvent(QKeyEvent *event) {
    player->handleMovement(event);

}

void Game::keyReleaseEvent(QKeyEvent *event) {
    if(event->isAutoRepeat()) return;
    player->handleMovement(event);
}