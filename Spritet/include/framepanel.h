/**
 * Filename: framepanel.h
 * Author: Terrifying Nitpickers
 * Date: 3 April 2016
 * Description: Dockwidget that contains the preview and thumbnail list of
 * DrawingCanvas. Allows users to add, delete, select which panel to show in the
 * preview, and change the order of canvas
 */

#ifndef FRAMEPANEL_H
#define FRAMEPANEL_H

#include <QDockWidget>
#include <QPushButton>
#include <QWidget>
#include <stdlib.h>
#include <preview.h>
#include "drawingcanvas.h"
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QListWidget>
#include <map>
#include <vector>

class FramePanel : public QDockWidget {
Q_OBJECT

public:
    FramePanel(QWidget *parent = Q_NULLPTR);

    ~FramePanel();

signals:

    //Tells SpritetGUI to add frame to index num
    void addFrameToGUI(int num);

    //Signal events to Controller and Preview
    void removeFrameSignal(DrawingCanvas *);

    void moveUpFrameSignal(DrawingCanvas *);

    void moveDownFrameSignal(DrawingCanvas *);

    //Signals to Preview only
    void frameChecked(DrawingCanvas *, int row);

    void frameUnchecked(DrawingCanvas *);

    void addFrameSignalToPreview(DrawingCanvas *, int num);

    void frameSizeSetted(size_t x, size_t y);

public slots:

    void addFrame(DrawingCanvas *frame);

    void removeFrame(DrawingCanvas *frame);

    void moveFrameUp(DrawingCanvas *frame);

    void moveFrameDown(DrawingCanvas *frame);

    void changeVisiblity(DrawingCanvas *frame, bool visibility);

private:
    virtual QSize sizeHint() const;

    Preview *animationPreview;
    QVBoxLayout *layout;
    std::map<DrawingCanvas *, QListWidgetItem *> canvasThumbnailMap;
    std::vector<DrawingCanvas *> canvasList;
    QWidget *parent;
    QListWidget *thumbnailList;
    QWidget *framePanel;
    QHBoxLayout *buttonsLayout;
    QPushButton *addButton;
    QPushButton *removeButton;
};

#endif // FRAMEPANEL_H
