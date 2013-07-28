#include "editor.h"

Editor::Editor(QObject *parent) :
    Scene(1024, 768, parent)
{
    createBorders();
    menu = new EditorMenu;
    addWidget(menu);
    menu->setGeometry(900, 550, 100, 150);

    createExamples();

    connect(menu, SIGNAL(signalMain()), this, SIGNAL(signalMain()));
    connect(menu, SIGNAL(signalSave(QString)), this, SLOT(slotSave(QString)));
    connect(menu, SIGNAL(signalLoad(QString)), this, SLOT(slotLoad(QString)));
}

Editor::~Editor(){
    if (menu!=nullptr)
        menu->deleteLater();
    foreach(EditorBlock* eb, standartBlocks){
        delete eb;
    }
    standartBlocks.clear();
    foreach(EditorBlock* eb, undestrBlocks){
        delete eb;
    }
    undestrBlocks.clear();
    foreach(EditorBlock* eb, bonusBlocks){
        delete eb;
    }
    bonusBlocks.clear();
}

void Editor::createExamples(){
    EditorBlock* example = new EditorBlock(EditorBlock::STANDART);
    addItem(example);
    example->setRect(QRectF(0, 0, 100, 20));
    example->setPos(900, 60);
    standartBlocks.push_back(example);
    connect(example, SIGNAL(signalCopy(EditorBlock::BlockType)), this, SLOT(slotCopy(EditorBlock::BlockType)));
    connect(example, SIGNAL(signalRemove(EditorBlock::BlockType)), this, SLOT(slotRemove(EditorBlock::BlockType)));

    example = new EditorBlock(EditorBlock::UNDESTR);
    addItem(example);
    example->setRect(QRectF(0, 0, 100, 20));
    example->setPos(900, 90);
    undestrBlocks.push_back(example);
    connect(example, SIGNAL(signalCopy(EditorBlock::BlockType)), this, SLOT(slotCopy(EditorBlock::BlockType)));
    connect(example, SIGNAL(signalRemove(EditorBlock::BlockType)), this, SLOT(slotRemove(EditorBlock::BlockType)));

    example = new EditorBlock(EditorBlock::BONUS);
    addItem(example);
    example->setRect(QRectF(0, 0, 100, 20));
    example->setPos(900, 120);
    bonusBlocks.push_back(example);
    connect(example, SIGNAL(signalCopy(EditorBlock::BlockType)), this, SLOT(slotCopy(EditorBlock::BlockType)));
    connect(example, SIGNAL(signalRemove(EditorBlock::BlockType)), this, SLOT(slotRemove(EditorBlock::BlockType)));
}

void Editor::clearLevel(){
    foreach(EditorBlock* eb, standartBlocks){
        removeItem(eb);
        delete eb;
    }
    standartBlocks.clear();
    foreach(EditorBlock* eb, undestrBlocks){
        removeItem(eb);
        delete eb;
    }
    undestrBlocks.clear();
    foreach(EditorBlock* eb, bonusBlocks){
        removeItem(eb);
        delete eb;
    }
    bonusBlocks.clear();
}

void Editor::createBorders(){
    QGraphicsRectItem* borders = new QGraphicsRectItem(0, this);
    borders->setRect(LEFT_BORDER, UP_BORDER, RIGHT_BORDER-LEFT_BORDER, DOWN_BORDER-UP_BORDER);
    borders->setPen(QPen(Qt::black));
    borders->setBrush(QBrush(Qt::white));
}

void Editor::slotCopy(EditorBlock::BlockType type){
    EditorBlock* a = new EditorBlock(type);
    QVector<EditorBlock*>* blocks;
    if (type == EditorBlock::STANDART)
        blocks = &standartBlocks;
    else if (type == EditorBlock::UNDESTR)
        blocks = &undestrBlocks;
    else if (type == EditorBlock::BONUS)
        blocks = &bonusBlocks;
    a->setRect(blocks->back()->rect());
    a->setPos(blocks->back()->pos());
    a->setPen(blocks->back()->pen());
    a->setBrush(blocks->back()->brush());
    a->setColor(blocks->back()->color());

    disconnect(blocks->back(), SIGNAL(signalCopy(EditorBlock::BlockType)), this, SLOT(slotCopy(EditorBlock::BlockType)));
    connect(a, SIGNAL(signalCopy(EditorBlock::BlockType)), this, SLOT(slotCopy(EditorBlock::BlockType)));
    connect(a, SIGNAL(signalRemove(EditorBlock::BlockType)), this, SLOT(slotRemove(EditorBlock::BlockType)));
    addItem(a);
    blocks->push_back(a);
}

