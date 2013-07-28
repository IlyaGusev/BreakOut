#include "bonus.h"

Bonus::Bonus(BonusType __type, QGraphicsScene *scene,
             QObject *parent,
             QGraphicsItem *gparent) :
    GameObject(scene, parent, gparent), _type(__type)
{
    delete graphics;
    graphics = new QGraphicsEllipseItem(gparent, scene);
}

Bonus::BonusType Bonus::type() const{
    return _type;
}
