/**
 * Filename: mirror.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description: This draws a dot where the user clicks as well as the mirrored sied
 * If the user clicks and
 * drags, it will continue drawing dots
 */

#ifndef MIRRORTOOL_H
#define MIRRORTOOL_H

#include <QObject>
#include "tool.h"

class MirrorTool : public Tool {
public:
    MirrorTool();

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);
};

#endif // MIRRORTOOL_H
