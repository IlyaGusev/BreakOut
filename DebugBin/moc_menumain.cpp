/****************************************************************************
** Meta object code from reading C++ file 'menumain.h'
**
** Created: Sun Jul 28 14:32:06 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Menu/menumain.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menumain.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MenuMain[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      23,    9,    9,    9, 0x05,
      38,    9,    9,    9, 0x05,
      55,    9,    9,    9, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_MenuMain[] = {
    "MenuMain\0\0signalGame()\0signalEditor()\0"
    "signalSettings()\0signalExit()\0"
};

void MenuMain::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MenuMain *_t = static_cast<MenuMain *>(_o);
        switch (_id) {
        case 0: _t->signalGame(); break;
        case 1: _t->signalEditor(); break;
        case 2: _t->signalSettings(); break;
        case 3: _t->signalExit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MenuMain::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MenuMain::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MenuMain,
      qt_meta_data_MenuMain, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MenuMain::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MenuMain::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MenuMain::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MenuMain))
        return static_cast<void*>(const_cast< MenuMain*>(this));
    return QWidget::qt_metacast(_clname);
}

int MenuMain::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MenuMain::signalGame()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MenuMain::signalEditor()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MenuMain::signalSettings()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MenuMain::signalExit()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
