#ifndef BALL_H
#define BALL_H

#include"sceneobject.h"

class Ball : public SceneObject
{
    public:
        explicit Ball(QGraphicsScene *scene,
                      QObject *parent = 0,
                      QGraphicsItem *gparent = 0
                      );
};

#endif // BALL_H
