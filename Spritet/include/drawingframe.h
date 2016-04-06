#ifndef DRAWINGFRAME_H
#define DRAWINGFRAME_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>

#include "drawingcanvas.h"

class DrawingCanvas;

class DrawingFrame : public QWidget {
Q_OBJECT

public:
    explicit DrawingFrame(QWidget *);

    ~DrawingFrame();

signals:
    /*void mousePressed(DrawingCanvas*, QPointF*, QMouseEvent *event);
    void mouseDragged(DrawingCanvas*, QPointF*, QMouseEvent *event);
    void mouseReleased(DrawingCanvas*, QPointF*, QMouseEvent *event);*/

public slots:

    void updateFrameList(std::vector<DrawingCanvas *> *);

    void indexChanged(int);

private:
    std::vector<DrawingCanvas *> *canvases;
    QComboBox *frames;
    DrawingCanvas *canvas = Q_NULLPTR;
    QVBoxLayout *layout;
};

#endif // DRAWINGFRAME_H
