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
}
