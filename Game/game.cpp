#include "game.h"
Game::Game(QObject *parent) :
    Scene(1024, 768, parent),
    state(new GameState),
    field(new GameField(this)),
    menu(new GameMenu)
{
    this->addWidget(state);
    state->show();

    field->createPlatform(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    field->createBorders();
    field->addBall(QRectF(field->platform->graphics->pos().x()+PLATFORM_WIDTH/2-BALL_RADIUS/2,
                   field->platform->graphics->pos().y()-BALL_RADIUS,
                   BALL_RADIUS,
                   BALL_RADIUS),
            QColor(Qt::red),
            QVector2D(0, 0));
    field->createBorders();
    field->loadLevel("Levels/1.lvl");
    field->start();

    this->addWidget(menu);
    menu->hide();

    connect(field, SIGNAL(signalBlockDestroyed()), this, SLOT(slotBlockDestroyed()));
    connect(field, SIGNAL(signalBallLost()), this, SLOT(slotBallLost()));
    connect(field, SIGNAL(signalLevelFinished()), this, SLOT(slotLevelFinished()));
    connect(menu, SIGNAL(signalMain()), this, SIGNAL(signalMain()));
    connect(menu, SIGNAL(signalResume()), this, SLOT(slotResume()));
}

Game::~Game(){
    if (state!=nullptr)
        state->deleteLater();
    if (field!=nullptr)
        field->deleteLater();
    if (menu!=nullptr)
        menu->deleteLater();
}

void Game::keyPressEvent(QKeyEvent * pe){
    switch (pe->key()){
        case Qt::Key_Left:{
            if (!pe->isAutoRepeat()){
                field->platform->properties->setProperty("isMovingLeft", true);
                if ((field->platform->properties->property("isMovingRight")).toBool())
                    field->platform->properties->setSpeed(QVector2D(0, 0));
                else
                    field->platform->properties->setSpeed(QVector2D(-PLATFORM_SPEED, 0));
            }
        }
        break;
        case Qt::Key_Right:{
            if (!pe->isAutoRepeat()){
                field->platform->properties->setProperty("isMovingRight", true);
                if ((field->platform->properties->property("isMovingLeft")).toBool())
                    field->platform->properties->setSpeed(QVector2D(0, 0));
                else
                    field-> platform->properties->setSpeed(QVector2D(PLATFORM_SPEED, 0));
             }
        }
        break;
        case Qt::Key_Space:{
            foreach(Ball* bl, field->balls){
                if (bl->properties->getSpeed()==QVector2D(0,0)){
                    bl->properties->setSpeed(QVector2D(0, -BALL_SPEED));
                }
            }
        }
        break;
        case Qt::Key_Escape:{
            if (!pe->isAutoRepeat()){
                if (menu->isHidden() && field->anitimer.isActive()){
                    field->stop();
                    menu->show();
                }
                else
                if ((!menu->isHidden()) && (!field->anitimer.isActive())){
                    field->start();
                    menu->hide();
                }
            }
        }
        break;
        case Qt::Key_B:{
            if (!pe->isAutoRepeat()){
                field->addBall(QRectF(field->platform->graphics->pos().x()+PLATFORM_WIDTH/2-BALL_RADIUS/2,
                               field->platform->graphics->pos().y()-BALL_RADIUS,
                               BALL_RADIUS,
                               BALL_RADIUS),
                           QColor(Qt::red),
                           QVector2D(0, -BALL_SPEED));
            }
        }
        break;
        default:
            QGraphicsScene::keyPressEvent(pe);
        break;
    }
}

void Game::keyReleaseEvent(QKeyEvent * pe){
    switch (pe->key()){
        case Qt::Key_Left:{
            if (!pe->isAutoRepeat()){
                field->platform->properties->setProperty("isMovingLeft", false);
                if ((field->platform->properties->property("isMovingRight")).toBool())
                    field->platform->properties->setSpeed(QVector2D(PLATFORM_SPEED, 0));
                else
                    field->platform->properties->setSpeed(QVector2D(0, 0));
            }
        }
        break;
        case Qt::Key_Right:{
            if (!pe->isAutoRepeat()){
                field->platform->properties->setProperty("isMovingRight", false);
                if ((field->platform->properties->property("isMovingLeft")).toBool())
                    field->platform->properties->setSpeed(QVector2D(-PLATFORM_SPEED, 0));
                else
                    field->platform->properties->setSpeed(QVector2D(0, 0));
            }
        }
        break;
        default:
            QGraphicsScene::keyReleaseEvent(pe);
        break;
    }
}

void Game::slotBallLost(){
    if (state->getLifes()!=0){
        state->setLifes(state->getLifes()-1);
        field->addBall(QRectF(field->platform->graphics->pos().x()+PLATFORM_WIDTH/2-BALL_RADIUS/2,
                       field->platform->graphics->pos().y()-BALL_RADIUS,
                       BALL_RADIUS,
                       BALL_RADIUS),
                QColor(Qt::red),
                QVector2D(0, 0));
    }
    else{
        field->stop();
        QTimer::singleShot(1000, this, SLOT(slotGameOver()));
    }
}

void Game::slotBlockDestroyed(){
    state->setScore(state->getScore()+100);
}

void Game::slotLevelFinished(){
    state->setLevel(QString((((char)((state->getLevel().toInt())+1))+'0')));

    field->clear();
    field->createPlatform(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    field->createBorders();
    field->addBall(QRectF(field->platform->graphics->pos().x()+PLATFORM_WIDTH/2-BALL_RADIUS/2,
                   field->platform->graphics->pos().y()-BALL_RADIUS,
                   BALL_RADIUS,
                   BALL_RADIUS),
            QColor(Qt::red),
            QVector2D(0, 0));
    field->createBorders();
    field->loadLevel("Levels/"+state->getLevel()+".lvl");
    field->start();
}

void Game::slotResume(){
    field->start();
    menu->hide();
}

void Game::slotGameOver(){
    emit signalMain();
}
