/****************************************************************************
** Meta object code from reading C++ file 'drawingcanvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../A7/include/drawingcanvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawingcanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DrawingCanvas_t {
    QByteArrayData data[22];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawingCanvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawingCanvas_t qt_meta_stringdata_DrawingCanvas = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DrawingCanvas"
QT_MOC_LITERAL(1, 14, 12), // "mousePressed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "DrawingCanvas*"
QT_MOC_LITERAL(4, 43, 8), // "QPointF*"
QT_MOC_LITERAL(5, 52, 12), // "QMouseEvent*"
QT_MOC_LITERAL(6, 65, 5), // "event"
QT_MOC_LITERAL(7, 71, 12), // "mouseDragged"
QT_MOC_LITERAL(8, 84, 13), // "mouseReleased"
QT_MOC_LITERAL(9, 98, 12), // "frameChanged"
QT_MOC_LITERAL(10, 111, 8), // "setPixel"
QT_MOC_LITERAL(11, 120, 1), // "x"
QT_MOC_LITERAL(12, 122, 1), // "y"
QT_MOC_LITERAL(13, 124, 4), // "size"
QT_MOC_LITERAL(14, 129, 4), // "QRgb"
QT_MOC_LITERAL(15, 134, 5), // "color"
QT_MOC_LITERAL(16, 140, 8), // "getPixel"
QT_MOC_LITERAL(17, 149, 11), // "showPreview"
QT_MOC_LITERAL(18, 161, 20), // "std::vector<QPointF>"
QT_MOC_LITERAL(19, 182, 6), // "pixels"
QT_MOC_LITERAL(20, 189, 12), // "clearPreview"
QT_MOC_LITERAL(21, 202, 6) // "redraw"

    },
    "DrawingCanvas\0mousePressed\0\0DrawingCanvas*\0"
    "QPointF*\0QMouseEvent*\0event\0mouseDragged\0"
    "mouseReleased\0frameChanged\0setPixel\0"
    "x\0y\0size\0QRgb\0color\0getPixel\0showPreview\0"
    "std::vector<QPointF>\0pixels\0clearPreview\0"
    "redraw"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawingCanvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,
       7,    3,   66,    2, 0x06 /* Public */,
       8,    3,   73,    2, 0x06 /* Public */,
       9,    1,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    4,   83,    2, 0x0a /* Public */,
      16,    2,   92,    2, 0x0a /* Public */,
      17,    3,   97,    2, 0x0a /* Public */,
      20,    0,  104,    2, 0x0a /* Public */,
      21,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    6,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Int, 0x80000000 | 14,   11,   12,   13,   15,
    QMetaType::QColor, QMetaType::Int, QMetaType::Int,   11,   12,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Int, 0x80000000 | 14,   19,   13,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DrawingCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DrawingCanvas *_t = static_cast<DrawingCanvas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePressed((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< QPointF*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 1: _t->mouseDragged((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< QPointF*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 2: _t->mouseReleased((*reinterpret_cast< DrawingCanvas*(*)>(_a[1])),(*reinterpret_cast< QPointF*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 3: _t->frameChanged((*reinterpret_cast< DrawingCanvas*(*)>(_a[1]))); break;
        case 4: _t->setPixel((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QRgb(*)>(_a[4]))); break;
        case 5: { QColor _r = _t->getPixel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QColor*>(_a[0]) = _r; }  break;
        case 6: _t->showPreview((*reinterpret_cast< std::vector<QPointF>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QRgb(*)>(_a[3]))); break;
        case 7: _t->clearPreview(); break;
        case 8: _t->redraw(); break;
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
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DrawingCanvas::*_t)(DrawingCanvas * , QPointF * , QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawingCanvas::mousePressed)) {
                *result = 0;
            }
        }
        {
            typedef void (DrawingCanvas::*_t)(DrawingCanvas * , QPointF * , QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawingCanvas::mouseDragged)) {
                *result = 1;
            }
        }
        {
            typedef void (DrawingCanvas::*_t)(DrawingCanvas * , QPointF * , QMouseEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawingCanvas::mouseReleased)) {
                *result = 2;
            }
        }
        {
            typedef void (DrawingCanvas::*_t)(DrawingCanvas * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DrawingCanvas::frameChanged)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject DrawingCanvas::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_DrawingCanvas.data,
      qt_meta_data_DrawingCanvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DrawingCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawingCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DrawingCanvas.stringdata0))
        return static_cast<void*>(const_cast< DrawingCanvas*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int DrawingCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void DrawingCanvas::mousePressed(DrawingCanvas * _t1, QPointF * _t2, QMouseEvent * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DrawingCanvas::mouseDragged(DrawingCanvas * _t1, QPointF * _t2, QMouseEvent * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DrawingCanvas::mouseReleased(DrawingCanvas * _t1, QPointF * _t2, QMouseEvent * _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DrawingCanvas::frameChanged(DrawingCanvas * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
