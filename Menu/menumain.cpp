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

    setStyleSheet("QWidget{background-color: rgba(0, 0, 0, 30%);}"
                  "QPushButton {"
                  "height : 30 px;"
                  "color: rgb(0, 170, 255);\n"
                  "border : 0 px;"
                  "background-image: url(:/images/button.png);\n"
                  "background-repeat: no-repeat;"
                  "background-position: center center;"
                  "background-color: rgba(0, 0, 0, 0%);"
                  "font: 75 11pt \"Century Schoolbook L\";"
                  "selection-color: rgb(26, 26, 26); "
                  "selection-background-color: rgb(143, 237, 255)}"
                  );
}
