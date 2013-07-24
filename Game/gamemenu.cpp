#include "gamemenu.h"

GameMenu::GameMenu(QWidget *parent) :
    QWidget(parent)
{
    setGeometry((1024-160)/2-50, 768/2-50, 100, 100);

    QPushButton* exit = new QPushButton("Exit");
    QPushButton* resume = new QPushButton("Resume");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(resume);
    layout->addWidget(exit);
    setLayout(layout);

    connect(exit, SIGNAL(clicked()), SIGNAL(signalMain()));
    connect(resume, SIGNAL(clicked()), SIGNAL(signalResume()));
}
