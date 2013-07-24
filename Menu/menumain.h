#ifndef MENUMAIN_H
#define MENUMAIN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MenuMain : public QWidget
{
    Q_OBJECT
public:
    explicit MenuMain(QWidget *parent = 0);
signals:
    void signalGame();
    void signalEditor();
    void signalSettings();
    void signalExit();
};

#endif // MENUMAIN_H
