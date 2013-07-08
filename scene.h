#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QVector>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QDebug>
#include <QGraphicsView>
#include "menu.h"
#include <cmath>
#include "roundplatform.h"
#include "sceneobject.h"
#include "ball.h"
#include "block.h"
#include "platform.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
    public:
        Scene(int width, int height, QObject * parent = 0);
        ~Scene();
        void start();
        void createPlatform(int, int);
        void createBorders();
        void addBall(QRectF, QColor, QVector2D);
        void addBlock(QRectF, QColor);
        void clearScene();
    protected:
        void keyPressEvent(QKeyEvent * pe);
        void keyReleaseEvent(QKeyEvent * pe);
    private slots:
        void nextTick();
    signals:
        void quit();
    public slots:
        void exit();
        void initGame(); //
        void initLevelEditor(); //
        void initSettings(); //
    private:
        Menu* mainMenu;
        Menu* settingsMenu;
        QGraphicsView* view;
        Platform* platform;
        QVector<Ball*> balls;
        QVector<Block*> borders;
        QVector<Block*> blocks;
        QTimer timer;
        void calculateCollide(SceneObject* main, SceneObject* secondary);
        void initMainMenu();

};

#endif // SCENE_H
