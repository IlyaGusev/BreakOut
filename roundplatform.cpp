#include "roundplatform.h"

RoundPlatform::RoundPlatform() : QGraphicsItem(),
    _rect(0, 0, 0, 0), _pen(Qt::black), _brush(Qt::black){}

void RoundPlatform::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setPen(_pen);
    painter->setBrush(_brush);
    painter->drawChord(0, 0, _rect.width(), _rect.height()*2, 0, 180*16);
}

QRectF RoundPlatform::boundingRect() const{
     qreal penWidth = 1;
     return QRectF(0 - penWidth / 2, 0 - penWidth / 2,
                   _rect.width() + penWidth, _rect.height()*2 + penWidth);
}

void RoundPlatform::setRect(QRectF cp){
     _rect=cp;
}

QPainterPath RoundPlatform::shape() const{
     QPainterPath path;
     path.moveTo(_rect.width()/2, _rect.height()/2);
     path.arcTo(_rect, 0, 180);
     return path;
}

void RoundPlatform::setPen(QPen pen){
    _pen = pen;
}

void RoundPlatform::setBrush(QBrush brush){
    _brush = brush;
}
