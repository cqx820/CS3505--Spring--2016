/**
 * Filename: fill.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */

#include "fill.h"

#include <QDebug>
#include "define.h"

FillTool::FillTool() {
    name = Tool::tr("Fill");
}

void FillTool::mouseMove(ToolEvent *event) {
    QColor oldColor = event->canvas->getPixel(event->coordinates->x(),
                                              event->coordinates->y());
    if(event->color->rgb() == oldColor.rgb()) {
        return;
    }

    fillArea(event, event->coordinates->x(), event->coordinates->y(), oldColor);

    event->canvas->setPixel(event->coordinates->x(), event->coordinates->y(),
                            event->penSize, event->color->rgba());
    event->canvas->redraw();
}

void FillTool::mousePress(ToolEvent *event) {
    mouseMove(event);
}

void FillTool::mouseRelease(ToolEvent *) {
}


void FillTool::fillArea(ToolEvent *event, int x, int y, QColor oldColor) {
    if (x < 0 || x >= event->canvas->scene()->width() || y < 0 ||
        y >= event->canvas->scene()->height()) {
        return;
    }

    if (event->canvas->getPixel(x, y) == oldColor) {
        event->canvas->setPixel(x, y, 1, event->color->rgba());
    } else {
        return;
    }

    fillArea(event, x - 1, y, oldColor);
    fillArea(event, x, y + 1, oldColor);
    fillArea(event, x + 1, y, oldColor);
    fillArea(event, x, y - 1, oldColor);

}
