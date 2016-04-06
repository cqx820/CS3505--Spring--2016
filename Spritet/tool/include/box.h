/**
 * Filename: box.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description:
 */

#ifndef BOXTOOL_H
#define BOXTOOL_H

#include <QObject>
#include "tool.h"

class BoxTool : public Tool {
public:
    BoxTool();

    /**
     * Generate the pixels forming the box between (startX, startY) and (endX, endY)
     * @return
     */
    std::vector<QPointF> generateBox(double startX, double endX,
                                     double startY, double endY);

    std::vector<QPointF> generateFilledBox(double startX, double endX,
                                           double startY, double endY);

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);

protected:
    QPointF *startCoordinates;
};

#endif // BOXTOOL_H
