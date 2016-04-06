/****************************************************************************
** Meta object code from reading C++ file 'framecontainer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/framecontainer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'framecontainer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FrameContainer_t {
    QByteArrayData data[7];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FrameContainer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FrameContainer_t qt_meta_stringdata_FrameContainer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "FrameContainer"
QT_MOC_LITERAL(1, 15, 8), // "addFrame"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 14), // "DrawingCanvas*"
QT_MOC_LITERAL(4, 40, 15), // "updateFrameList"
QT_MOC_LITERAL(5, 56, 28), // "std::vector<DrawingCanvas*>*"
QT_MOC_LITERAL(6, 85, 14) // "addCanvasFrame"

    },
    "FrameContainer\0addFrame\0\0DrawingCanvas*\0"
    "updateFrameList\0std::vector<DrawingCanvas*>*\0"
    "addCanvasFrame"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FrameContainer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void FrameContainer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FrameContainer *_t = static_cast<FrameContainer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addFrame((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 1: _t->updateFrameList((*reinterpret_cast< std::vector<DrawingCanvas*>*(*)>(_a[1]))); break;
        case 2: _t->addCanvasFrame(); break;
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
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FrameContainer::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FrameContainer::addFrame)) {
                *result = 0;
            }
        }
        {
            typedef void (FrameContainer::*_t)(std::vector<DrawingCanvas*> * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FrameContainer::updateFrameList)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject FrameContainer::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FrameContainer.data,
      qt_meta_data_FrameContainer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FrameContainer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FrameContainer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FrameContainer.stringdata0))
        return static_cast<void*>(const_cast< FrameContainer*>(this));
    return QWidget::qt_metacast(_clname);
}

int FrameContainer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void FrameContainer::addFrame(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FrameContainer::updateFrameList(std::vector<DrawingCanvas*> * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
