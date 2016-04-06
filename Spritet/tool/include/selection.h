/**
 * Filename: selection.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description: This tool allows users to drag to select and click to paste,
 * after which the tool resets.
 */
#ifndef SELECTION_H
#define SELECTION_H

#include "eraser.h"
#include <QPointF>

class SelectionTool : public Tool {
public:
    SelectionTool();

public slots:

    void mouseMove(ToolEvent *event);

    void mousePress(ToolEvent *event);

    void mouseRelease(ToolEvent *event);

private:
    //Reflects which stage the user is at in the press, drag,
    // release ( aka select) and press, release (aka click) sequence
    int stage;
    std::vector<std::vector<unsigned int>> selected;
    QPointF startPoint;
    QPointF endPoint;
};

#endif // SELECTION_H
