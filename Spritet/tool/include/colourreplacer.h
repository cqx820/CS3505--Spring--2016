/**
 * Filename: colourreplacer.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */
#ifndef COLORREPLACER_H
#define COLORREPLACER_H

#include <QObject>
#include <QColor>
#include <QPointF>
#include "tool.h"

class ColorReplacer : public Tool {
public:
    ColorReplacer();

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);

protected:
    QColor thisColor;
    QPointF *pixel_position;
};

#endif // COLOURREPLACER_H
