#ifndef MENU_H
#define MENU_H

#include "scene.h"
#include "menumain.h"
#include "menusettings.h"

class Menu : public Scene
{
    Q_OBJECT
public:
    explicit Menu(QObject *parent = 0);
signals:
    void signalExit();
    void signalGame();
    void signalEditor();
public slots:
    void slotMain();
    void slotSettings();
private:
    MenuMain* main;
    MenuSettings* settings;
};

#endif // MENU_H
