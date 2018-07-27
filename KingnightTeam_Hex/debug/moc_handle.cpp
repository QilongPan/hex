/****************************************************************************
** Meta object code from reading C++ file 'handle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../handle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'handle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Handle_t {
    QByteArrayData data[12];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Handle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Handle_t qt_meta_stringdata_Handle = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Handle"
QT_MOC_LITERAL(1, 7, 13), // "startBtnClick"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 15), // "restartBtnClick"
QT_MOC_LITERAL(4, 38, 12), // "backBtnClick"
QT_MOC_LITERAL(5, 51, 22), // "radioBtnClick_Computer"
QT_MOC_LITERAL(6, 74, 20), // "radioBtnClick_Player"
QT_MOC_LITERAL(7, 95, 12), // "readBtnClick"
QT_MOC_LITERAL(8, 108, 12), // "saveBtnClick"
QT_MOC_LITERAL(9, 121, 10), // "toBtnClick"
QT_MOC_LITERAL(10, 132, 10), // "upBtnClick"
QT_MOC_LITERAL(11, 143, 12) // "downBtnClick"

    },
    "Handle\0startBtnClick\0\0restartBtnClick\0"
    "backBtnClick\0radioBtnClick_Computer\0"
    "radioBtnClick_Player\0readBtnClick\0"
    "saveBtnClick\0toBtnClick\0upBtnClick\0"
    "downBtnClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Handle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    0,   71,    2, 0x0a /* Public */,
      10,    0,   72,    2, 0x0a /* Public */,
      11,    0,   73,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Handle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Handle *_t = static_cast<Handle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startBtnClick(); break;
        case 1: _t->restartBtnClick(); break;
        case 2: _t->backBtnClick(); break;
        case 3: _t->radioBtnClick_Computer(); break;
        case 4: _t->radioBtnClick_Player(); break;
        case 5: _t->readBtnClick(); break;
        case 6: _t->saveBtnClick(); break;
        case 7: _t->toBtnClick(); break;
        case 8: _t->upBtnClick(); break;
        case 9: _t->downBtnClick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Handle::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Handle.data,
      qt_meta_data_Handle,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Handle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Handle::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Handle.stringdata0))
        return static_cast<void*>(const_cast< Handle*>(this));
    return QWidget::qt_metacast(_clname);
}

int Handle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
