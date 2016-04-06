/****************************************************************************
** Meta object code from reading C++ file 'framepanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/framepanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framepanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FramePanel_t {
    QByteArrayData data[23];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FramePanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FramePanel_t qt_meta_stringdata_FramePanel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "FramePanel"
QT_MOC_LITERAL(1, 11, 13), // "addFrameToGUI"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 3), // "num"
QT_MOC_LITERAL(4, 30, 17), // "removeFrameSignal"
QT_MOC_LITERAL(5, 48, 14), // "DrawingCanvas*"
QT_MOC_LITERAL(6, 63, 17), // "moveUpFrameSignal"
QT_MOC_LITERAL(7, 81, 19), // "moveDownFrameSignal"
QT_MOC_LITERAL(8, 101, 12), // "frameChecked"
QT_MOC_LITERAL(9, 114, 3), // "row"
QT_MOC_LITERAL(10, 118, 14), // "frameUnchecked"
QT_MOC_LITERAL(11, 133, 23), // "addFrameSignalToPreview"
QT_MOC_LITERAL(12, 157, 15), // "frameSizeSetted"
QT_MOC_LITERAL(13, 173, 6), // "size_t"
QT_MOC_LITERAL(14, 180, 1), // "x"
QT_MOC_LITERAL(15, 182, 1), // "y"
QT_MOC_LITERAL(16, 184, 8), // "addFrame"
QT_MOC_LITERAL(17, 193, 5), // "frame"
QT_MOC_LITERAL(18, 199, 11), // "removeFrame"
QT_MOC_LITERAL(19, 211, 11), // "moveFrameUp"
QT_MOC_LITERAL(20, 223, 13), // "moveFrameDown"
QT_MOC_LITERAL(21, 237, 15), // "changeVisiblity"
QT_MOC_LITERAL(22, 253, 10) // "visibility"

    },
    "FramePanel\0addFrameToGUI\0\0num\0"
    "removeFrameSignal\0DrawingCanvas*\0"
    "moveUpFrameSignal\0moveDownFrameSignal\0"
    "frameChecked\0row\0frameUnchecked\0"
    "addFrameSignalToPreview\0frameSizeSetted\0"
    "size_t\0x\0y\0addFrame\0frame\0removeFrame\0"
    "moveFrameUp\0moveFrameDown\0changeVisiblity\0"
    "visibility"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FramePanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       7,    1,   88,    2, 0x06 /* Public */,
       8,    2,   91,    2, 0x06 /* Public */,
      10,    1,   96,    2, 0x06 /* Public */,
      11,    2,   99,    2, 0x06 /* Public */,
      12,    2,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  109,    2, 0x0a /* Public */,
      18,    1,  112,    2, 0x0a /* Public */,
      19,    1,  115,    2, 0x0a /* Public */,
      20,    1,  118,    2, 0x0a /* Public */,
      21,    2,  121,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    9,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    3,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   14,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,   17,
    QMetaType::Void, 0x80000000 | 5,   17,
    QMetaType::Void, 0x80000000 | 5,   17,
    QMetaType::Void, 0x80000000 | 5,   17,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Bool,   17,   22,

       0        // eod
};

void FramePanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FramePanel *_t = static_cast<FramePanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addFrameToGUI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->removeFrameSignal((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 2: _t->moveUpFrameSignal((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 3: _t->moveDownFrameSignal((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 4: _t->frameChecked((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->frameUnchecked((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 6: _t->addFrameSignalToPreview((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->frameSizeSetted((*reinterpret_cast< size_t(*)>(_a[1])),(*reinterpret_cast< size_t(*)>(_a[2]))); break;
        case 8: _t->addFrame((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 9: _t->removeFrame((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 10: _t->moveFrameUp((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 11: _t->moveFrameDown((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 12: _t->changeVisiblity((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< DrawingCanvas* >(); break;
            }
            break;
        case 12:
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
            typedef void (FramePanel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::addFrameToGUI)) {
                *result = 0;
            }
        }
        {
            typedef void (FramePanel::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::removeFrameSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (FramePanel::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::moveUpFrameSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (FramePanel::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::moveDownFrameSignal)) {
                *result = 3;
            }
        }
        {
            typedef void (FramePanel::*_t)(DrawingCanvas * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::frameChecked)) {
                *result = 4;
            }
        }
        {
            typedef void (FramePanel::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::frameUnchecked)) {
                *result = 5;
            }
        }
        {
            typedef void (FramePanel::*_t)(DrawingCanvas * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::addFrameSignalToPreview)) {
                *result = 6;
            }
        }
        {
            typedef void (FramePanel::*_t)(size_t , size_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FramePanel::frameSizeSetted)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject FramePanel::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_FramePanel.data,
      qt_meta_data_FramePanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FramePanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FramePanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FramePanel.stringdata0))
        return static_cast<void*>(const_cast< FramePanel*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int FramePanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void FramePanel::addFrameToGUI(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FramePanel::removeFrameSignal(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FramePanel::moveUpFrameSignal(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FramePanel::moveDownFrameSignal(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FramePanel::frameChecked(DrawingCanvas * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FramePanel::frameUnchecked(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FramePanel::addFrameSignalToPreview(DrawingCanvas * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void FramePanel::frameSizeSetted(size_t _t1, size_t _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
