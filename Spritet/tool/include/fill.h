/**
 * Filename: fill.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description: This fills in an area with the selected color
 */

#ifndef FILLTOOL_H
#define FILLTOOL_H

#include <QObject>
#include "tool.h"

class FillTool : public Tool {
public:
    FillTool();

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);

private:
    void fillArea(ToolEvent *, int, int, QColor);
};

#endif // FILLTOOL_H
