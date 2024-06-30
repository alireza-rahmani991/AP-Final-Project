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
}
