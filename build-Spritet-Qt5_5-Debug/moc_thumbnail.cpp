/****************************************************************************
** Meta object code from reading C++ file 'thumbnail.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/thumbnail.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thumbnail.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Thumbnail_t {
    QByteArrayData data[9];
    char stringdata0[109];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Thumbnail_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Thumbnail_t qt_meta_stringdata_Thumbnail = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Thumbnail"
QT_MOC_LITERAL(1, 10, 6), // "moveUp"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 14), // "DrawingCanvas*"
QT_MOC_LITERAL(4, 33, 8), // "moveDown"
QT_MOC_LITERAL(5, 42, 16), // "changeVisibility"
QT_MOC_LITERAL(6, 59, 15), // "upButtonPressed"
QT_MOC_LITERAL(7, 75, 17), // "downButtonPressed"
QT_MOC_LITERAL(8, 93, 15) // "checkBoxChanged"

    },
    "Thumbnail\0moveUp\0\0DrawingCanvas*\0"
    "moveDown\0changeVisibility\0upButtonPressed\0"
    "downButtonPressed\0checkBoxChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Thumbnail[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    2,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Thumbnail::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Thumbnail *_t = static_cast<Thumbnail *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->moveUp((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 1: _t->moveDown((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 2: _t->changeVisibility((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->upButtonPressed(); break;
        case 4: _t->downButtonPressed(); break;
        case 5: _t->checkBoxChanged(); break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Thumbnail::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thumbnail::moveUp)) {
                *result = 0;
            }
        }
        {
            typedef void (Thumbnail::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thumbnail::moveDown)) {
                *result = 1;
            }
        }
        {
            typedef void (Thumbnail::*_t)(DrawingCanvas * , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Thumbnail::changeVisibility)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject Thumbnail::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Thumbnail.data,
      qt_meta_data_Thumbnail,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Thumbnail::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Thumbnail::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Thumbnail.stringdata0))
        return static_cast<void*>(const_cast< Thumbnail*>(this));
    return QWidget::qt_metacast(_clname);
}

int Thumbnail::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Thumbnail::moveUp(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Thumbnail::moveDown(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Thumbnail::changeVisibility(DrawingCanvas * _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
