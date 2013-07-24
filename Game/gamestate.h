#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QVBoxLayout>

class GameState : public QWidget
{
    Q_OBJECT
public:
    explicit GameState(QWidget *parent = 0);
    void setScore(int);
    void setLifes(int);
    void setLevel(QString);
    int getScore() const;
    int getLifes() const;
    QString getLevel() const;
private:
    void update();
private:
    QString level;
    int score;
    int lifes;
    QLabel* lvlLbl;
    QLabel* scoreLbl;
    QLabel* lifesLbl;
    QLCDNumber* scoreWgt;
    QLCDNumber* lifesWgt;
    QVBoxLayout* layout;
};

#endif // GAMESTATE_H
