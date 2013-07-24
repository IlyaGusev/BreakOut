#include "editor.h"

Editor::Editor(QObject *parent) :
    Scene(1024, 768, parent)
{
    createBorders();
    menu = new EditorMenu;
    addWidget(menu);
    menu->setGeometry(900, 600, 100, 120);

    EditorBlock* example = new EditorBlock;
    addItem(example);
    example->setRect(QRectF(0, 0, 100, 20));
    example->setPos(900, 60);
    blocks.push_back(example);

    connect(example, SIGNAL(signalCopy()), this, SLOT(slotCopy()));
    connect(example, SIGNAL(signalRemove()), this, SLOT(slotRemove()));
    connect(menu, SIGNAL(signalMain()), this, SIGNAL(signalMain()));
    connect(menu, SIGNAL(signalSave(QString)), this, SLOT(slotSave(QString)));
}

Editor::~Editor(){
    if (menu!=nullptr)
        menu->deleteLater();
    foreach(EditorBlock* eb, blocks){
        eb->deleteLater();
    }
}

void Editor::createBorders(){
    QGraphicsRectItem* borders = new QGraphicsRectItem(0, this);
    borders->setRect(LEFT_BORDER, UP_BORDER, RIGHT_BORDER-LEFT_BORDER, DOWN_BORDER-UP_BORDER);
    borders->setPen(QPen(Qt::black));
    borders->setBrush(QBrush(Qt::white));
}

void Editor::slotCopy(){
    EditorBlock* a = new EditorBlock;
    addItem(a);
    a->setRect(blocks.back()->rect());
    a->setPos(blocks.back()->pos());
    a->setPen(blocks.back()->pen());
    a->setBrush(blocks.back()->brush());
    a->setColor(blocks.back()->color());
    disconnect(blocks.back(), SIGNAL(signalCopy()), this, SLOT(slotCopy()));
    connect(a, SIGNAL(signalCopy()), this, SLOT(slotCopy()));
    connect(a, SIGNAL(signalRemove()), this, SLOT(slotRemove()));
    blocks.push_back(a);
}

void Editor::slotRemove(){
    QVector<EditorBlock*>::iterator it;
    for (it=blocks.begin(); it!=(blocks.end()-1); it++){
        if (!(((*it)->pos().x()>LEFT_BORDER) &&
              ((*it)->pos().x()+(*it)->rect().width()<RIGHT_BORDER) &&
              ((*it)->pos().y()>UP_BORDER) &&
              ((*it)->pos().y()+(*it)->rect().height()<DOWN_BORDER))){
            removeItem(*it);
            delete (*it);
            blocks.erase(it);
            break;
        }
    }
}

void Editor::slotSave(QString name){
    if (name!=""){
        QFile file("Levels/"+name+".lvl");
        if (file.open(QIODevice::WriteOnly)){
            QTextStream stream(&file);
            foreach (EditorBlock* bl, blocks){
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
