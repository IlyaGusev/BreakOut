#ifndef BALL_H
#define BALL_H

#include "gameobject.h"

class Ball : public GameObject
{
public:
    explicit Ball(QGraphicsScene *scene=0, QObject *parent=0, QGraphicsItem *gparent=0);
};

#endif // BALL_H
