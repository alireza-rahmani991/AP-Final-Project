#include "Booster.h"

Booster::Booster(int width, int height, const Position &positionz, QGraphicsPixmapItem *image) : BodyObject(width,
                                                                                                            height,
                                                                                                            positionz,
                                                                                                            image) {}

void Booster::draw(QGraphicsScene &scene) {
    if (image) {
        image->setPixmap(image->pixmap().scaled(width, height,Qt::KeepAspectRatioByExpanding));
        image->setPos(position.getX(), position.getY());
        scene.addItem(image);
    }
}

QGraphicsItem*  Booster::getGraphicsItem() const {
    return image;
}