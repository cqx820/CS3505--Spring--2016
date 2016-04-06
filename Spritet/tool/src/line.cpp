/**
 * Filename: line.cpp
 * Author: Terrifying Nitpickers
 * Date: 19 March 2016
 */

#include <QDebug>
#include <QPointF>
#include "line.h"
#include "math.h"

LineTool::LineTool() {
    name = Tool::tr("Line");
}

void LineTool::mouseMove(ToolEvent *event) {
    std::vector<QPointF> points = generateLine(startCoordinates->x(),
                                               event->coordinates->x(),
                                               startCoordinates->y(),
                                               event->coordinates->y());
    event->canvas->clearPreview();
    event->canvas->showPreview(points, event->penSize, event->color->rgba());
}

void LineTool::mousePress(ToolEvent *event) {
    startCoordinates = new QPointF(*(event->coordinates));
}

void LineTool::mouseRelease(ToolEvent *event) {
    std::vector<QPointF> points = generateLine(startCoordinates->x(),
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

std::vector<QPointF> LineTool::generateLine(double startX, double endX,
                                            double startY, double endY) {
    std::vector<QPointF> toReturn;


    if (startX > endX) {
        double temp = endX;
        endX = startX;
        startX = temp;
        temp = endY;
        endY = startY;
        startY = temp;
    }


    //Bresenham's algorithm for line drawing
    if ((int) startX == (int) endX) {
        if (startY > endY) {
            double temp = endY;
            endY = startY;
            startY = temp;
        }
        //The algorithm does not work when the line is vertical.
        for (int paintY = startY; paintY < endY; paintY++) {
            toReturn.push_back(QPointF(startX, paintY));
        }
    } else {
        double error = 0;
        double slope = (endY - startY) / (endX - startX);
        double deltaError = fabs(slope);
        double paintY = startY;
        for (double step = startX; step < endX; step++) {
            toReturn.push_back(QPointF(step, paintY));
            error = error + deltaError;
            while (error >= 0.5) {
                toReturn.push_back(QPointF(step, paintY));
                paintY = paintY + (slope / deltaError);
                error = error - 1;
            }
        }
    }
    return toReturn;
}

