#include "platform.h"

Platform::Platform(QGraphicsScene *scene, QObject *parent, QGraphicsItem *gparent) :
    SceneObject(scene, parent, gparent)
{
    delete graphics;
    graphics = new RoundPlatform;
    scene->addItem(graphics);
}
