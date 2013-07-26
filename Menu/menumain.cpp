#include "menumain.h"

MenuMain::MenuMain(QWidget *parent) :
    QWidget(parent)
{
    QPushButton* ng = new QPushButton("New Game");
    QPushButton* le = new QPushButton("Level Editor");
    QPushButton* st = new QPushButton("Settings");
    QPushButton* ex = new QPushButton("Exit");

    connect(ng, SIGNAL(clicked()), this, SIGNAL(signalGame()));
    connect(le, SIGNAL(clicked()), this, SIGNAL(signalEditor()));
    connect(st, SIGNAL(clicked()), this, SIGNAL(signalSettings()));
    connect(ex, SIGNAL(clicked()), this, SIGNAL(signalExit()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ng);
    layout->addWidget(le);
    layout->addWidget(st);
    layout->addWidget(ex);
    setLayout(layout);

    setStyleSheet(QString("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(54, 54, 54, 255));")+
                  QString("\nQPushButton {")+
                  QString("color: rgb(0, 156, 0);")+
                  QString("background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(43, 43, 43, 255), stop:1 rgba(101, 101, 101, 255));")+
                  QString("border-color: rgb(50, 50, 50)}")
                  );
}
