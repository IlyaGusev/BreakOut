/****************************************************************************
** Meta object code from reading C++ file 'editor.h'
**
** Created: Sun Jul 28 14:31:59 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Editor/editor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Editor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      21,    7,    7,    7, 0x0a,
      54,    7,    7,    7, 0x0a,
      89,    7,    7,    7, 0x0a,
     107,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Editor[] = {
    "Editor\0\0signalMain()\0"
    "slotCopy(EditorBlock::BlockType)\0"
    "slotRemove(EditorBlock::BlockType)\0"
    "slotSave(QString)\0slotLoad(QString)\0"
};

void Editor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Editor *_t = static_cast<Editor *>(_o);
        switch (_id) {
        case 0: _t->signalMain(); break;
        case 1: _t->slotCopy((*reinterpret_cast< EditorBlock::BlockType(*)>(_a[1]))); break;
        case 2: _t->slotRemove((*reinterpret_cast< EditorBlock::BlockType(*)>(_a[1]))); break;
        case 3: _t->slotSave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->slotLoad((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Editor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Editor::staticMetaObject = {
    { &Scene::staticMetaObject, qt_meta_stringdata_Editor,
      qt_meta_data_Editor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Editor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Editor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Editor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Editor))
        return static_cast<void*>(const_cast< Editor*>(this));
    return Scene::qt_metacast(_clname);
}

int Editor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Scene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Editor::signalMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
