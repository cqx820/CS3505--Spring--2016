/**
 * Filename: tool.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description:
 */

#ifndef TOOL_H
#define TOOL_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include "define.h"
#include "drawingcanvas.h"

class Tool : public QObject {
Q_OBJECT

public:
    virtual QString getName();

signals:

public slots:

    virtual void mouseMove(ToolEvent *) = 0;

    virtual void mousePress(ToolEvent *) = 0;

    virtual void mouseRelease(ToolEvent *) = 0;

    //virtual void keyPress(DrawingCanvas*, QColor) = 0;
    //virtual void keyRelease(DrawingCanvas*, QColor) = 0;
protected:
    QString name;
};


#endif // TOOL_H
