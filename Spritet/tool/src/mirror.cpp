/**
 * Filename: mirror.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */

#include "mirror.h"
#include "define.h"
#include <QDebug>

MirrorTool::MirrorTool() {
    name = Tool::tr("Mirror Pencil");
}

void MirrorTool::mouseMove(ToolEvent *event) {
    //get the dimensions of the canvas
    qreal midpoint;
    if (event->shiftHeld) {
        midpoint = event->canvas->scene()->height() / 2;
    } else {
        midpoint = event->canvas->scene()->width() / 2;
    }

    //based on mouse event, calculate the second point
    // first copy the same values
    qreal x2 = event->coordinates->x();
    qreal y2 = event->coordinates->y();
    // overwrite the one that needs to be mirrored
    //if shift key
    if (event->shiftHeld) {
        y2 = midpoint + (midpoint - y2);
    } else {
        x2 = midpoint + (midpoint - x2);
    }

    //Draw both points
    event->canvas->setPixel(event->coordinates->x(), event->coordinates->y(),
                            event->penSize, event->color->rgba());
    event->canvas->setPixel(x2, y2,
                            event->penSize, event->color->rgba());

    event->canvas->redraw();
}

void MirrorTool::mousePress(ToolEvent *event) {
    mouseMove(event);
}

void MirrorTool::mouseRelease(ToolEvent *) {
}

