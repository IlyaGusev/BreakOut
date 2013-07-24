#ifndef EDITOR_H
#define EDITOR_H

class Editor;
class EditorBlock;

#include <QVector>
#include <QFile>
#include <QTextStream>

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
signals:
    void signalMain();
public slots:
    void slotCopy();
    void slotRemove();
    void slotSave(QString);
private:
    EditorMenu* menu;
    QVector<EditorBlock*> blocks;
};

#endif // EDITOR_H
