#include "gameobject.h"
#include <QDebug>
GameObject::GameObject(QGraphicsScene *scene, QObject *parent, QGraphicsItem *gparent) :
    properties(new PhysicsObject(parent)), graphics(new QGraphicsRectItem(gparent, scene)){}

GameObject::~GameObject(){
    delete properties;
    delete graphics;
}

static inline void _q_adjustRect(QRectF *rect)
{
    if (!rect->width())
        rect->adjust(0, 0, 1, 0);
    if (!rect->height())
        rect->adjust(0, 0, 0, 1);
}

bool GameObject::collidesWithItem(const GameObject *other, QPointF* interpoint) const
{
    QPainterPath path = graphics->mapFromItem(other->graphics, other->graphics->shape());
    QRectF rectA(graphics->boundingRect());
    _q_adjustRect(&rectA);
    QRectF rectB(path.controlPointRect());
    _q_adjustRect(&rectB);
    if (!rectA.intersects(rectB))
        return false;
    QPainterPath intersection = graphics->shape().intersected(path);
    if(intersection.isEmpty())
        return false;
    QRectF is = intersection.boundingRect();
    if (interpoint!=0)
        *interpoint=(QPointF(is.x(), is.y()) + QPointF(is.width()/2, is.height()/2));
    return true;
}


