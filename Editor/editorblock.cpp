#include "editorblock.h"

EditorBlock::EditorBlock(QGraphicsItem *gparent) :
    QGraphicsObject(gparent), _color(2)
{
    setToolTip(QString("%1").arg("Click LMB and drag to scene!\nClick RMB to change color!"));
    setCursor(Qt::OpenHandCursor);
    setPen(QPen(Qt::black));
    setBrush(QColor(Qt::GlobalColor(_color)));
}

void EditorBlock::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button()==Qt::RightButton){
        if (_color<18)
            setBrush(QColor(Qt::GlobalColor(++_color)));
        else
            _color=2;
    }
    if (event->button()==Qt::LeftButton){
        if (!((pos().x()>LEFT_BORDER) && (pos().x()+rect().width()<RIGHT_BORDER) &&
              (pos().y()>UP_BORDER) && (pos().y()+rect().height()<DOWN_BORDER)))
            emit signalCopy();
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
        emit signalRemove();
    }
}

void EditorBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(_pen);
    painter->setBrush(_brush);
    painter->drawRect(_rect.x(), _rect.y(), _rect.width(), _rect.height());
}

QRectF EditorBlock::boundingRect() const{
     qreal penWidth = 1;
     return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
                   _rect.width() + penWidth, _rect.height() + penWidth);
}

void EditorBlock::setRect(QRectF cp){
     _rect=cp;
}

QPainterPath EditorBlock::shape() const{
     QPainterPath path;
     path.addRect(0, 0, _rect.width(), _rect.height());
     return path;
}

void EditorBlock::setPen(QPen pen){
    _pen = pen;
    update();
}

void EditorBlock::setBrush(QBrush brush){
    _brush = brush;
    update();
}

QBrush EditorBlock::brush(){
    return _brush;
}

QPen EditorBlock::pen(){
    return _pen;
}

QRectF EditorBlock::rect(){
    return _rect;
}

