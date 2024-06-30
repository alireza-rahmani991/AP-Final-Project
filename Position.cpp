#include "position.h"

Position::Position(int X, int Y):x(X), y(Y) {}

Position::Position():x(0), y(0) {}


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

