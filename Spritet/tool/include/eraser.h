/**
 * Filename: eraser.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description: This tool erases pensize number of pixels by setting
 *  them to white and trasparent.
 */
#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include <QObject>
#include <drawingcanvas.h>

#include "tool.h"

class EraserTool : public Tool {
public:
    EraserTool();

public slots:

    void mouseMove(ToolEvent *event);

    void mousePress(ToolEvent *event);

    void mouseRelease(ToolEvent *event);

private:
};

#endif // ERASERTOOL_H
