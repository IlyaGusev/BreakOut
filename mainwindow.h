#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <phonon>
#include "Game/game.h"
#include "Menu/menu.h"
#include "Editor/editor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
signals:
    void quit();
public slots:
    void exit(){ emit quit(); }
    void openGame();
    void openEditor();
    void openMain();
    void slotRepeat();
    void slotMusic();
private:
    Phonon::MediaObject *music;
    Scene* scene;
    QGraphicsView* view;
    void setupView();
};

#endif // MAINWINDOW_H
