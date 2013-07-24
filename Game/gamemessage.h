#ifndef GAMEMESSAGE_H
#define GAMEMESSAGE_H

#include <QWidget>

class GameMessage : public QWidget
{
    Q_OBJECT
public:
    explicit GameMessage(QWidget *parent = 0);
    void send(QString);
private:
};

#endif // GAMEMESSAGE_H
