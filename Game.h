#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "Decorator.h"
#include "Player.h"
#include "platform.h"
#include <vector>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QMediaContent>


class Game : public QGraphicsView
{
public:
    Game();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void checkPlayerYPos();
    void handleGameOver();
    void resetGame();



private:
    std::vector<Platform*> platforms;
    Player *player;
    QGraphicsScene* scene;
    Position lastPosition;
    QPointF lastScrollPosition;
    QAudioOutput *audioOutput;
    QBuffer *buffer;
    QMediaPlayer* mediaPlayer;
};

#endif
