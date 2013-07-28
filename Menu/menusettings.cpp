#include "menusettings.h"

MenuSettings::MenuSettings(QWidget *parent) :
    QWidget(parent)
{
    QPushButton* ms = new QPushButton("Music On/Off");
    QPushButton* ex = new QPushButton("Return");

    connect(ex, SIGNAL(clicked()), this, SIGNAL(signalMain()));
    connect(ms, SIGNAL(clicked()), this, SIGNAL(signalMusic()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ms);
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
