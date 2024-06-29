#include "position.h"

Position::Position() {}
Position::Position(int x, int y) : x(x), y(y) {}

int Position::getX() const {
    return x;
}

void Position::setX(int x) {
    Position::x = x;
}

int Position::getY() const {
    return y;
}

void Position::setY(int y) {
    Position::y = y;
}


