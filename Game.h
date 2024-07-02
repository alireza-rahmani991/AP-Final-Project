#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include "Decorator.h"
#include "Player.h"
#include "platform.h"
#include <QGraphicsItem>


class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game();

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Player *player; // Declare the player object as a member variable
};

#endif
