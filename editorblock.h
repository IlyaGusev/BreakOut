#ifndef EDITORBLOCK_H
#define EDITORBLOCK_H
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QBrush>
#include <QPen>
#include "scene.h"

#include <QDebug>
class EditorBlock : public QGraphicsRectItem
{
    public:
        explicit EditorBlock(Scene *scene, QGraphicsItem *gparent = 0);
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    private:
        int color;
        Scene* _scene;
};

#endif // EDITORBLOCK_H
