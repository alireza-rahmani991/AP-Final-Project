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


    // Building the ground
    auto img1 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos1(0, 630);
    Platform *plt1 = new Platform(430, 110 , pos1, img1);


    auto img2 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos2(505, 630);
    Platform *plt2 = new Platform(430, 110 , pos2, img2);


    auto img3 = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/img/platform.png"));
    Position pos3(1010, 630);
    Platform *plt3 = new Platform(430, 110 , pos3, img3);

    plt1->draw(*scene);
    plt2->draw(*scene);
    plt3->draw(*scene);

    Position backgroundPosition(0,0);
    auto backgroundImage = new QGraphicsPixmapItem( QPixmap(":/background"));
    Decorator *background = new Decorator(width(), height(), backgroundPosition, backgroundImage);
    background->draw(*scene);

    auto hillImage1= new QGraphicsPixmapItem(QPixmap(":/hill1"));
    Position hillPos1(100,100);
    Decorator *hill1 = new Decorator(300, 300, hillPos1, hillImage1);
    hill1->draw(*scene);



    auto hillImage3= new QGraphicsPixmapItem(QPixmap(":/hill3"));
    Position hillPos3(900,100);
    Decorator *hill3 = new Decorator(300, 300, hillPos3, hillImage3);
    hill3->draw(*scene);



    auto hillImage5= new QGraphicsPixmapItem(QPixmap(":/hill5"));
    Position hillPos5(600,100);
    Decorator *hill5 = new Decorator(150, 150, hillPos5, hillImage5);
    hill5->draw(*scene);
}
