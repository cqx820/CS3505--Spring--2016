/**
 * Filename: framepanel.h
 * Author: Terrifying Nitpickers
 * Date: 3 April 2016
 * Description: Displays a preview of the checked frames, allowing users to adjust
 * the fps at which slides are updated
 */
#ifndef PREVIEW_H
#define PREVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QSlider>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <map>
#include <QTimer>
#include <QScrollArea>
#include "drawingcanvas.h"

class Preview : public QWidget {
Q_OBJECT
public:
    explicit Preview(QWidget *parent = 0);

    ~Preview();

private:
    QScrollArea *previewArea;
    QSlider *slider;
    QGraphicsView *previewCanvas;
    QCheckBox *actualSizeCheckbox;
    QStackedWidget *stack;
    std::map<DrawingCanvas *, QGraphicsView *> canvasMap;
    QVBoxLayout *layout;
    QVBoxLayout *scrollLayout;
    QTimer *timer;
    int tempFrameIndex;
    size_t drawingWidth;
    size_t drawingHeight;

public slots:

    void deleteScene(DrawingCanvas *scene);

    void addCanvas(DrawingCanvas *previewCanvas, int i);

    void moveCanvasUp(DrawingCanvas *thisCanvas);

    void moveCanvasDown(DrawingCanvas *thisCanvas);

    void fpsChange(int value);

    void canvasDisplay();

    void setCanvasSize(size_t x, size_t y);
};

#endif // PREVIEW_H
