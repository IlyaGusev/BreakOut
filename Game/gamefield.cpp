#include "gamefield.h"
#include <QDebug>

GameField::GameField(QGraphicsScene* sc, QObject *parent) :
    QObject(parent),
    PLATFORM_SPEED(1.5),
    BALL_SPEED(2.0),
    platform(nullptr),
    balls(),
    blocks(),
    anitimer(this),
    scene(sc),
    borders()
{
    connect(&anitimer, SIGNAL(timeout()), this, SLOT(nextTick()));
}

GameField::~GameField(){
    if (platform!=nullptr){
        delete platform->properties;
        platform = nullptr;
    }
    foreach (Ball* b, balls){
        delete b->properties;
    }
    balls.clear();
    foreach (Block* b, blocks){
        delete b->properties;
    }
    blocks.clear();
    foreach (Block* b, borders){
        delete b->properties;
    }
    borders.clear();
    foreach (Bonus* b, bonuses){
        delete b->properties;
    }
    bonuses.clear();
}

void GameField::createPlatform(int width, int height){
    if (platform==0){
        platform=new Platform;
        ((RoundPlatform*)platform->graphics)->setPen(QPen(Qt::black));
        ((RoundPlatform*)platform->graphics)->setBrush(QBrush(Qt::green));
        ((RoundPlatform*)platform->graphics)->setRect(QRectF(0, 0, width, height));
        ((RoundPlatform*)platform->graphics)->setPos((1024-GAME_STATS_WIDTH)/2-width/2, 768-height*2);
        platform->properties->setProperty("isMovingLeft", false);
        platform->properties->setProperty("isMovingRight", false);
        scene->addItem(platform->graphics);
    }
}

void GameField::createBorders(){
    if (borders.isEmpty()){
        for (int i=0; i<4; i++){
            borders.push_back(new Block);
            ((QGraphicsRectItem*)borders[i]->graphics)->setPen(QPen(Qt::black));
            ((QGraphicsRectItem*)borders[i]->graphics)->setBrush(QBrush(Qt::gray));
            scene->addItem(borders.back()->graphics);
        }
        ((QGraphicsRectItem*)borders[0]->graphics)->setRect(0, 0, 1024-GAME_STATS_WIDTH, 1);
        ((QGraphicsRectItem*)borders[0]->graphics)->setPos(0, 767);
        ((QGraphicsRectItem*)borders[1]->graphics)->setRect(0, 0, 10, 768);
        ((QGraphicsRectItem*)borders[2]->graphics)->setRect(0, 0, 1024-GAME_STATS_WIDTH, 10);
        ((QGraphicsRectItem*)borders[3]->graphics)->setRect(0, 0, 10, 768);
        ((QGraphicsRectItem*)borders[3]->graphics)->setPos(1024-GAME_STATS_WIDTH-BORDER_DEPTH, 0);
        borders[0]->graphics->hide();
    }
}

void GameField::addBall(QRectF rect, QColor clr, QVector2D vect){
    balls.push_back(new Ball);
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setPen(QPen(Qt::black));
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setBrush(QBrush(clr));
//    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setBrush(QBrush(QImage(":/images/ball1.jpg")));
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setPos(rect.x(), rect.y());
    balls.back()->properties->setSpeed(vect);
    scene->addItem(balls.back()->graphics);
    balls.back()->properties->setProperty("isFired", false);
}

void GameField::addBlock(QRectF rect, QColor clr, BlockType type){
    blocks.push_back(new Block);
    ((QGraphicsRectItem*)blocks.back()->graphics)->setPen(QPen(Qt::black));
    ((QGraphicsRectItem*)blocks.back()->graphics)->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsRectItem*)blocks.back()->graphics)->setPos(rect.x(), rect.y());

    if (type == STANDART){
        blocks.back()->properties->setProperty("isDestroyable", true);
        blocks.back()->properties->setProperty("isBonus", false);
        ((QGraphicsRectItem*)blocks.back()->graphics)->setBrush(QBrush(clr));
    }else
    if (type == BONUS){
        blocks.back()->properties->setProperty("isDestroyable", true);
        blocks.back()->properties->setProperty("isBonus", true);
        ((QGraphicsRectItem*)blocks.back()->graphics)->setBrush(QBrush(clr, Qt::Dense1Pattern));
    }else
    if (type == UNDESTR){
        blocks.back()->properties->setProperty("isDestroyable", false);
        blocks.back()->properties->setProperty("isBonus", false);
        ((QGraphicsRectItem*)blocks.back()->graphics)->setBrush(QBrush(clr, Qt::Dense3Pattern));
    }
    scene->addItem(blocks.back()->graphics);
}

