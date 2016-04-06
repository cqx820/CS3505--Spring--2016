/**
 * Filename: selection.cpp
 * Author: Terrifying Nitpickers
 * Date: 1 April 2016
 */
#include "selection.h"
#include <QPointF>
#include <algorithm>
#include <QRgb>

SelectionTool::SelectionTool() {
    stage = 0;
    name = Tool::tr("Selection");
}

void SelectionTool::mouseMove(ToolEvent *toolEvent) {
    int startX = startPoint.x();
    int endX = toolEvent->coordinates->x();
    int startY = startPoint.y();
    int endY = toolEvent->coordinates->y();

    if (startX > endX) {
        int temp = endX;
        endX = startX;
        startX = temp;
    }
    if (startY > endY) {
        int temp = endY;
        endY = startY;
        startY = temp;
    }

    std::vector<QPointF> points;
    for (int xdex = startX; xdex <= endX; xdex++) {
        points.push_back(QPointF(xdex, startY));
        points.push_back(QPointF(xdex, endY));
    }
    for (int ydex = startY; ydex <= endY; ydex++) {
        points.push_back(QPointF(startX, ydex));
        points.push_back(QPointF(endX, ydex));
    }
    toolEvent->canvas->clearPreview();
    toolEvent->canvas->showPreview(points, 1, qRgba(0, 0, 0, 255));
}

void SelectionTool::mousePress(ToolEvent *toolEvent) {
    toolEvent->canvas->clearPreview();
    stage++;
    if (stage == 1) {
        selected.clear();
        startPoint = toolEvent->canvas->mapToScene(toolEvent->event->pos());
    }
}

void SelectionTool::mouseRelease(ToolEvent *toolEvent) {
    toolEvent->canvas->clearPreview();
    stage++;
    if (stage == 2) {
        endPoint = toolEvent->canvas->mapToScene(toolEvent->event->pos());
        int endX = std::max(startPoint.x(), endPoint.x());
        int startX = std::min(startPoint.x(), endPoint.x());
        int endY = std::max(startPoint.y(), endPoint.y());
        int startY = std::min(startPoint.y(), endPoint.y());
        selected.resize(endY - startY + 1,
                        std::vector<unsigned int>(endX - startX + 1, 0));
        for (int y = startY; y <= endY; y++) {
            for (int x = startX; x <= endX; x++) {
                selected[y - startY][x - startX] = toolEvent->canvas->getPixel(
                        x, y).rgba();
            }
        }
    }
    if (stage == 4) {
        QPointF pastePoint = toolEvent->canvas->mapToScene(
                toolEvent->event->pos());
        for (unsigned int y = 0; y < selected.size(); y++) {
            for (unsigned int x = 0; x < selected[0].size(); x++) {
                int canvasX = pastePoint.x() + x;
                int canvasY = pastePoint.y() + y;
                toolEvent->canvas->setPixel(canvasX, canvasY, 1,
                                            selected[y][x]);
            }
        }
        toolEvent->canvas->redraw();
        stage = 0;
    }
}
