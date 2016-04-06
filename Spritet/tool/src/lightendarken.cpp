/**
 * Filename: lightendarken.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */

#include "lightendarken.h"

#include <QDebug>
#include "define.h"

LightenDarkenTool::LightenDarkenTool() {
    name = Tool::tr("Lighten/Darken");
}

void LightenDarkenTool::mouseMove(ToolEvent *event) {
    qreal x = event->coordinates->x();
    qreal y = event->coordinates->y();
    int size = event->penSize;

    //copied from the drawingCanvas and modified a bit, since we need a
    // custom behaviour for each pixel within our radius
    int currentSize = size;

    if (size % 2 == 0) {
        currentSize -= 1; // even sizes have too many dynamic needs/buggy af
    }
    // We will have to go this far from the center
    { //empty bracket for scope
        int distance = (int) ((currentSize - 1) / 2.0);
        int paintX = (int) x - distance;
        int paintY = (int) y - distance;
        while (true) {
            QColor currentPixel = QColor(event->canvas->getPixel(paintX,
                                                                 paintY));
            if (currentPixel.alpha() != 0) { //don't change the pure alpha layer
                QColor newPixel = currentPixel;
                if (event->shiftHeld) { //darken
                    newPixel.setAlpha(currentPixel.alpha() + 10);
                } else { //lighten
                    newPixel.setAlpha(currentPixel.alpha() - 10);
                }
                event->canvas->setPixel(paintX, paintY, 1,
                                        newPixel.rgba());
            }
            paintX = paintX + 1;
            if (paintX > x + distance) {
                paintX = (int) x - distance;
                paintY = paintY + 1;
                if (paintY > y + distance) {
                    break;
                }
            }
        }
    }

    event->canvas->redraw();
}

void LightenDarkenTool::mousePress(ToolEvent *event) {
    mouseMove(event);
}

void LightenDarkenTool::mouseRelease(ToolEvent *) {
}

