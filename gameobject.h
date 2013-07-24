#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "physicsobject.h"

class SceneObject
{
    public:
        PhysicsObject* properties;
        QGraphicsItem* graphics;
        explicit SceneObject(QGraphicsScene *scene,
                             QObject *parent = 0,
                             QGraphicsItem *gparent = 0
                             );
        virtual ~SceneObject();
        bool collidesWithItem(const SceneObject *other, QPointF* intersection=0) const;
};

#endif // SCENEOBJECT_H
