/**
 * Filename: eraser.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */
#include "eraser.h"
#include "drawingcanvas.h"
#include "QPointF"
#include <QDebug>
#include <QRgb>
#include <QGraphicsView>

EraserTool::EraserTool() {
    name = Tool::tr("Eraser");
}

void EraserTool::mouseMove(ToolEvent *toolEvent) {
    QPointF coordinates = toolEvent->canvas->mapToScene(
            toolEvent->event->pos());
    toolEvent->canvas->setPixel(coordinates.x(), coordinates.y(),
                                toolEvent->penSize, qRgba(255, 255, 255, 0));
    toolEvent->canvas->redraw();
}

void EraserTool::mousePress(ToolEvent *toolEvent) {

    QPointF coordinates = toolEvent->canvas->mapToScene(
            toolEvent->event->pos());
    toolEvent->canvas->setPixel(coordinates.x(), coordinates.y(),
                                toolEvent->penSize, qRgba(255, 255, 255, 0));
    toolEvent->canvas->redraw();
}

void EraserTool::mouseRelease(ToolEvent *) {
}
