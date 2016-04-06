/****************************************************************************
** Meta object code from reading C++ file 'preview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/preview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Preview_t {
    QByteArrayData data[18];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Preview_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Preview_t qt_meta_stringdata_Preview = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Preview"
QT_MOC_LITERAL(1, 8, 11), // "deleteScene"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 14), // "DrawingCanvas*"
QT_MOC_LITERAL(4, 36, 5), // "scene"
QT_MOC_LITERAL(5, 42, 9), // "addCanvas"
QT_MOC_LITERAL(6, 52, 13), // "previewCanvas"
QT_MOC_LITERAL(7, 66, 1), // "i"
QT_MOC_LITERAL(8, 68, 12), // "moveCanvasUp"
QT_MOC_LITERAL(9, 81, 10), // "thisCanvas"
QT_MOC_LITERAL(10, 92, 14), // "moveCanvasDown"
QT_MOC_LITERAL(11, 107, 9), // "fpsChange"
QT_MOC_LITERAL(12, 117, 5), // "value"
QT_MOC_LITERAL(13, 123, 13), // "canvasDisplay"
QT_MOC_LITERAL(14, 137, 13), // "setCanvasSize"
QT_MOC_LITERAL(15, 151, 6), // "size_t"
QT_MOC_LITERAL(16, 158, 1), // "x"
QT_MOC_LITERAL(17, 160, 1) // "y"

    },
    "Preview\0deleteScene\0\0DrawingCanvas*\0"
    "scene\0addCanvas\0previewCanvas\0i\0"
    "moveCanvasUp\0thisCanvas\0moveCanvasDown\0"
    "fpsChange\0value\0canvasDisplay\0"
    "setCanvasSize\0size_t\0x\0y"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Preview[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x0a /* Public */,
       5,    2,   52,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,
      10,    1,   60,    2, 0x0a /* Public */,
      11,    1,   63,    2, 0x0a /* Public */,
      13,    0,   66,    2, 0x0a /* Public */,
      14,    2,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    6,    7,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 15, 0x80000000 | 15,   16,   17,

       0        // eod
};

void Preview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Preview *_t = static_cast<Preview *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->deleteScene((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 1: _t->addCanvas((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->moveCanvasUp((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 3: _t->moveCanvasDown((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 4: _t->fpsChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->canvasDisplay(); break;
        case 6: _t->setCanvasSize((*reinterpret_cast< size_t(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Preview::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Preview.data,
      qt_meta_data_Preview,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Preview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Preview::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Preview.stringdata0))
        return static_cast<void*>(const_cast< Preview*>(this));
    return QWidget::qt_metacast(_clname);
}

int Preview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
