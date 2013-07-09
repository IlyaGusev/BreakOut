/****************************************************************************
** Meta object code from reading C++ file 'scene.h'
**
** Created: Tue Jul 9 22:25:31 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../scene.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Scene[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      14,    6,    6,    6, 0x0a,
      25,    6,    6,    6, 0x0a,
      40,    6,    6,    6, 0x0a,
      51,    6,    6,    6, 0x0a,
      67,    6,    6,    6, 0x0a,
      85,    6,    6,    6, 0x0a,
     105,    6,    6,    6, 0x0a,
     116,    6,    6,    6, 0x0a,
     134,    6,    6,    6, 0x0a,
     152,    6,    6,    6, 0x0a,
     167,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Scene[] = {
    "Scene\0\0quit()\0nextTick()\0initMainMenu()\0"
    "initGame()\0initGameState()\0updateGameState()\0"
    "levelFinishedSlot()\0gameOver()\0"
    "initLevelEditor()\0saveEditorLevel()\0"
    "initSettings()\0exit()\0"
};

void Scene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Scene *_t = static_cast<Scene *>(_o);
        switch (_id) {
        case 0: _t->quit(); break;
        case 1: _t->nextTick(); break;
        case 2: _t->initMainMenu(); break;
        case 3: _t->initGame(); break;
        case 4: _t->initGameState(); break;
        case 5: _t->updateGameState(); break;
        case 6: _t->levelFinishedSlot(); break;
        case 7: _t->gameOver(); break;
        case 8: _t->initLevelEditor(); break;
        case 9: _t->saveEditorLevel(); break;
        case 10: _t->initSettings(); break;
        case 11: _t->exit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Scene::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Scene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_Scene,
      qt_meta_data_Scene, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Scene::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Scene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Scene::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Scene))
        return static_cast<void*>(const_cast< Scene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int Scene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Scene::quit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
