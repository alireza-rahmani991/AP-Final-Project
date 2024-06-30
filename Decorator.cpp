#include "Decorator.h"



Decorator::Decorator(int Width, int Height, Position _position, QGraphicsPixmapItem* Image)
        : BodyObject(Width, Height, _position, Image) {

}

void Decorator::draw(QGraphicsScene &scene) {
    if (image) {
        image->setPixmap(image->pixmap().scaled(width, height,Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }


}
