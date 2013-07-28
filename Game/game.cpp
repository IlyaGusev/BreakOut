#include "game.h"
Game::Game(QObject *parent) :
    Scene(1024, 768, parent),
    state(new GameState),
    field(new GameField(this)),
    menu(new GameMenu)
{
    addWidget(state);
    state->show();
    field->createPlatform(field->PLATFORM_WIDTH, field->PLATFORM_HEIGHT);
    field->createBorders();
    field->addBall(QRectF(field->platform->graphics->pos().x()+
                          field->PLATFORM_WIDTH/2-
                          field->BALL_RADIUS/2,
                          field->platform->graphics->pos().y()-field->BALL_RADIUS,
                          field->BALL_RADIUS,
                          field->BALL_RADIUS),
            QColor(Qt::red),
            QVector2D(0, 0));
    field->createBorders();
    field->loadLevel("Levels/1.lvl");
    field->start();
    field->BALL_SPEED = 2;
    field->PLATFORM_SPEED = 1.5;

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
                    field->platform->properties->setSpeed(QVector2D(-field->PLATFORM_SPEED, 0));
            }
        }
        break;
        case Qt::Key_Right:{
            if (!pe->isAutoRepeat()){
                field->platform->properties->setProperty("isMovingRight", true);
                if ((field->platform->properties->property("isMovingLeft")).toBool())
                    field->platform->properties->setSpeed(QVector2D(0, 0));
                else
                    field-> platform->properties->setSpeed(QVector2D(field->PLATFORM_SPEED, 0));
             }
        }
        break;
        case Qt::Key_Space:{
            foreach(Ball* bl, field->balls){
                if (bl->properties->getSpeed()==QVector2D(0,0)){
                    bl->properties->setSpeed(QVector2D(0, -field->BALL_SPEED));
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
                field->addBall(QRectF(field->platform->graphics->pos().x()+
                                      field->platform->graphics->boundingRect().width()/2-
                                      field->BALL_RADIUS/2,
                                      field->platform->graphics->pos().y()-
                                      field->BALL_RADIUS,
                                      field->BALL_RADIUS,
                                      field->BALL_RADIUS),
                        QColor(Qt::red),
                        QVector2D(0, -field->BALL_SPEED));
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
                    field->platform->properties->setSpeed(QVector2D(field->PLATFORM_SPEED, 0));
                else
                    field->platform->properties->setSpeed(QVector2D(0, 0));
            }
        }
        break;
        case Qt::Key_Right:{
            if (!pe->isAutoRepeat()){
                field->platform->properties->setProperty("isMovingRight", false);
                if ((field->platform->properties->property("isMovingLeft")).toBool())
                    field->platform->properties->setSpeed(QVector2D(-field->PLATFORM_SPEED, 0));
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
        ((RoundPlatform*)field->platform->graphics)->setRect(QRectF(0,0, field->PLATFORM_WIDTH, field->PLATFORM_HEIGHT));
        state->setLifes(state->getLifes()-1);
        field->addBall(QRectF(field->platform->graphics->pos().x()+
                              field->platform->graphics->boundingRect().width()/2-
                              field->BALL_RADIUS/2,
                              field->platform->graphics->pos().y()-
                              field->BALL_RADIUS,
                              field->BALL_RADIUS,
                              field->BALL_RADIUS),
                QColor(Qt::red),
                QVector2D(0, 0));

        field->BALL_SPEED = 2;
        field->PLATFORM_SPEED = 1.5;
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
    field->createPlatform(field->PLATFORM_WIDTH, field->PLATFORM_HEIGHT);
    field->createBorders();
    field->addBall(QRectF(field->platform->graphics->pos().x()+
                          field->PLATFORM_WIDTH/2-
                          field->BALL_RADIUS/2,
                          field->platform->graphics->pos().y()-
                          field->BALL_RADIUS,
                          field->BALL_RADIUS,
                          field->BALL_RADIUS),
            QColor(Qt::red),
            QVector2D(0, 0));
    field->createBorders();
    field->loadLevel("Levels/"+state->getLevel()+".lvl");
    field->start();
    field->BALL_SPEED = 2;
    field->PLATFORM_SPEED = 1.5;
}

void Game::slotResume(){
    field->start();
    menu->hide();
}

void Game::slotGameOver(){
    emit signalMain();
}
