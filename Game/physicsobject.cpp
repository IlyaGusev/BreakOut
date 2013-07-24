#include "physicsobject.h"

PhysicsObject::PhysicsObject(QObject *parent) :
    QObject(parent), _speed(0, 0), _isDestroyable(false)
{
}

void PhysicsObject::setSpeed(QVector2D sp){
    _speed=sp;
}
QVector2D PhysicsObject::getSpeed() const{
    return _speed;
}

void PhysicsObject::setDestroyable(bool destr){
    _isDestroyable=destr;
}
bool PhysicsObject::isDestroyable() const{
    return _isDestroyable;
}