void GameField::addBonus(QRectF rect, Bonus::BonusType type){
    bonuses.push_back(new Bonus(type));
    ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setPen(QPen(Qt::black));
    ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setPos(rect.x(), rect.y());
    bonuses.back()->properties->setSpeed(QVector2D(0, 1.5));
    if (type == Bonus::PLATFORM_EXTEND){
        ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setBrush(QBrush(Qt::green));
    }
    if (type == Bonus::BALL_ACCELERATION){
        ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setBrush(QBrush(Qt::red));
    }
    if (type == Bonus::PLATFORM_ACCELERATION){
        ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setBrush(QBrush(Qt::blue));
    }
    if (type == Bonus::FIREBALL){
        ((QGraphicsEllipseItem*)(bonuses.back()->graphics))->setBrush(QBrush(Qt::yellow));
    }
    scene->addItem(bonuses.back()->graphics);
}

void GameField::loadLevel(QString name){
    QFile file(name);
    if (file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QString str;
        while(!stream.atEnd()){
            stream>>str;
            if (str=="addblock"){
                stream>>str;
                double x = str.toDouble();
                stream>>str;
                double y = str.toDouble();
                stream>>str;
                double width = str.toDouble();
                stream>>str;
                double height = str.toDouble();
                stream>>str;
                int color = str.toInt();
                stream>>str;
                int type = str.toInt();
                addBlock(QRectF(x,y,width,height), QColor(Qt::GlobalColor(color)), BlockType(type));;
            }
        }
        file.close();
    }
}

void GameField::clear(){
    if (platform!=nullptr){
        delete platform;
        platform = nullptr;
    }
    foreach (Ball* b, balls){
        delete b;
    }
    balls.clear();
    foreach (Block* b, blocks){
        delete b;
    }
    blocks.clear();
    foreach (Block* b, borders){
        delete b;
    }
    borders.clear();
    foreach (Bonus* b, bonuses){
        delete b;
    }
    bonuses.clear();
}


void GameField::start(){
    anitimer.start(3);
}

void GameField::stop(){
    anitimer.stop();
}

