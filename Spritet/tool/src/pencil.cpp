/**
 * Filename: pencil.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */

#include <QDebug>
#include "define.h"
#include "pencil.h"

PencilTool::PencilTool() {
    name = Tool::tr("Pencil");
}

void PencilTool::mouseMove(ToolEvent *event) {
    event->canvas->setPixel(event->coordinates->x(), event->coordinates->y(),
                            event->penSize, event->color->rgba());
    event->canvas->redraw();
}

void PencilTool::mousePress(ToolEvent *event) {
    mouseMove(event);
}

void PencilTool::mouseRelease(ToolEvent *) {
}

