#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MenuSettings : public QWidget
{
    Q_OBJECT
public:
    explicit MenuSettings(QWidget *parent = 0);
signals:
    void signalMain();
public slots:
    
};

#endif // MENUSETTINGS_H
