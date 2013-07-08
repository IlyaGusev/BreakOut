#include "menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent), layout(new QVBoxLayout),
    buttons(), sliders()
{
//    setFixedSize(1024, 768);
//    logo->setFont(QFont("Courier", 50, QFont::Bold));
//    logo->setGeometry(width()/2-160, height()/5, 320, 50);


//    QObject::connect(buttons[0], SIGNAL(clicked()), parent, SLOT(init()));
//    QObject::connect(buttons[1], SIGNAL(clicked()), parent,  SLOT(exit()));
//    QObject::connect(buttons[2], SIGNAL(clicked()), parent, SLOT(settings()));

    setLayout(layout);
}

QAbstractButton* Menu::addButton(QString str){
    buttons.push_back(new QPushButton(str));
    layout->addWidget(buttons.back());
    return buttons.back();
}

QSlider* Menu::addSlider(){
    sliders.push_back(new QSlider);
    layout->addWidget(sliders.back());
    return sliders.back();
}

void Menu::paintEvent(QPaintEvent * pe)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
 }
