#include "scene.h"
const int PLATFORM_WIDTH = 100;
const int PLATFORM_HEIGHT = 20;
const int BALL_WIDTH = 24;
const int BALL_HEIGHT = 24;
const int TIMER_STEP = 3;
const int BORDER_DEPTH = 10;
const int BLOCK_WIDTH = 100;
const int BLOCK_HEIGHT = 20;
const double BALL_SPEED = 2;
const double PLATFORM_SPEED = 1.5;

Scene::Scene(int width, int height, QObject* parent) :
    QGraphicsScene(0, 0, width, height, parent),
    mainMenu(nullptr),
    settingsMenu(nullptr),
    view (new QGraphicsView),
    platform(nullptr),
    balls(),
    borders(),
    blocks(),
    timer(this)
{
    initMainMenu();
}

Scene::~Scene()
{
    view->deleteLater();
    clearScene();
}

void Scene::clearScene(){
    if (mainMenu!=nullptr){
        mainMenu->deleteLater();
        mainMenu = nullptr;
    }
    if (settingsMenu!=nullptr){
        settingsMenu->deleteLater();
        settingsMenu = nullptr;
    }
    if (platform!=nullptr){
        delete platform;
        platform = nullptr;
    }
    foreach (Ball* b, balls){
        removeItem(b->graphics);
        delete b;
    }
    balls.clear();
    foreach (Block* b, blocks){
        removeItem(b->graphics);
        delete b;
    }
    blocks.clear();
    foreach (Block* b, borders){
        removeItem(b->graphics);
        delete b;
    }
    borders.clear();
}

void Scene::start(){
    connect(&timer, SIGNAL(timeout()), this, SLOT(nextTick()));
    timer.start(TIMER_STEP);
}

inline void Scene::createPlatform(int width, int height){
    if (platform==0){
        platform=new Platform(this);
        ((RoundPlatform*)platform->graphics)->setPen(QPen(Qt::black));
        ((RoundPlatform*)platform->graphics)->setBrush(QBrush(Qt::green));
        ((RoundPlatform*)platform->graphics)->setRect(QRectF(0, 0, width, height));
        ((RoundPlatform*)platform->graphics)->setPos(this->width()/2-width/2,
                                                        this->height()-height*2);
        platform->properties->setProperty("isMovingLeft", false);
        platform->properties->setProperty("isMovingRight", false);
    }
}

void Scene::addBall(QRectF rect, QColor clr, QVector2D vect){
    balls.push_back(new Ball(this));
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setPen(QPen(Qt::black));
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setBrush(QBrush(clr));
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsEllipseItem*)(balls.back()->graphics))->setPos(rect.x(), rect.y());
    balls.back()->properties->setSpeed(vect);
}

void Scene::addBlock(QRectF rect, QColor clr){
    blocks.push_back(new Block(this));
    ((QGraphicsRectItem*)blocks.back()->graphics)->setPen(QPen(Qt::black));
    ((QGraphicsRectItem*)blocks.back()->graphics)->setBrush(QBrush(clr));
    ((QGraphicsRectItem*)blocks.back()->graphics)->setRect(0, 0, rect.width(), rect.height());
    ((QGraphicsRectItem*)blocks.back()->graphics)->setPos(rect.x(), rect.y());
    blocks.back()->properties->setDestroyable(true);
 }

inline void Scene::createBorders(){
    if (borders.isEmpty()){
        for (int i=0; i<4; i++){
            borders.push_back(new Block(this));
            ((QGraphicsRectItem*)borders[i]->graphics)->setPen(QPen(Qt::black));
            ((QGraphicsRectItem*)borders[i]->graphics)->setBrush(QBrush(Qt::gray));
        }
        ((QGraphicsRectItem*)borders[0]->graphics)->setRect(0, 0, this->width(), 1);
        ((QGraphicsRectItem*)borders[0]->graphics)->setPos(0, this->height()-1);
        ((QGraphicsRectItem*)borders[1]->graphics)->setRect(0, 0, BORDER_DEPTH, this->height());
        ((QGraphicsRectItem*)borders[2]->graphics)->setRect(0, 0, this->width(), BORDER_DEPTH);
        ((QGraphicsRectItem*)borders[3]->graphics)->setRect(0, 0, BORDER_DEPTH, this->height());
        ((QGraphicsRectItem*)borders[3]->graphics)->setPos(this->width()-BORDER_DEPTH, 0);
        borders[0]->graphics->hide();
    }
}

