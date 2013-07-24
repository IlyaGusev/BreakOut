#include "gamestate.h"

GameState::GameState(QWidget *parent) :
    QWidget(parent),
    level("1"),
    score(0),
    lifes(3),
    lvlLbl(nullptr),
    scoreLbl(nullptr),
    lifesLbl(nullptr),
    scoreWgt(nullptr),
    lifesWgt(nullptr),
    layout(nullptr)
{
    setGeometry(1024-145, 50, 140, 250);
    update();
}

void GameState::setScore(int _score){
    score = _score;
    update();
}

void GameState::setLifes(int _lifes){
    lifes = _lifes;
    update();
}

void GameState::setLevel(QString _level){
    level = _level;
    update();
}

int GameState::getScore() const{
    return score;
}

int GameState::getLifes() const{
    return lifes;
}

QString GameState::getLevel() const{
    return level;
}

void GameState::update(){
    if (lvlLbl!=nullptr){
        lvlLbl->deleteLater();
        scoreLbl->deleteLater();
        lifesLbl->deleteLater();
        scoreWgt->deleteLater();
        lifesWgt->deleteLater();
    }

    lvlLbl = new QLabel("Level: "+level);
    scoreLbl = new QLabel("Score: ");
    lifesLbl = new QLabel("Lifes: ");
    scoreWgt = new QLCDNumber(6);
    lifesWgt = new QLCDNumber(6);

    scoreWgt->display(score);
    lifesWgt->display(lifes);

    if (layout==nullptr)
        layout = new QVBoxLayout;
    layout->addWidget(lvlLbl);
    layout->addWidget(scoreLbl);
    layout->addWidget(scoreWgt);
    layout->addWidget(lifesLbl);
    layout->addWidget(lifesWgt);
    setLayout(layout);
}
