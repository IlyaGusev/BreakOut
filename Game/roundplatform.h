#ifndef ROUNDPLATFORM_H
#define ROUNDPLATFORM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class RoundPlatform : public QGraphicsItem
{
public:
    RoundPlatform();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void setRect(QRectF cp);
    QPainterPath shape() const;
    void setPen(QPen);
    void setBrush(QBrush);
private:
    QRectF _rect;
    QPen _pen;
    QBrush _brush;
};

#endif // ROUNDPLATFORM_H
