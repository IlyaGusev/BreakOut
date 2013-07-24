#include "gamefield.h"
#include <QDebug>

GameField::GameField(QGraphicsScene* sc, QObject *parent) :
    QObject(parent),
    platform(nullptr),
    balls(),
    blocks(),
    scene(sc),
    borders(),
    anitimer(this)
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
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setPos(rect.x(), rect.y());
    balls.back()->properties->setSpeed(vect);
    scene->addItem(balls.back()->graphics);
}

void GameField::addBlock(QRectF rect, QColor clr){
    blocks.push_back(new Block);
    ((QGraphicsRectItem*)blocks.back()->graphics)->setPen(QPen(Qt::black));
    ((QGraphicsRectItem*)blocks.back()->graphics)->setBrush(QBrush(clr));
    ((QGraphicsRectItem*)blocks.back()->graphics)->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsRectItem*)blocks.back()->graphics)->setPos(rect.x(), rect.y());
    blocks.back()->properties->setDestroyable(true);
    scene->addItem(blocks.back()->graphics);
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
                addBlock(QRectF(x,y,width,height), QColor(Qt::GlobalColor(color)));;
            }
            if (str=="color"){
                stream>>str;
                int index = str.toInt();
                stream>>str;
                int color = str.toInt();
                if (index<blocks.size())
                    ((QGraphicsRectItem*)blocks[index]->graphics)->setBrush(QColor(Qt::GlobalColor(color)));
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
}


void GameField::start(){
    anitimer.start(ANITIMER_STEP);
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
                                           PLATFORM_WIDTH-BORDER_DEPTH-
                                           GAME_STATS_WIDTH)
            platform->graphics->setPos(platform->graphics->pos().x()+
                                       platform->properties->getSpeed().x(),
                                       platform->graphics->pos().y()+
                                       platform->properties->getSpeed().y());
    for (int i=0; i<balls.size(); i++){
        if (balls[i]->properties->getSpeed()==QVector2D(0,0))
            balls[i]->graphics->setPos(platform->graphics->pos().x()+
                                       PLATFORM_WIDTH/2-BALL_RADIUS/2,
                                       platform->graphics->pos().y()
                                       -BALL_RADIUS);
        else
            balls[i]->graphics->setPos(balls[i]->graphics->pos().x()+
                                       balls[i]->properties->getSpeed().x(),
                                       balls[i]->graphics->pos().y()+
                                       balls[i]->properties->getSpeed().y());
    }
    //Collides
    for (int i=0; i<balls.size(); i++){
        QPointF intersection(0,0);
        if (balls[i]->collidesWithItem(platform, &intersection)){
            calculateCollide(balls[i], platform, &intersection);
        }
        for (int j=1; j<borders.size(); j++){
            if (balls[i]->collidesWithItem(borders[j], &intersection)){
                calculateCollide(balls[i], borders[j], &intersection);
            }
        }
        for (int j=0; j<balls.size(); j++){
            if (i!=j)
            if (balls[i]->collidesWithItem(balls[j], &intersection))
                calculateCollide(balls[i], balls[j], &intersection);
        }
        for (int j=0; j<blocks.size(); j++){
            if (balls[i]->collidesWithItem(blocks[j], &intersection)){
                calculateCollide(balls[i], blocks[j], &intersection);
                if (blocks[j]->properties->isDestroyable()){
                    delete blocks[j];
                    blocks.erase(blocks.begin()+j);
                    emit signalBlockDestroyed();
                    if (blocks.isEmpty()){
                        stop();
                        QTimer::singleShot(2000, this, SIGNAL(signalLevelFinished()));
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
    double temp = tangent.y()/tangent.length();

    double alpha;
    if (temp<=1.0000001 && temp>=0.9999999)         alpha = M_PI/2;
    else if (temp>=-1.0000001 && temp<=-0.9999999)  alpha = -M_PI/2;
    else                                            alpha = asin(temp);

    QVector2D static_speed ((speedX*cos(2*alpha)+speedY*sin(2*alpha)),
                            (speedX*sin(2*alpha)-speedY*cos(2*alpha)));
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