void GameField::nextTick(){
    //Moves

    if ((platform->properties->property("isMovingLeft")).toBool())
        if (platform->graphics->pos().x()>=BORDER_DEPTH)
            platform->graphics->setPos(platform->graphics->pos().x()+
                                       platform->properties->getSpeed().x(),
                                       platform->graphics->pos().y()+
                                       platform->properties->getSpeed().y());
    if ((platform->properties->property("isMovingRight")).toBool())
        if (platform->graphics->pos().x()<=1024-
                                           platform->graphics->boundingRect().width()-
                                           BORDER_DEPTH-
                                           GAME_STATS_WIDTH)
            platform->graphics->setPos(platform->graphics->pos().x()+
                                       platform->properties->getSpeed().x(),
                                       platform->graphics->pos().y()+
                                       platform->properties->getSpeed().y());
    for (int i=0; i<balls.size(); i++){
        if (balls[i]->properties->getSpeed()==QVector2D(0,0))
            balls[i]->graphics->setPos(platform->graphics->pos().x()+
                                       platform->graphics->boundingRect().width()/2-
                                       BALL_RADIUS/2,
                                       platform->graphics->pos().y()-
                                       BALL_RADIUS);
        else
            balls[i]->graphics->setPos(balls[i]->graphics->pos().x()+
                                       balls[i]->properties->getSpeed().x(),
                                       balls[i]->graphics->pos().y()+
                                       balls[i]->properties->getSpeed().y());
    }
    for (int i=0; i<bonuses.size(); i++){
        bonuses[i]->graphics->setPos(bonuses[i]->graphics->pos().x()+
                                   bonuses[i]->properties->getSpeed().x(),
                                   bonuses[i]->graphics->pos().y()+
                                   bonuses[i]->properties->getSpeed().y());
    }
    //Collides
    for (int i=0; i<balls.size(); i++){
        QPointF intersection(0,0);
        QList<QGraphicsItem*> list = balls[i]->graphics->collidingItems();
        foreach(QGraphicsItem* it, list)
        {
            bool calculated = false;
            for (int j=0; j<balls.size(); j++){
                if (i!=j){
                    if (it==((QGraphicsItem*)balls[j]->graphics)){
                        balls[i]->collidesWithItem(balls[j], &intersection);
                        calculateCollide(balls[i], balls[j], &intersection);
                        calculated = true;
                        break;
                    }
                }
            }
            if (calculated==false)
                for (int j=1; j<borders.size(); j++){
                    if (it==((QGraphicsItem*)borders[j]->graphics)){
                        balls[i]->collidesWithItem(borders[j], &intersection);
                        calculateCollide(balls[i], borders[j], &intersection);
                        calculated = true;
                        break;
                    }
                }
            if (calculated==false)
                if (it==((QGraphicsItem*)platform->graphics)){
                    balls[i]->collidesWithItem(platform, &intersection);
                    calculateCollide(balls[i], platform, &intersection);
                    calculated = true;
                    continue;
                }
            if (calculated==false){
                for (int j=0; j<blocks.size(); j++){
                    if (it==((QGraphicsItem*)blocks[j]->graphics)){
                        balls[i]->collidesWithItem(blocks[j], &intersection);
                        if (!blocks[j]->properties->property("isDestroyable").toBool())
                            calculateCollide(balls[i], blocks[j], &intersection);
                        else if (!balls[i]->properties->property("isFired").toBool())
                            calculateCollide(balls[i], blocks[j], &intersection);
                        if (blocks[j]->properties->property("isDestroyable").toBool()){
                            if (blocks[j]->properties->property("isBonus").toBool()){
                                int BONUS_WIDTH = 40;
                                int BONUS_HEIGHT = 30;
                                qsrand(QTime::currentTime().msec());
                                int t = qrand()%4;
                                addBonus(QRectF(blocks[j]->graphics->pos().x()+
                                                blocks[j]->graphics->boundingRect().width()/2-BONUS_WIDTH/2,
                                                blocks[j]->graphics->pos().y()+
                                                blocks[j]->graphics->boundingRect().height()/2,
                                                BONUS_WIDTH,
                                                BONUS_HEIGHT),
                                         Bonus::BonusType(t));
                            }
                            delete blocks[j];
                            blocks.erase(blocks.begin()+j);
                            emit signalBlockDestroyed();

                            bool isFinished = true;
                            for (int j=0; j<blocks.size(); j++){
                                if (blocks[j]->properties->property("isBonus").toBool() || blocks[j]->properties->property("isDestroyable").toBool()){
                                    isFinished = false;
                                    break;
                                }
                            }
                            if (isFinished){
                                stop();
                                QTimer::singleShot(500, this, SIGNAL(signalLevelFinished()));
                            }
                        }
                        calculated = true;
                        break;
                    }
                }

            }
        }
        if (balls[i]->graphics->collidesWithItem(borders[0]->graphics)){
            delete balls[i];
            balls.erase(balls.begin()+i);
            if (balls.isEmpty())
                emit signalBallLost();
            continue;
        }
    }

    for (int i=0; i<bonuses.size(); i++){
        QList<QGraphicsItem*> list = bonuses[i]->graphics->collidingItems();
        bool calculated = false;
        foreach(QGraphicsItem* it, list)
        {
            if (it==((QGraphicsItem*)platform->graphics)){
                if (bonuses[i]->type()==Bonus::PLATFORM_EXTEND){
                    int current_width = ((RoundPlatform*)platform->graphics)->boundingRect().width();
                    if (current_width<300){
                        ((RoundPlatform*)platform->graphics)->setRect(QRectF(0,0, current_width+20, PLATFORM_HEIGHT));
                        ((RoundPlatform*)platform->graphics)->setPos(platform->graphics->pos().x()-10, platform->graphics->pos().y());
                    }
                }
                if (bonuses[i]->type()==Bonus::PLATFORM_ACCELERATION){
                    if (PLATFORM_SPEED<3){
                        PLATFORM_SPEED+=0.2;
                    }
                }
                if (bonuses[i]->type()==Bonus::PLATFORM_ACCELERATION){
                    if (PLATFORM_SPEED<3){
                        PLATFORM_SPEED+=0.2;
                    }
                }
                if (bonuses[i]->type()==Bonus::BALL_ACCELERATION){
                    if (BALL_SPEED<4){
                        BALL_SPEED+=0.2;
                    }
                }
                if (bonuses[i]->type()==Bonus::FIREBALL){
                    for (int i=0; i<balls.size(); i++){
                        ((QGraphicsEllipseItem*)(balls[i]->graphics))->setBrush(QBrush(Qt::yellow));
                        balls[i]->properties->setProperty("isFired", true);
                    }
                }
                delete bonuses[i];
                bonuses.erase(bonuses.begin()+i);
                calculated = true;
                break;
            }
        }
        if (calculated) continue;
        if (bonuses[i]->graphics->collidesWithItem(borders[0]->graphics)){
            delete bonuses[i];
            bonuses.erase(bonuses.begin()+i);
        }
    }
}

