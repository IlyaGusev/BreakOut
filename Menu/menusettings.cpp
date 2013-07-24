#include "menusettings.h"

MenuSettings::MenuSettings(QWidget *parent) :
    QWidget(parent)
{
    QPushButton* ex = new QPushButton("Return");

    connect(ex, SIGNAL(clicked()), this, SIGNAL(signalMain()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ex);
    setLayout(layout);
}
