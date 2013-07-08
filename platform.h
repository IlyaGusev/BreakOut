#ifndef PLATFORM_H
#define PLATFORM_H

#include "sceneobject.h"
#include "roundplatform.h"

class Platform : public SceneObject
{
    public:
        explicit Platform(QGraphicsScene *scene,
                      QObject *parent = 0,
                      QGraphicsItem *gparent = 0
                      );
};

#endif // PLATFORM_H
