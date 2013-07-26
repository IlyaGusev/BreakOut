/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created: Thu Jul 25 14:15:58 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Game/game.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Game[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       6,    5,    5,    5, 0x05,

 // slots: signature, parameters, type, tag, flags
      19,    5,    5,    5, 0x08,
      40,    5,    5,    5, 0x08,
      60,    5,    5,    5, 0x08,
      75,    5,    5,    5, 0x08,
      88,    5,    5,    5, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Game[] = {
    "Game\0\0signalMain()\0slotBlockDestroyed()\0"
    "slotLevelFinished()\0slotBallLost()\0"
    "slotResume()\0slotGameOver()\0"
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Game *_t = static_cast<Game *>(_o);
        switch (_id) {
        case 0: _t->signalMain(); break;
        case 1: _t->slotBlockDestroyed(); break;
        case 2: _t->slotLevelFinished(); break;
        case 3: _t->slotBallLost(); break;
        case 4: _t->slotResume(); break;
        case 5: _t->slotGameOver(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Game::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Game::staticMetaObject = {
    { &Scene::staticMetaObject, qt_meta_stringdata_Game,
      qt_meta_data_Game, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Game::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Game))
        return static_cast<void*>(const_cast< Game*>(this));
    return Scene::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Scene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Game::signalMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
