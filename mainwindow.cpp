#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), scene(new Menu), view (new QGraphicsView)
{
    music = Phonon::createPlayer(Phonon::MusicCategory,
                                 Phonon::MediaSource(":/music/Fly12.mp3"));
    music->play();
    connect(music, SIGNAL(aboutToFinish()), this , SLOT(slotRepeat()));

    connect(scene, SIGNAL(signalGame()), this, SLOT(openGame()));
    connect(scene, SIGNAL(signalEditor()), this, SLOT(openEditor()));
    connect(scene, SIGNAL(signalExit()), this, SLOT(exit()));
    connect(scene, SIGNAL(signalMusic()), this, SLOT(slotMusic()));

    setupView();
}

void MainWindow::openGame(){
    scene->deleteLater();
    scene = new Game;

    connect (scene, SIGNAL(signalMain()), this, SLOT(openMain()));

    setupView();
}
void MainWindow::openEditor(){
    scene->deleteLater();
    scene = new Editor;

    connect (scene, SIGNAL(signalMain()), this, SLOT(openMain()));

    setupView();
}

void MainWindow::openMain(){
    scene->deleteLater();
    scene = new Menu;

    connect(scene, SIGNAL(signalGame()), this, SLOT(openGame()));
    connect(scene, SIGNAL(signalEditor()), this, SLOT(openEditor()));
    connect(scene, SIGNAL(signalMusic()), this, SLOT(slotMusic()));
    connect(scene, SIGNAL(signalExit()), this, SLOT(exit()));

    setupView();
}

void MainWindow::setupView(){
    view->setRenderHints(QPainter::Antialiasing);
    view->setScene(scene);
    view->setViewport(this);
    view->show();
    view->fitInView(scene->sceneRect());
}

void MainWindow::slotRepeat(){
    music->clearQueue();
    music->enqueue(Phonon::MediaSource(":/music/Fly12.mp3"));
}

void MainWindow::slotMusic(){
    if (music->state()==Phonon::StoppedState)
        music->play();
    else
        music->stop();
}
