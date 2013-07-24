#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class GameMenu : public QWidget
{
    Q_OBJECT
public:
    explicit GameMenu(QWidget *parent = 0);
signals:
    void signalMain();
    void signalResume();
};

#endif // GAMEMENU_H
