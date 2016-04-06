/**
 * Filename: modtroller.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description: This is the model controller portion of an MVC architecture for
 * the Spritet project
 */

#ifndef MODTROLLER_H
#define MODTROLLER_H

#include <QApplication>
#include <QColor>
#include <QObject>
#include <vector>
#include <QString>
#include <QDebug>
#include "define.h"
#include "drawingcanvas.h"
#include "spritetgui.h"
#include "tool.h"

class SpritetGUI;

class ModTroller : public QObject {
Q_OBJECT

public:
    explicit ModTroller();

    ~ModTroller();

    /*
     * Returns the last frame added. Mostly for testing purposes.
     */
    DrawingCanvas *getLastFrame();

    int initView(int, char *argv[]);

public slots:

    void mouseEventHandler(int x, int y);

    DrawingCanvas *addNewFrame(int);

    void removeFrame(DrawingCanvas *);

    void moveFrameUp(DrawingCanvas *);

    void moveFrameDown(DrawingCanvas *);

    void setFrameSize(size_t x, size_t y);

    void mousePressed(DrawingCanvas *, QPointF *, QMouseEvent *);

    void mouseMoved(DrawingCanvas *, QPointF *, QMouseEvent *);

    void mouseReleased(DrawingCanvas *, QPointF *, QMouseEvent *);

    void keyPressed(QKeyEvent *);

    void keyReleased(QKeyEvent *);

    void toolSelected(Tool *);

    void switchPrimaryAndSecondaryColor();

    void changePrimaryColor(QColor);

    void changePenSize(int value);

    void saveToFile(QString filename);

    void loadFromFile(QString filename);

    void exportToGif(QString filename);

    void hotkeyClicked(int);

    void addCanvasFrame();

signals:

    void toolPressed(ToolEvent *);

    void toolMoved(ToolEvent *);

    void toolReleased(ToolEvent *);

    void frameAdded(DrawingCanvas *);

    void frameSizeSetted(size_t x, size_t y);

    void setHotkey(int, Tool *);

    void updateFrameList(std::vector<DrawingCanvas *> *);

private:
    QApplication *spritet;
    SpritetGUI *view;

    std::vector<DrawingCanvas *> frames;

    QColor *currentColor = Q_NULLPTR;
    QColor *secondaryColor = Q_NULLPTR;

    Tool *currentTool;

    //The number of pixels in the IMAGE BEING WORKED ON
    size_t drawingWidth;
    size_t drawingHeight;

    int penSize;
    bool shiftHeld = false;

    void initTool();
};

#endif // MODTROLLER_H
