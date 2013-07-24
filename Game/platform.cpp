#include "platform.h"

Platform::Platform(QGraphicsScene *scene, QObject *parent, QGraphicsItem *gparent) :
    GameObject(scene, parent, gparent)
{
    delete graphics;
    graphics = new RoundPlatform;
    if (scene!=0)
        scene->addItem(graphics);
}
