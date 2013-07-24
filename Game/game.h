#ifndef GAME_H
#define GAME_H

#include <QKeyEvent>

#include "scene.h"
#include "gamestate.h"
#include "gamefield.h"
#include "gamemenu.h"
#include "gamemessage.h"

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
protected:
    void keyPressEvent(QKeyEvent * pe);
    void keyReleaseEvent(QKeyEvent * pe);
private:
    GameState*   state;
    GameField*   field;
    GameMenu*    menu;
    GameMessage* message;
};

#endif // GAME_H
