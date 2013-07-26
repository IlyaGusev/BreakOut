#ifndef GAME_H
#define GAME_H

#include <QKeyEvent>

#include "scene.h"
#include "gamestate.h"
#include "gamefield.h"
#include "gamemenu.h"

class Game : public Scene
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    ~Game();
    void start();
    void stop();
signals:
    void signalMain();
private slots:
    void slotBlockDestroyed();
    void slotLevelFinished();
    void slotBallLost();
    void slotResume();
    void slotGameOver();
protected:
    void keyPressEvent(QKeyEvent * pe);
    void keyReleaseEvent(QKeyEvent * pe);
private:
    GameState*   state;
    GameField*   field;
    GameMenu*    menu;
};

#endif // GAME_H
