#include "scene.h"

Scene::Scene(int width, int height, QObject* parent) :
    QGraphicsScene(0, 0, width, height, parent)
{
}
//void Scene::saveEditorLevel(){
//    QWidget* line = editorMenu->childAt(editorMenu->width()/2, 15);
//    if (((QLineEdit*)line)->displayText()!=""){
//        QFile file("Levels/"+((QLineEdit*)line)->displayText()+".lvl");
//        if (file.open(QIODevice::WriteOnly)){
//            QTextStream stream(&file);
//            foreach (EditorBlock* bl, editorBlocks){
//                if (((bl->pos().x()>LEFT_BORDER) && (bl->pos().x()+bl->rect().width()<RIGHT_BORDER) &&
//                       (bl->pos().y()>UP_BORDER) && (bl->pos().y()+bl->rect().height()<DOWN_BORDER))){
//                    stream<<"addblock "<<bl->pos().x()<<" "<<bl->pos().y()<<" "<<
//                            bl->rect().width()<<" "<<bl->rect().height()<<" "<<bl->color()<<"\n";
//                }
//            }
//            file.close();
//        }
//    }
//}


