#ifndef FRAMECONTAINER_H
#define FRAMECONTAINER_H

#include <QWidget>

#include <QGridLayout>

#include "drawingcanvas.h"
#include "drawingframe.h"

class FrameContainer : public QWidget {
Q_OBJECT
public:
    explicit FrameContainer(QWidget *parent = 0);

    ~FrameContainer();

signals:

    void addFrame(DrawingCanvas *);

    void updateFrameList(std::vector<DrawingCanvas *> *);

    /*void mousePressed(DrawingCanvas*, QPointF*, QMouseEvent *event);
    void mouseDragged(DrawingCanvas*, QPointF*, QMouseEvent *event);
    void mouseReleased(DrawingCanvas*, QPointF*, QMouseEvent *event);*/

public slots:

    void addCanvasFrame();

private:
    std::vector<DrawingFrame *> frames;
    QGridLayout *layout;

    void addDrawingFrame(int, int, int, int);
};

#endif // FRAMECONTAINER_H

