#ifndef EDITORMENU_H
#define EDITORMENU_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>

class EditorMenu : public QWidget
{
    Q_OBJECT
public:
    explicit EditorMenu(QWidget *parent = 0);
signals:
    void signalSave(QString);
    void signalLoad(QString);
    void signalMain();
public slots:
    void slotEmitSave();
    void slotEmitLoad();
private:
    QLineEdit* le;
};

#endif // EDITORMENU_H
