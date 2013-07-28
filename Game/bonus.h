#ifndef BONUS_H
#define BONUS_H
#include "gameobject.h"

class Bonus : public GameObject
{
public:
    enum BonusType{PLATFORM_EXTEND, PLATFORM_ACCELERATION, BALL_ACCELERATION, FIREBALL};

    explicit Bonus(BonusType __type, QGraphicsScene *scene=0, QObject *parent=0, QGraphicsItem *gparent=0);
    BonusType type() const;
private:
    BonusType _type;
};

#endif // BONUS_H
