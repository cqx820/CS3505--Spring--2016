/**
 * Filename: line.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description: This tool draws a reasonably straight line from where the user
 * initially clicks to where he releases. The degree of straightness is
 * restricted based on the resolution of the drawing
 */

#ifndef LINETOOL_H
#define LINETOOL_H

#include <QObject>
#include "tool.h"

class LineTool : public Tool {
public:
    LineTool();

    /**
     * Generate the pixels between (startX, startY) and (endX, endY)
     * @return
     */
    std::vector<QPointF> generateLine(double startX, double endX,
                                      double startY, double endY);

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);

protected:
    QPointF *startCoordinates;
};

#endif // LINETOOL_H
