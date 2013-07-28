#ifndef EDITOR_H
#define EDITOR_H

class Editor;
class EditorBlock;

#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "scene.h"
#include "editorblock.h"
#include "editormenu.h"

class Editor : public Scene
{
    Q_OBJECT
public:
    explicit Editor(QObject *parent = 0);
    ~Editor();
    void createBorders();
    void clearLevel();
    void createExamples();
signals:
    void signalMain();
public slots:
    void slotCopy(EditorBlock::BlockType);
    void slotRemove(EditorBlock::BlockType);
    void slotSave(QString);
    void slotLoad(QString);
private:
    EditorMenu* menu;
    QVector<EditorBlock*> standartBlocks;
    QVector<EditorBlock*> undestrBlocks;
    QVector<EditorBlock*> bonusBlocks;
};

#endif // EDITOR_H
