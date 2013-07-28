#include "physicsobject.h"

PhysicsObject::PhysicsObject(QObject *parent) :
    QObject(parent), _speed(0, 0)
{
}

void PhysicsObject::setSpeed(QVector2D sp){
    _speed=sp;
}
QVector2D PhysicsObject::getSpeed() const{
    return _speed;
}
