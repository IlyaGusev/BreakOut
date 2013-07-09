#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), scene( new Scene(1024, 768, this)), view (new QGraphicsView)
{
//    logo->setFont(QFont("Courier", 50, QFont::Bold));
//    logo->setGeometry(width()/2-160, height()/5, 320, 50);

    connect (scene, SIGNAL(quit()), this, SLOT(exit()));
    view->setRenderHints(QPainter::Antialiasing);
    view->setScene(scene);
    view->setViewport(this);
    view->show();
    view->fitInView(scene->sceneRect());
}
