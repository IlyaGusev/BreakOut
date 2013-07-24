#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

#include <QObject>
#include <QVector2D>

class PhysicsObject : public QObject
{
    Q_OBJECT
public:
    explicit PhysicsObject(QObject *parent = 0);
    void setSpeed(QVector2D);
    QVector2D getSpeed() const;
    void setDestroyable(bool);
    bool isDestroyable() const;
private:
    QVector2D _speed;
    bool _isDestroyable;
};

#endif // PHYSICSOBJECT_H
