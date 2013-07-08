#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "scene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = 0);
    signals:
        void quit();
    public slots:
        void exit(){ emit quit(); }
    private:
        Scene* scene;
        QGraphicsView* view;
};

#endif // MAINWINDOW_H
