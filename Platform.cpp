#include "platform.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <position.h>

Platform::Platform(int Width, int Height, Position _position, QGraphicsPixmapItem* Image) :
    BodyObject(Width, Height, _position, Image)
{

}

void Platform::draw(QGraphicsScene &scene) {
    // scene.addItem(image); // Implement the function
}