inline void Scene::initMainMenu(){
    mainMenu = new Menu;
    this->addWidget(mainMenu);
//    mainMenu->setStyleSheet("QPushButton { color: white }");
    mainMenu->setGeometry(width()/2-100, height()/5+100, 200, 200);
    QAbstractButton* temp = mainMenu->addButton("New Game");
    connect(temp, SIGNAL(clicked()), this, SLOT(initGame()));
    temp = mainMenu->addButton("Level Editor");
    connect(temp, SIGNAL(clicked()), this, SLOT(initLevelEditor()));
    temp = mainMenu->addButton("Settings");
    connect(temp, SIGNAL(clicked()), this, SLOT(initSettings()));
    temp = mainMenu->addButton("Exit");
    connect(temp, SIGNAL(clicked()), this, SLOT(exit()));
}

 void Scene::nextTick(){
    //Moves
    if ((platform->properties->property("isMovingLeft")).toBool())
        if (platform->graphics->pos().x()>=BORDER_DEPTH+BALL_WIDTH+1)
            platform->graphics->setPos(platform->graphics->pos().x()+
                                       platform->properties->getSpeed().x(),
                                       platform->graphics->pos().y()+
                                       platform->properties->getSpeed().y());
    if ((platform->properties->property("isMovingRight")).toBool())
        if (platform->graphics->pos().x()<=this->width()-PLATFORM_WIDTH-BORDER_DEPTH-BALL_WIDTH-1)
            platform->graphics->setPos(platform->graphics->pos().x()+
                                       platform->properties->getSpeed().x(),
                                       platform->graphics->pos().y()+
                                       platform->properties->getSpeed().y());
    for (int i=0; i<balls.size(); i++){
        balls[i]->graphics->setPos(balls[i]->graphics->pos().x()+
                                   balls[i]->properties->getSpeed().x(),
                                   balls[i]->graphics->pos().y()+
                                   balls[i]->properties->getSpeed().y());
    }
    //Collides
    for (int i=0; i<balls.size(); i++){
        if (balls[i]->collidesWithItem(borders[0])){
            delete balls[i];
            balls.erase(balls.begin()+i);
            continue;
        }
        if (balls[i]->collidesWithItem(platform)){
            calculateCollide(balls[i], platform);
        }
        for (int j=1; j<borders.size(); j++){
            if (balls[i]->collidesWithItem(borders[j])){
                calculateCollide(balls[i], borders[j]);
            }
        }
        for (int j=0; j<balls.size(); j++){
            if (i!=j)
            if (balls[i]->collidesWithItem(balls[j]))
                calculateCollide(balls[i], balls[j]);
        }
        for (int j=0; j<blocks.size(); j++){
            if (balls[i]->collidesWithItem(blocks[j])){
                calculateCollide(balls[i], blocks[j]);
                if (blocks[j]->properties->isDestroyable()){
                    delete blocks[j];
                    blocks.erase(blocks.begin()+j);
                }
            }
        }
    }
}

