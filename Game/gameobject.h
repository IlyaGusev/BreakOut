#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "physicsobject.h"

class GameObject
{
public:
    explicit GameObject(QGraphicsScene *scene, QObject *parent=0, QGraphicsItem *gparent=0);
    virtual ~GameObject();
    bool collidesWithItem(const GameObject *other, QPointF* intersection=0) const;
public:
    PhysicsObject* properties;
    QGraphicsItem* graphics;
};

#endif // GAMEOBJECT_H
