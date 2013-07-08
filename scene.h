#ifndef SCENE_H
#define SCENE_H

class Scene;
class EditorBlock;
    //QT
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QVector>
#include <QString>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QTextStream>
#include <QFile>

    //C++
#include <cmath>

    //My
#include "menu.h"
#include "sceneobject.h"
#include "ball.h"
#include "block.h"
#include "platform.h"
#include "editorblock.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
    public:
        Scene(int width, int height, QObject * parent = 0);
        ~Scene();
        void start();
        void copyEditorBlock(EditorBlock*);
    protected:
        void keyPressEvent(QKeyEvent * pe);
        void keyReleaseEvent(QKeyEvent * pe);
        void initMainMenu();
        void createPlatform(int, int);
        void createBorders();
        void addBall(QRectF, QColor, QVector2D);
        void addBlock(QRectF, QColor);
        void clearScene();
        void loadLevel(QString);
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

};

#endif // SCENE_H
