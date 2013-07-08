#include <QtGui/QApplication>
#include <QWidget>
#include <QImage>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

   QObject::connect(&mainWindow, SIGNAL(quit()), &a, SLOT(quit()));
    return a.exec();
}
