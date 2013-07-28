#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QTimer>
#include <QVector>
#include <QString>
#include <QList>
#include <cmath>
#include <QTime>

#include "platform.h"
#include "ball.h"
#include "block.h"
#include "bonus.h"

class GameField : public QObject
{
    Q_OBJECT
    enum BlockType{STANDART, UNDESTR, BONUS};
public:
    static const int BALL_RADIUS = 24;
    static const int PLATFORM_WIDTH = 150;
    static const int PLATFORM_HEIGHT = 30;
    static const int BORDER_DEPTH = 10;
    static const int GAME_STATS_WIDTH = 160;
    double PLATFORM_SPEED;
    double BALL_SPEED;

public:
    explicit GameField(QGraphicsScene* sc = 0, QObject *parent = 0);
    ~GameField();
    void createPlatform(int, int);
    void createBorders();
    void addBall(QRectF rect, QColor clr, QVector2D vect);
    void addBlock(QRectF, QColor, BlockType);
    void addBonus(QRectF rect, Bonus::BonusType type);
    void loadLevel(QString);
    void clear();
    void start();
    void stop();
private:
    void calculateCollide(GameObject*, GameObject*, QPointF*);
signals:
    void signalBlockDestroyed();
    void signalLevelFinished();
    void signalBallLost();
private slots:
    void nextTick();
public:
    QGraphicsRectItem* background;
    Platform* platform;
    QVector<Ball*> balls;
    QVector<Block*> blocks;
    QTimer anitimer;
private:
    QGraphicsScene* scene;
    QVector<Block*> borders;
    QVector<Bonus*> bonuses;
};

#endif // GAMEFIELD_H
