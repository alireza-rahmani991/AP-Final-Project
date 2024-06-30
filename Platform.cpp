#include "platform.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <position.h>



Platform::Platform(int Width, int Height, Position _position, QGraphicsPixmapItem* Image) :
    BodyObject(Width, Height, _position, Image)
{

}

void Platform::draw(QGraphicsScene &scene) {
    if (image){
        image->setPixmap(image->pixmap().scaled(width, height,Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}
