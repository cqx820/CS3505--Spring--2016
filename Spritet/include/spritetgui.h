/**
 * Filename: spritetgui.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description: This is the main GUI for the Spritet project. Ideally, the class
 * will one day be better named and this comment updated appropriately.
 */

#ifndef SPRITETGUI_H
#define SPRITETGUI_H

#include <QColorDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <stdlib.h>
#include <QDebug>
#include "drawingcanvas.h"
#include "drawingframe.h"
#include "framecontainer.h"
#include "framepanel.h"
#include "menu.h"
#include "tool.h"
#include "toolbox.h"
#include "hotkeypanel.h"

class Menu;

class ToolBox;

class FrameContainer;

class SpritetGUI : public QMainWindow {
Q_OBJECT

public:
    explicit SpritetGUI(QWidget *parent = Q_NULLPTR);

    ~SpritetGUI();

    ToolBox *getToolbox() { return toolbox; }

    FramePanel *getFramepanel() { return framepanel; }

    HotkeyPanel *getHotkey() { return hotkeypanel; }

    void hideToolbox();

public slots:

//    void mouseEventHandler(double x, double y);
    void setStatusBarText(QString text);

    void newFrame(int);

    void addNewFrameToGUI(DrawingCanvas *);

    void removeFrameFromGUI(DrawingCanvas *);

    void loadTriggered();

    void saveAsTriggered();

    void saveTriggered();

    void exportTriggered();

    void getFrameSize();

signals:

    void switchColorsButtonClicked();

    void keyPressed(QKeyEvent *);

    void keyReleased(QKeyEvent *);

    void addFrameRequest(int);

    void removeFrameSignal(DrawingCanvas *);

    void moveFrameUp(DrawingCanvas *);

    void moveFrameDown(DrawingCanvas *);

    void setTool(Tool *);

    void mousePressed(DrawingCanvas *, QPointF *, QMouseEvent *);

    void mouseMoved(DrawingCanvas *, QPointF *, QMouseEvent *);

    void mouseReleased(DrawingCanvas *, QPointF *, QMouseEvent *);

    void addFrame(DrawingCanvas *);

    void frameSizeSet(size_t x, size_t y);

    void penSizeChanged(int value);

    void primaryColorChanged(QColor);

    void saveToFileSignal(QString);

    void loadFromFileSignal(QString);

    void saveFileSignal(QString);

    void exportToFileSignal(QString);

    void hotkeyClicked(int);

    void setHotkey(int, Tool *);

    void hotkeyNumber(int);

    void applyHotkey(Tool *);

    void addCanvasFrame();

    void updateFrameList(std::vector<DrawingCanvas *> *);

protected:
    virtual void keyPressEvent(QKeyEvent *);

    virtual void keyReleaseEvent(QKeyEvent *);

private:
    Menu *menu;
    std::vector<FrameContainer *> frames;
    ToolBox *toolbox;
    FramePanel *framepanel;
    HotkeyPanel *hotkeypanel;

    void initMenu();

    bool vimMode;
    QString vimBuffer;
    QString filename;
};

#endif // SpritetGUI_H
