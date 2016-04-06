/**
 * Filename: box.cpp
 * Author: Terrifying Nitpickers
 * Date: 2 April 2016
 */

#include "box.h"

#include <QDebug>
#include "define.h"

BoxTool::BoxTool() {
    name = Tool::tr("Box");
}

void BoxTool::mouseMove(ToolEvent *event) {
    if (event->shiftHeld && Qt::ShiftModifier) {
        std::vector<QPointF> points = generateFilledBox(startCoordinates->x(),
                                                        event->coordinates->x(),
                                                        startCoordinates->y(),
                                                        event->coordinates->y());
    }
    std::vector<QPointF> points = generateBox(startCoordinates->x(),
                                              event->coordinates->x(),
                                              startCoordinates->y(),
                                              event->coordinates->y());
    event->canvas->clearPreview();
    event->canvas->showPreview(points, event->penSize, event->color->rgba());
}

void BoxTool::mousePress(ToolEvent *event) {
    startCoordinates = new QPointF(*(event->coordinates));
}

void BoxTool::mouseRelease(ToolEvent *event) {
    if (event->shiftHeld && Qt::ShiftModifier) {
        std::vector<QPointF> points = generateFilledBox(startCoordinates->x(),
                                                        event->coordinates->x(),
                                                        startCoordinates->y(),
                                                        event->coordinates->y());
    }

    std::vector<QPointF> points = generateBox(startCoordinates->x(),
                                              event->coordinates->x(),
                                              startCoordinates->y(),
                                              event->coordinates->y());

    for (QPointF point : points) {
        event->canvas->setPixel(point.x(), point.y(), event->penSize,
                                event->color->rgba());
    }
    event->canvas->clearPreview();
    event->canvas->redraw();
}


std::vector<QPointF> BoxTool::generateBox(double startX, double endX,
                                          double startY, double endY) {
    std::vector<QPointF> toReturn;


    if (startX > endX) {
        double temp = endX;
        endX = startX;
        startX = temp;
    }
    if (startY > endY) {
        double temp = endY;
        endY = startY;
        startY = temp;
    }

    for (double x = startX; x <= endX; x++) {
        toReturn.push_back(QPointF(x, startY));
        toReturn.push_back(QPointF(x, endY));
    }

    for (double y = startY; y <= endY; y++) {
        toReturn.push_back(QPointF(startX, y));
        toReturn.push_back(QPointF(endX, y));
    }

    return toReturn;
}


std::vector<QPointF> BoxTool::generateFilledBox(double startX, double endX,
                                                double startY, double endY) {
    std::vector<QPointF> toReturn;


    if (startX > endX) {
        double temp = endX;
        endX = startX;
        startX = temp;
    }
    if (startY > endY) {
        double temp = endY;
        endY = startY;
        startY = temp;
    }

    for (double x = startX; x <= endX; x++) {
        for (double y = startY; y <= endY; y++) {
            toReturn.push_back(QPointF(x, y));
        }
    }


    return toReturn;
}

