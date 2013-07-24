#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int width, int height, QObject * parent = 0);
};

#endif // SCENE_H
