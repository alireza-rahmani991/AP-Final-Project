#include "Game.h"
#include "platform.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>


Game::Game()
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    showFullScreen();

    auto scene = new QGraphicsScene(this);

    scene->setSceneRect(0, 0, width(), height());

    scene->setBackgroundBrush(QBrush(QColor("white")));

    setScene(scene);

    int screenHeight = height();
    int totalWidth = width();
    int platformHeight = 110;




    Position backgroundPosition(0,0);
    auto backgroundImage = new QGraphicsPixmapItem( QPixmap(":/new/prefix1/img/background.png"));
    Decorator *background = new Decorator(width(), height(), backgroundPosition, backgroundImage);
    background->draw(*scene);


    auto hillImage1= new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/hill1.png"));
    Position hillPos1(100,screenHeight - (2 * platformHeight + 300));
    Decorator *hill1 = new Decorator(300, 300, hillPos1, hillImage1);
    hill1->draw(*scene);



    auto hillImage3= new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/hill3.png"));
    Position hillPos3(900,screenHeight - (2 * platformHeight + 300));
    Decorator *hill3 = new Decorator(300, 300, hillPos3, hillImage3);
    hill3->draw(*scene);



    auto hillImage5= new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/hill5.png"));
    Position hillPos5(600, screenHeight - (2 * platformHeight + 150));
    Decorator *hill5 = new Decorator(150, 150, hillPos5, hillImage5);
    hill5->draw(*scene);

    // Building the ground
    int platformWidth = totalWidth/3;
    auto img1 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos1(0, screenHeight - platformHeight);
    Platform *plt1 = new Platform(platformWidth, platformHeight , pos1, img1);


    auto img2 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos2(platformWidth, screenHeight - platformHeight);
    Platform *plt2 = new Platform(platformWidth, platformHeight , pos2, img2);


    auto img3 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos3(platformWidth*2, screenHeight - platformHeight);
    Platform *plt3 = new Platform(platformWidth, platformHeight , pos3, img3);

    plt1->draw(*scene);
    plt2->draw(*scene);
    plt3->draw(*scene);
}
