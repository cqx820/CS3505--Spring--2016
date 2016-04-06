/**
 * Filename: define.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description:
 */

#ifndef DEFINE_H
#define DEFINE_H

#include <string>
#include <QObject>
#include <QMouseEvent>
#include <QString>

#include "drawingcanvas.h"

const QString tools_str[] = {"Pencil", "Eraser", "Line", "Replacer",
                             "Selection", "Box", "Mirror", "Fill",
                             "LightenDarken"};

class DrawingCanvas;

struct ToolEvent {
    DrawingCanvas *canvas;
    QMouseEvent *event;
    QColor *color;
    QPointF *coordinates;
    int penSize;
    bool shiftHeld;
};

#endif // DEFINE_H

