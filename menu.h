#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QVector>
#include <QSlider>
#include <QStyleOption>
#include <QPainter>

class Menu : public QWidget
{
    Q_OBJECT
    public:
        explicit Menu(QWidget *parent = 0);
        QAbstractButton* addButton(QString);
        QSlider* addSlider();
    private:
        QVBoxLayout* layout;
        QVector<QAbstractButton*> buttons;
        QVector<QSlider*> sliders;
    protected:
        void paintEvent(QPaintEvent *);
};

#endif // MENU_H
