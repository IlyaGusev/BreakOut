#ifndef EDITORBLOCK_H
#define EDITORBLOCK_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QBrush>
#include <QPainter>
#include <QPen>

const int LEFT_BORDER = 10;
const int UP_BORDER = 10;
const int DOWN_BORDER = 600;
const int RIGHT_BORDER = 1024-170;

class EditorBlock : public QGraphicsObject
{
        Q_OBJECT
    public:
        explicit EditorBlock(QGraphicsItem *gparent = 0);
        int color(){ return _color; }
        void setColor(int c){_color=c;}

        void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
        QRectF boundingRect() const;
        QPainterPath shape() const;
        void setRect(QRectF);
        void setPen(QPen);
        void setBrush(QBrush);
        QRectF rect();
        QPen pen();
        QBrush brush();
    signals:
        void signalCopy();
        void signalRemove();
    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    private:
        int _color;
        QRectF _rect;
        QPen _pen;
        QBrush _brush;
};

#endif // EDITORBLOCK_H
