/**
 * Filename: colourreplacer.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */
#include "colourreplacer.h"
#include <QPointF>
#include <QRgb>

ColorReplacer::ColorReplacer() {
    name = Tool::tr("Replacer");
}

void ColorReplacer::mousePress(ToolEvent *event) {
    pixel_position = new QPointF(*(event->coordinates));
    thisColor = event->canvas->getPixel(pixel_position->x(),
                                        pixel_position->y());
}

void ColorReplacer::mouseRelease(ToolEvent *event) {
    for (size_t i = 0; i < event->canvas->getHeight(); ++i) {
        for (size_t j = 0; j < event->canvas->getWidth(); ++j) {
            if (thisColor == event->canvas->getPixel(i, j)) {
                event->canvas->setPixel(i, j, 1, event->color->rgba());
            }
        }
    }
    event->canvas->redraw();
}

void ColorReplacer::mouseMove(ToolEvent *) {
}
