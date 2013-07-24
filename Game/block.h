#ifndef BLOCK_H
#define BLOCK_H

#include "gameobject.h"

class Block : public GameObject
{
public:
    explicit Block(QGraphicsScene *scene=0, QObject *parent=0, QGraphicsItem *gparent=0);
};

#endif // BLOCK_H
