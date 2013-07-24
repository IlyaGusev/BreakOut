#include "menu.h"

Menu::Menu(QObject *parent) :
    Scene(1024, 768, parent),
    main(new MenuMain),
    settings(new MenuSettings)
{
    addWidget(settings);
    settings->setGeometry(width()/2-100, height()/5+100, 200, 200);

    addWidget(main);
    main->setGeometry(width()/2-100, height()/5+100, 200, 200);

    slotMain();

    connect(main, SIGNAL(signalGame()), this, SIGNAL(signalGame()));
    connect(main, SIGNAL(signalEditor()), this, SIGNAL(signalEditor()));
    connect(main, SIGNAL(signalExit()), this, SIGNAL(signalExit()));
    connect(main, SIGNAL(signalSettings()), this, SLOT(slotSettings()));

    connect(settings, SIGNAL(signalMain()), this, SLOT(slotMain()));
}

void Menu::slotSettings(){
    main->hide();
    settings->show();
}

void Menu::slotMain(){
    settings->hide();
    main->show();
}
