#ifndef EDITORBLOCK_H
#define EDITORBLOCK_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QBrush>
#include <QPen>
#include "scene.h"

const int LEFT_BORDER = 10;
const int UP_BORDER = 10;
const int DOWN_BORDER = 600;
const int RIGHT_BORDER = 1024-170;

class EditorBlock : public QGraphicsRectItem
{
    public:
        explicit EditorBlock(Scene *scene, QGraphicsItem *gparent = 0);
        int color(){ return _color; }
        void setColor(int c){_color=c;}
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    private:
        int _color;
        Scene* _scene;
};

#endif // EDITORBLOCK_H
