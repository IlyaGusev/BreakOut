#include "ball.h"

Ball::Ball(QGraphicsScene *scene,
           QObject *parent,
           QGraphicsItem *gparent) :
    GameObject(scene, parent, gparent)
{
    delete graphics;
    graphics = new QGraphicsEllipseItem(gparent, scene);
}
