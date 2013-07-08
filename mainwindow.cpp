#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), scene( new Scene(1024, 768, this)), view (new QGraphicsView)
{
//    resize(1024, 768);
//    QPalette pal;
//    pal.setColor(backgroundRole(), QColor(Qt::black));
//    pal.setColor(QPalette::WindowText, QColor(Qt::white));
//    setPalette(pal);

//    logo->setFont(QFont("Courier", 50, QFont::Bold));
//    logo->setGeometry(width()/2-160, height()/5, 320, 50);

//    initMainMenu();
    connect (scene, SIGNAL(quit()), this, SLOT(exit()));
    view->setRenderHints(QPainter::Antialiasing);
    view->setScene(scene);
    view->setViewport(this);
    view->show();
    view->fitInView(scene->sceneRect());
}


//void MainWindow::initGame(){
//    QGraphicsView* view = new QGraphicsView;
//    scene = new Scene(1024, 768, this);
//    view->setRenderHints(QPainter::Antialiasing);
//    view->setScene(scene);
//    view->setViewport(this);
//    delete mainMenu;
//    delete logo;
//    view->show();
//    scene->start();
//    view->fitInView(scene->sceneRect());
//}
//void MainWindow::settings(){
//    delete mainMenu;
//    settingsMenu = new Menu(this);
//    settingsMenu->setGeometry(width()/2-100, height()/5+100, 200, 200);
//    QLabel* lbl = new QLabel("Set definition", settingsMenu);


//    settingsMenu->show();
//}

//void MainWindow::level(){

//}
