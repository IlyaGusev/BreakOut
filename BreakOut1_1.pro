#-------------------------------------------------
#
# Project created by QtCreator 2013-07-05T15:50:21
#
#-------------------------------------------------

QT       += core gui

TARGET = BreakOut1_1
TEMPLATE = app

SOURCES += main.cpp\
        scene.cpp \
    physicsobject.cpp \
    sceneobject.cpp \
    roundplatform.cpp \
    menu.cpp \
    mainwindow.cpp \
    ball.cpp \
    block.cpp \
    platform.cpp

HEADERS  += scene.h \
    physicsobject.h \
    sceneobject.h \
    roundplatform.h \
    menu.h \
    mainwindow.h \
    ball.h \
    block.h \
    platform.h

OTHER_FILES +=

QMAKE_CXXFLAGS += -std=c++0x
