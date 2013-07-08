#ifndef BLOCK_H
#define BLOCK_H

#include"sceneobject.h"

class Block : public SceneObject
{
    public:
        explicit Block(QGraphicsScene *scene,
                      QObject *parent = 0,
                      QGraphicsItem *gparent = 0
                      );
};

#endif // BLOCK_H
