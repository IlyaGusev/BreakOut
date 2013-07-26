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

#include "platform.h"
#include "ball.h"
#include "block.h"

const int BORDER_DEPTH = 10;
const int PLATFORM_WIDTH = 150;
const int PLATFORM_HEIGHT = 30;
const double PLATFORM_SPEED = 1.5;
const int GAME_STATS_WIDTH = 160;
const int BALL_RADIUS = 24;
const int BALL_SPEED = 2;
const int ANITIMER_STEP = 3;

class GameField : public QObject
{
    Q_OBJECT
public:
    explicit GameField(QGraphicsScene* sc = 0, QObject *parent = 0);
    ~GameField();
    void createPlatform(int, int);
    void createBorders();
    void addBall(QRectF rect, QColor clr, QVector2D vect);
    void addBlock(QRectF, QColor);
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
    Platform* platform;
    QVector<Ball*> balls;
    QVector<Block*> blocks;
    QTimer anitimer;
private:
    QGraphicsScene* scene;
    QVector<Block*> borders;
};

#endif // GAMEFIELD_H
