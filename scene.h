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
#include <QList>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QLCDNumber>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>

    //C++
#include <cmath>

    //My
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
        void stop();
        void copyEditorBlock(EditorBlock*);
        void removeEditorBlock(EditorBlock*);
        void createPlatform(int, int);
        void createBorders();
        void addBall(QRectF, QColor, QVector2D);
        void addBlock(QRectF, QColor);
        void clearScene();
        void levelFinished();
        void loadLevel(QString);
    protected:
        void keyPressEvent(QKeyEvent * pe);
        void keyReleaseEvent(QKeyEvent * pe);
    public slots:
        void nextTick();
        void initMainMenu();
        void initGame();
        void initGameState();
        void updateGameState();
        void levelFinishedSlot();
        void gameOver();
        void initLevelEditor();
        void saveEditorLevel();
        void initSettings(); //
        void exit();
    signals:
        void quit();
    private:
        QLabel* message;
        QWidget* mainMenu;
        QWidget* settingsMenu;
        QWidget* editorMenu;
        QWidget* gameState;
        QGraphicsView* view;
        Platform* platform;
        QVector<Ball*> balls;
        QVector<Block*> borders;
        QVector<Block*> blocks;
        QVector<EditorBlock*> editorBlocks;
        QTimer animationTimer;

        QString levelName;
        int score;
        QTime time;
        int lifes;
        bool isInGame;
        void calculateCollide(SceneObject* main, SceneObject* secondary);
};

#endif // SCENE_H
