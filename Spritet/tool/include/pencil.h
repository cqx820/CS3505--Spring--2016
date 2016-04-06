/**
 * Filename: pencil.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description: This draws a dot where the user clicks. If the user clicks and
 * drags, it will continue drawing dots
 */

#ifndef PENCILTOOL_H
#define PENCILTOOL_H

#include <QObject>
#include "tool.h"

class PencilTool : public Tool {
public:
    PencilTool();

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);
};

#endif // PENCILTOOL_H
