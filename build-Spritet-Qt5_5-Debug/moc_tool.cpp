/****************************************************************************
** Meta object code from reading C++ file 'tool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/tool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Tool_t {
    QByteArrayData data[6];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tool_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tool_t qt_meta_stringdata_Tool = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Tool"
QT_MOC_LITERAL(1, 5, 9), // "mouseMove"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 10), // "ToolEvent*"
QT_MOC_LITERAL(4, 27, 10), // "mousePress"
QT_MOC_LITERAL(5, 38, 12) // "mouseRelease"

    },
    "Tool\0mouseMove\0\0ToolEvent*\0mousePress\0"
    "mouseRelease"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

       0        // eod
};

void Tool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tool *_t = static_cast<Tool *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseMove((*reinterpret_cast< ToolEvent*(*)>(_a[1]))); break;
        case 1: _t->mousePress((*reinterpret_cast< ToolEvent*(*)>(_a[1]))); break;
        case 2: _t->mouseRelease((*reinterpret_cast< ToolEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Tool::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Tool.data,
      qt_meta_data_Tool,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Tool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tool::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Tool.stringdata0))
        return static_cast<void*>(const_cast< Tool*>(this));
    return QObject::qt_metacast(_clname);
}

int Tool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