void GameField::calculateCollide(GameObject* main, GameObject* secondary, QPointF* intersection){
    *intersection+=main->graphics->scenePos();

    //Static part
    double posX = main->graphics->pos().x();
    double posY = main->graphics->pos().y();
    double centerX = posX + (double)BALL_RADIUS/2;
    double centerY = posY + (double)BALL_RADIUS/2;
    double speedX = main->properties->getSpeed().x();
    double speedY = main->properties->getSpeed().y();
    QVector2D normal(intersection->x()-centerX, intersection->y()-centerY);
    QVector2D tangent(normal.y(), -normal.x());
    if (tangent.y()<0)
        tangent = QVector2D(-tangent.x(), -tangent.y());
    double temp = tangent.y()/tangent.length();

    double alpha;
    if (temp<=1.0000001 && temp>=0.9999999)         alpha = M_PI/2;
    else if (temp>=-1.0000001 && temp<=-0.9999999)  alpha = -M_PI/2;
    else                                            alpha = asin(temp);

    if (tangent.x()<0)
        alpha=M_PI-alpha;

    QVector2D static_speed ((speedX*cos(2*alpha)+speedY*sin(2*alpha)),
                            (speedX*sin(2*alpha)-speedY*cos(2*alpha)));
    static_speed.normalize();
    static_speed*=BALL_SPEED;
    main->properties->setSpeed(static_speed);

    //Dynamic part
    normal=-normal;
    double cos_alpha = normal.x()/normal.length();
    double sin_alpha = normal.y()/normal.length();
    double dynamic_speed_length = (secondary->properties->getSpeed().x()*cos_alpha+
                                   secondary->properties->getSpeed().y()*sin_alpha);
    if (dynamic_speed_length<0) dynamic_speed_length = -dynamic_speed_length;

    QVector2D dynamic_speed ((dynamic_speed_length * cos_alpha),
                             (dynamic_speed_length * sin_alpha));
    if (!(dynamic_speed.x()>=-0.00001 && dynamic_speed.x()<=0.00001 &&
        dynamic_speed.y()>=-0.00001 && dynamic_speed.y()<=0.00001)){
        dynamic_speed.normalize();
        dynamic_speed*=BALL_SPEED;
        main->properties->setSpeed(dynamic_speed);
    }
}
