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
    enum BlockType{STANDART, UNDESTR, BONUS};

    explicit EditorBlock(BlockType,QGraphicsItem *gparent = 0);
    int color(){ return _color; }
    void setColor(int c){_color=c;}

    void setRect(QRectF);
    void setPen(QPen);
    void setBrush(QBrush);
    void setType(BlockType);
    QRectF rect() const;
    QPen pen() const;
    QBrush brush() const;
    BlockType blockType() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
    QPainterPath shape() const;
signals:
    void signalCopy(EditorBlock::BlockType);
    void signalRemove(EditorBlock::BlockType);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    int _color;
    QRectF _rect;
    QPen _pen;
    QBrush _brush;
    BlockType _type;
};

#endif // EDITORBLOCK_H
