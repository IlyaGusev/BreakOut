#include "editormenu.h"

EditorMenu::EditorMenu(QWidget *parent) :
    QWidget(parent)
{
    le = new QLineEdit;
    QPushButton* sv = new QPushButton("Save");
    QPushButton* ld = new QPushButton("Load");
    QPushButton* ex = new QPushButton("Exit");

    connect(sv, SIGNAL(clicked()), SLOT(slotEmitSave()));
    connect(ex, SIGNAL(clicked()), this, SIGNAL(signalMain()));
    connect(ld, SIGNAL(clicked()), this, SLOT(slotEmitLoad()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(le);
    layout->addWidget(sv);
    layout->addWidget(ld);
    layout->addWidget(ex);
    setLayout(layout);
}

void EditorMenu::slotEmitSave(){
    emit signalSave(le->displayText());
}

void EditorMenu::slotEmitLoad(){
    emit signalLoad(le->displayText());
}