void Editor::slotRemove(EditorBlock::BlockType type){
    QVector<EditorBlock*>* blocks;
    if (type == EditorBlock::STANDART)
        blocks = &standartBlocks;
    else if (type == EditorBlock::UNDESTR)
        blocks = &undestrBlocks;
    else if (type == EditorBlock::BONUS)
        blocks = &bonusBlocks;
    QVector<EditorBlock*>::iterator it;
    for (it=blocks->begin(); it!=(blocks->end()-1); it++){
        if (!(((*it)->pos().x()>LEFT_BORDER) &&
              ((*it)->pos().x()+(*it)->rect().width()<RIGHT_BORDER) &&
              ((*it)->pos().y()>UP_BORDER) &&
              ((*it)->pos().y()+(*it)->rect().height()<DOWN_BORDER))){
            removeItem(*it);
            delete (*it);
            blocks->erase(it);
            break;
        }
    }
}

void Editor::slotSave(QString name){
    if (name!=""){
        QFile file("Levels/"+name+".lvl");
        if (file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            foreach (EditorBlock* bl, standartBlocks){
                if (((bl->pos().x()>LEFT_BORDER) && (bl->pos().x()+bl->rect().width()<RIGHT_BORDER) &&
                       (bl->pos().y()>UP_BORDER) && (bl->pos().y()+bl->rect().height()<DOWN_BORDER))){
                    stream<<"addblock "<<bl->pos().x()<<" "<<bl->pos().y()<<" "<<
                            bl->rect().width()<<" "<<bl->rect().height()<<" "<<
                            bl->color()<<" "<<static_cast<int>(bl->blockType())<<"\n";
                }
            }
            foreach (EditorBlock* bl, undestrBlocks){
                if (((bl->pos().x()>LEFT_BORDER) && (bl->pos().x()+bl->rect().width()<RIGHT_BORDER) &&
                       (bl->pos().y()>UP_BORDER) && (bl->pos().y()+bl->rect().height()<DOWN_BORDER))){
                    stream<<"addblock "<<bl->pos().x()<<" "<<bl->pos().y()<<" "<<
                            bl->rect().width()<<" "<<bl->rect().height()<<" "<<
                            bl->color()<<" "<<static_cast<int>(bl->blockType())<<"\n";
                }
            }
            foreach (EditorBlock* bl, bonusBlocks){
                if (((bl->pos().x()>LEFT_BORDER) && (bl->pos().x()+bl->rect().width()<RIGHT_BORDER) &&
                       (bl->pos().y()>UP_BORDER) && (bl->pos().y()+bl->rect().height()<DOWN_BORDER))){
                    stream<<"addblock "<<bl->pos().x()<<" "<<bl->pos().y()<<" "<<
                            bl->rect().width()<<" "<<bl->rect().height()<<" "<<
                            bl->color()<<" "<<static_cast<int>(bl->blockType())<<"\n";
                }
            }
            file.close();
        }
    }
}

void Editor::slotLoad(QString name){
    clearLevel();
    if (name!=""){
        QFile file("Levels/"+name+".lvl");
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

                    EditorBlock* bl = new EditorBlock(EditorBlock::BlockType(type));
                    addItem(bl);
                    bl->setRect(QRectF(0, 0, width, height));
                    bl->setPos(x, y);
                    if (type==EditorBlock::STANDART)
                        bl->setBrush(QColor(Qt::GlobalColor(color)));
                    else if (type==EditorBlock::UNDESTR)
                        bl->setBrush(QBrush(QColor(Qt::GlobalColor(color)), Qt::Dense3Pattern));
                    else if (type==EditorBlock::BONUS)
                        bl->setBrush(QBrush(QColor(Qt::GlobalColor(color)), Qt::Dense1Pattern));
                    bl->setColor(color);

                    QVector<EditorBlock*>* blocks;
                    if (type == EditorBlock::STANDART)
                        blocks = &standartBlocks;
                    else if (type == EditorBlock::UNDESTR)
                        blocks = &undestrBlocks;
                    else if (type == EditorBlock::BONUS)
                        blocks = &bonusBlocks;
                    connect(bl, SIGNAL(signalRemove(EditorBlock::BlockType)), this, SLOT(slotRemove(EditorBlock::BlockType)));
                    blocks->push_back(bl);
                }
            }
            file.close();
        }
    }
    createExamples();
}
