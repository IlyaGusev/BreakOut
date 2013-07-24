#ifndef PLATFORM_H
#define PLATFORM_H

#include "gameobject.h"
#include "roundplatform.h"

class Platform : public GameObject
{
public:
    explicit Platform(QGraphicsScene *scene=0, QObject *parent=0, QGraphicsItem *gparent=0);
};

#endif // PLATFORM_H
