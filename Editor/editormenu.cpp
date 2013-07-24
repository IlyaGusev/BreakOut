#include "editormenu.h"

EditorMenu::EditorMenu(QWidget *parent) :
    QWidget(parent)
{
    le = new QLineEdit;
    QPushButton* sv = new QPushButton("Save");
    QPushButton* ex = new QPushButton("Exit");

    connect(sv, SIGNAL(clicked()), SLOT(slotEmitSave()));
    connect(ex, SIGNAL(clicked()), this, SIGNAL(signalMain()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(le);
    layout->addWidget(sv);
    layout->addWidget(ex);
    setLayout(layout);
}

void EditorMenu::slotEmitSave(){
    emit signalSave(le->displayText());
}
