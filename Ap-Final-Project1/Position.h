#ifndef POSITION_H
#define POSITION_H

class Position
{
private:
    int x;
    int y;
public:
    Position();
    Position(int X, int Y);


    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
};

#endif // POSITION_H