#include "editorblock.h"
const int LEFT_BORDER = 10;
const int UP_BORDER = 10;
const int DOWN_BORDER = 600;
const int RIGHT_BORDER = 1024-170;

EditorBlock::EditorBlock(Scene *scene, QGraphicsItem *gparent) :
    QGraphicsRectItem(gparent ,scene), color(2), _scene(scene)
{
    setToolTip(QString("%1").arg("Click LMB and drag to scene!\nClick RMB to change color!"));
    setCursor(Qt::OpenHandCursor);
    setPen(QPen(Qt::black));
    setBrush(QColor(Qt::GlobalColor(color)));
}

void EditorBlock::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button()==Qt::RightButton){
        if (color<18)
            setBrush(QColor(Qt::GlobalColor(++color)));
        else
            color=2;
    }
    if (event->button()==Qt::LeftButton){
        if (!((pos().x()>LEFT_BORDER) && (pos().x()+rect().width()<RIGHT_BORDER) &&
              (pos().y()>UP_BORDER) && (pos().y()+rect().height()<DOWN_BORDER)))
        _scene->copyEditorBlock(this);
    }
    setCursor(Qt::ClosedHandCursor);
}

void EditorBlock::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }
    setPos(pos()+(event->scenePos()-event->lastScenePos()));
}

void EditorBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    setCursor(Qt::OpenHandCursor);
    if (!((pos().x()>LEFT_BORDER) && (pos().x()+rect().width()<RIGHT_BORDER) &&
          (pos().y()>UP_BORDER) && (pos().y()+rect().height()<DOWN_BORDER)) &&
        event->button()==Qt::LeftButton)
    {
        _scene->removeItem(this);
        delete this;
    }
}
