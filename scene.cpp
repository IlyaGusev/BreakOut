#include "scene.h"
const int PLATFORM_WIDTH = 170;
const int PLATFORM_HEIGHT = 30;
const int BALL_RADIUS = 24;
const int ANIMATIONTIMER_STEP = 3;
const int BORDER_DEPTH = 10;
const double BALL_SPEED = 2;
const double PLATFORM_SPEED = 1.5;
static const int GAME_STATS_WIDTH = 160;

Scene::Scene(int width, int height, QObject* parent) :
    QGraphicsScene(0, 0, width, height, parent),
    mainMenu(nullptr),
    settingsMenu(nullptr),
    editorMenu(nullptr),
    gameState(nullptr),
    view (new QGraphicsView),
    platform(nullptr),
    balls(),
    borders(),
    blocks(),
    editorBlocks(),
    animationTimer(this),
    levelname("1-1"),
    score(0),
    lifes(3)
{
    initMainMenu();
}

void Scene::initMainMenu(){
    clearScene();
    mainMenu = new QWidget;
    this->addWidget(mainMenu);
    mainMenu->setGeometry(width()/2-100, height()/5+100, 200, 200);

    QPushButton* ng = new QPushButton("New Game");
    QPushButton* le = new QPushButton("Level Editor");
    QPushButton* st = new QPushButton("Settings");
    QPushButton* ex = new QPushButton("Exit");

    connect(ng, SIGNAL(clicked()), this, SLOT(initGame()));
    connect(le, SIGNAL(clicked()), this, SLOT(initLevelEditor()));
    connect(st, SIGNAL(clicked()), this, SLOT(initSettings()));
    connect(ex, SIGNAL(clicked()), this, SLOT(exit()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(ng);
    layout->addWidget(le);
    layout->addWidget(st);
    layout->addWidget(ex);
    mainMenu->setLayout(layout);
}

void Scene::initGame(){
    clearScene();
    createPlatform(PLATFORM_WIDTH, PLATFORM_HEIGHT);
    addBall(QRectF(platform->graphics->pos().x()+PLATFORM_WIDTH/2-BALL_RADIUS/2,
                   platform->graphics->pos().y()-BALL_RADIUS,
                   BALL_RADIUS,
                   BALL_RADIUS),
            QColor(Qt::red),
            QVector2D(0, -BALL_SPEED));
    createBorders();
    initGameState();
    loadLevel("Levels/"+levelname+".lvl");
    start();
}

void Scene::loadLevel(QString name){
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
                addBlock(QRectF(x,y,width,height), QColor(Qt::GlobalColor(color)));
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

void Scene::initGameState(){
    gameState = new QWidget;
    gameState->setGeometry(this->width()-GAME_STATS_WIDTH+20, 50,
                          GAME_STATS_WIDTH-20, 250);
    this->addWidget(gameState);
    QLabel* lvlLbl = new QLabel("Level: "+levelname);
    QLabel* scoreLbl = new QLabel("Score: ");
    QLabel* lifesLbl = new QLabel("Lifes: ");
    QLCDNumber* scoreWgt = new QLCDNumber(6);
    QLCDNumber* lifesWgt = new QLCDNumber(6);

    scoreWgt->display(score);
    lifesWgt->display(lifes);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(lvlLbl);
    layout->addWidget(scoreLbl);
    layout->addWidget(scoreWgt);
    layout->addWidget(lifesLbl);
    layout->addWidget(lifesWgt);
    gameState->setLayout(layout);
}

void Scene::updateGameState(){
    gameState->deleteLater();
    initGameState();
}

void Scene::updateTime(){
    time.addSecs(1);
    initGameState();
}

void Scene::initLevelEditor(){
    clearScene();
    createBorders();
    EditorBlock* example = new EditorBlock(this);
    example->setRect(0, 0, 100, 20);
    example->setPos(900, 60);
    editorBlocks.push_back(example);

    editorMenu = new QWidget;
    editorMenu->setGeometry(900, 600, 100, 120);
    this->addWidget(editorMenu);

    QLineEdit* le = new QLineEdit;
    QPushButton* sv = new QPushButton("Save");
    QPushButton* ex = new QPushButton("Exit");

    connect(sv, SIGNAL(clicked()), this, SLOT(saveEditorLevel()));
    connect(ex, SIGNAL(clicked()), this, SLOT(initMainMenu()));

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(le);
    layout->addWidget(sv);
    layout->addWidget(ex);
    editorMenu->setLayout(layout);
}

void Scene::saveEditorLevel(){
    QWidget* line = editorMenu->childAt(editorMenu->width()/2, 15);
    if (((QLineEdit*)line)->displayText()!=""){
        QFile file("Levels/"+((QLineEdit*)line)->displayText()+".lvl");
        if (file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            foreach (EditorBlock* bl, editorBlocks){
                if (((bl->pos().x()>LEFT_BORDER) && (bl->pos().x()+bl->rect().width()<RIGHT_BORDER) &&
                       (bl->pos().y()>UP_BORDER) && (bl->pos().y()+bl->rect().height()<DOWN_BORDER))){
                    stream<<"addblock "<<bl->pos().x()<<" "<<bl->pos().y()<<" "<<
                            bl->rect().width()<<" "<<bl->rect().height()<<" "<<bl->color()<<"\n";
                }
            }
            file.close();
        }
    }
}

void Scene::initSettings(){

}

void Scene::exit(){
    emit quit();
}

inline void Scene::createPlatform(int width, int height){
    if (platform==0){
        platform=new Platform(this);
        ((RoundPlatform*)platform->graphics)->setPen(QPen(Qt::black));
        ((RoundPlatform*)platform->graphics)->setBrush(QBrush(Qt::green));
        ((RoundPlatform*)platform->graphics)->setRect(QRectF(0, 0, width, height));
        ((RoundPlatform*)platform->graphics)->setPos((this->width()-GAME_STATS_WIDTH)/2-width/2,
                                                        this->height()-height*2);
        platform->properties->setProperty("isMovingLeft", false);
        platform->properties->setProperty("isMovingRight", false);
    }
}

inline void Scene::createBorders(){
    if (borders.isEmpty()){
        for (int i=0; i<4; i++){
            borders.push_back(new Block(this));
            ((QGraphicsRectItem*)borders[i]->graphics)->setPen(QPen(Qt::black));
            ((QGraphicsRectItem*)borders[i]->graphics)->setBrush(QBrush(Qt::gray));
        }
        ((QGraphicsRectItem*)borders[0]->graphics)->setRect(0, 0, this->width()-GAME_STATS_WIDTH, 1);
        ((QGraphicsRectItem*)borders[0]->graphics)->setPos(0, this->height()-1);
        ((QGraphicsRectItem*)borders[1]->graphics)->setRect(0, 0, BORDER_DEPTH, this->height());
        ((QGraphicsRectItem*)borders[2]->graphics)->setRect(0, 0, this->width()-GAME_STATS_WIDTH, BORDER_DEPTH);
        ((QGraphicsRectItem*)borders[3]->graphics)->setRect(0, 0, BORDER_DEPTH, this->height());
        ((QGraphicsRectItem*)borders[3]->graphics)->setPos(this->width()-GAME_STATS_WIDTH-BORDER_DEPTH, 0);
        borders[0]->graphics->hide();
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
void Scene::copyEditorBlock(EditorBlock* b){
    EditorBlock* a = new EditorBlock(this);
    a->setRect(b->rect());
    a->setPos(b->pos());
    a->setPen(b->pen());
    a->setBrush(b->brush());
    a->setColor(b->color());
    editorBlocks.push_back(a);
}

void Scene::removeEditorBlock(EditorBlock *bl){
    QVector<EditorBlock*>::iterator it;
    for (it=editorBlocks.begin(); it!=editorBlocks.end(); it++){
        if ((*it)==bl)
            editorBlocks.erase(it);
        break;
    }
}

void Scene::start(){
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(nextTick()));
    animationTimer.start(ANIMATIONTIMER_STEP);
}

void Scene::nextTick(){
    //Moves
    if ((platform->properties->property("isMovingLeft")).toBool())
        if (platform->graphics->pos().x()>=BORDER_DEPTH)
            platform->graphics->setPos(platform->graphics->pos().x()+
                                       platform->properties->getSpeed().x(),
                                       platform->graphics->pos().y()+
                                       platform->properties->getSpeed().y());
    if ((platform->properties->property("isMovingRight")).toBool())
        if (platform->graphics->pos().x()<=this->width()-
                                           PLATFORM_WIDTH-BORDER_DEPTH-
                                           GAME_STATS_WIDTH)
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
            if (balls.isEmpty()){
                lifes--;
                updateGameState();
            }
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
                    score+=100;
                    updateGameState();
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
    double centerX = posX + (double)BALL_RADIUS/2;
    double centerY = posY + (double)BALL_RADIUS/2;
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
                        setRect(QRect(0, 0, BALL_RADIUS, BALL_RADIUS));
                ((QGraphicsEllipseItem*)(balls.back()->graphics))->
                        setPos(this->width()/2-BALL_RADIUS/2, this->height()/2);
                balls.back()->properties->setSpeed(QVector2D(0, BALL_SPEED));
            }
        }
        break;
        case Qt::Key_S:{
            if (!pe->isAutoRepeat()){
                animationTimer.stop();
            }
        }
        break;
        case Qt::Key_D:{
            if (!pe->isAutoRepeat()){
                animationTimer.start(ANIMATIONTIMER_STEP);
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

Scene::~Scene(){
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
    if (editorMenu!=nullptr){
        editorMenu->deleteLater();
        editorMenu = nullptr;
    }
    if (gameState!=nullptr){
        gameState->deleteLater();
        gameState = nullptr;
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
    foreach (EditorBlock* b, editorBlocks){
        removeItem(b);
        delete b;
    }
    editorBlocks.clear();
    foreach (Block* b, borders){
        removeItem(b->graphics);
        delete b;
    }
    borders.clear();
}

