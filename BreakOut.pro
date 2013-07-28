#-------------------------------------------------
#
# Project created by QtCreator 2013-07-24T18:06:20
#
#-------------------------------------------------

QT       += core gui
QT       += phonon

TARGET = BreakOut
TEMPLATE = app


SOURCES += \
    scene.cpp \
    mainwindow.cpp \
    main.cpp \
    Editor/editormenu.cpp \
    Editor/editorblock.cpp \
    Editor/editor.cpp \
    Game/roundplatform.cpp \
    Game/platform.cpp \
    Game/physicsobject.cpp \
    Game/gamestate.cpp \
    Game/gameobject.cpp \
    Game/gamemenu.cpp \
    Game/gamefield.cpp \
    Game/game.cpp \
    Game/block.cpp \
    Game/ball.cpp \
    Menu/menusettings.cpp \
    Menu/menumain.cpp \
    Menu/menu.cpp \
    Game/bonus.cpp

HEADERS  += \
    scene.h \
    mainwindow.h \
    Editor/editormenu.h \
    Editor/editorblock.h \
    Editor/editor.h \
    Game/roundplatform.h \
    Game/platform.h \
    Game/physicsobject.h \
    Game/gamestate.h \
    Game/gameobject.h \
    Game/gamemenu.h \
    Game/gamefield.h \
    Game/game.h \
    Game/block.h \
    Game/ball.h \
    Menu/menusettings.h \
    Menu/menumain.h \
    Menu/menu.h \
    Game/bonus.h

FORMS    +=

QMAKE_CXXFLAGS += -std=c++0x

RESOURCES += \
    res.qrc