void Scene::calculateCollide(SceneObject* main, SceneObject* secondary){
    QPointF intersection(0,0);
    main->collidesWithItem(secondary, &intersection);
    intersection+=main->graphics->scenePos();

    //Static part
    double posX = main->graphics->pos().x();
    double posY = main->graphics->pos().y();
    double centerX = posX + (double)BALL_WIDTH/2;
    double centerY = posY + (double)BALL_HEIGHT/2;
    double speedX = main->properties->getSpeed().x();
    double speedY = main->properties->getSpeed().y();
    QVector2D normal(intersection.x()-centerX, intersection.y()-centerY);
    QVector2D tangent(normal.y(), -normal.x());
    double temp = tangent.y()/tangent.length();

    double alpha;
    if (temp<=1.0000001 && temp>=0.9999999)         alpha = M_PI/2;
    else if (temp>=-1.0000001 && temp<=-0.9999999)  alpha = -M_PI/2;
    else                                            alpha = asin(temp);

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

void Scene::exit(){
    emit quit();
}

void Scene::initGame(){
    clearScene();
}

void Scene::initLevelEditor(){

}

void Scene::initSettings(){

}

void Scene::keyPressEvent(QKeyEvent * pe){
    switch (pe->key()){
        case Qt::Key_Left:{
            if (!pe->isAutoRepeat()){
                platform->properties->setProperty("isMovingLeft", true);
                if ((platform->properties->property("isMovingRight")).toBool())
                    platform->properties->setSpeed(QVector2D(0, 0));
                else
                    platform->properties->setSpeed(QVector2D(-PLATFORM_SPEED, 0));
            }
        }
        break;
        case Qt::Key_Right:{
            if (!pe->isAutoRepeat()){
                platform->properties->setProperty("isMovingRight", true);
                if ((platform->properties->property("isMovingLeft")).toBool())
                    platform->properties->setSpeed(QVector2D(0, 0));
                else
                    platform->properties->setSpeed(QVector2D(PLATFORM_SPEED, 0));
             }
        }
        break;
        case Qt::Key_B:{
            if (!pe->isAutoRepeat()){
                balls.push_back(new Ball(this));
                delete balls.back()->graphics;
                balls.back()->graphics = new QGraphicsEllipseItem(0, this);
                ((QGraphicsEllipseItem*)(balls.back()->graphics))->
                        setPen(QPen(Qt::black));
                ((QGraphicsEllipseItem*)(balls.back()->graphics))->
                        setBrush(QBrush(Qt::red));
                ((QGraphicsEllipseItem*)(balls.back()->graphics))->
                        setRect(QRect(0, 0, BALL_WIDTH, BALL_HEIGHT));
                ((QGraphicsEllipseItem*)(balls.back()->graphics))->
                        setPos(this->width()/2-BALL_WIDTH/2, this->height()/2);
                balls.back()->properties->setSpeed(QVector2D(0, BALL_SPEED));
            }
        }
        break;
        case Qt::Key_S:{
            if (!pe->isAutoRepeat()){
                timer.stop();
            }
        }
        break;
        case Qt::Key_D:{
            if (!pe->isAutoRepeat()){
                timer.start(TIMER_STEP);
            }
        }
        break;
        default:
            QGraphicsScene::keyPressEvent(pe);
        break;
    }
}

void Scene::keyReleaseEvent(QKeyEvent * pe){
    switch (pe->key()){
        case Qt::Key_Left:{
            if (!pe->isAutoRepeat()){
                platform->properties->setProperty("isMovingLeft", false);
                if ((platform->properties->property("isMovingRight")).toBool())
                    platform->properties->setSpeed(QVector2D(PLATFORM_SPEED, 0));
                else
                    platform->properties->setSpeed(QVector2D(0, 0));
            }
        }
        break;
        case Qt::Key_Right:{
            if (!pe->isAutoRepeat()){
                platform->properties->setProperty("isMovingRight", false);
                if ((platform->properties->property("isMovingLeft")).toBool())
                    platform->properties->setSpeed(QVector2D(-PLATFORM_SPEED, 0));
                else
                    platform->properties->setSpeed(QVector2D(0, 0));
            }
        }
        break;
        default:
            QGraphicsScene::keyReleaseEvent(pe);
        break;
    }
}
