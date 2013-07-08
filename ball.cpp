#include "ball.h"

Ball::Ball(QGraphicsScene *scene, QObject *parent, QGraphicsItem *gparent) :
    SceneObject(scene, parent, gparent)
{
    delete graphics;
    graphics = new QGraphicsEllipseItem(0, scene);
}
