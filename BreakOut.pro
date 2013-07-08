#-------------------------------------------------
#
# Project created by QtCreator 2013-07-05T15:50:21
#
#-------------------------------------------------

QT       += core gui

TARGET = BreakOut
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
    platform.cpp \
    editorblock.cpp

HEADERS  += scene.h \
    physicsobject.h \
    sceneobject.h \
    roundplatform.h \
    menu.h \
    mainwindow.h \
    ball.h \
    block.h \
    platform.h \
    editorblock.h

OTHER_FILES +=

QMAKE_CXXFLAGS += -std=c++0x
