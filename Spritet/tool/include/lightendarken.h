/**
 * Filename: lightendarken.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 * Description:
 */

#ifndef LIGHTENDARKEN_H
#define LIGHTENDARKEN_H

#include <QObject>
#include "tool.h"

class LightenDarkenTool : public Tool {
public:
    LightenDarkenTool();

public slots:

    void mouseMove(ToolEvent *);

    void mousePress(ToolEvent *);

    void mouseRelease(ToolEvent *);
};

#endif // LIGHTENDARKEN_H
