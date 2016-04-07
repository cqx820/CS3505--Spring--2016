/**
 * Filename: drawingframe.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */
#include "drawingframe.h"

#include <QAction>
#include <QVBoxLayout>
#include <QComboBox>

#include "drawingcanvas.h"

DrawingFrame::DrawingFrame(QWidget *parent) : QWidget(parent) {
    /*canvas = new DrawingCanvas(50,50);
    canvas->fitInView(canvas->scene()->itemsBoundingRect(),Qt::KeepAspectRatio);*/

    frames = new QComboBox(this);
    frames->addItem(("Select Frame"));

    connect(frames, static_cast<void (QComboBox::*)(
                    int)>(&QComboBox::currentIndexChanged),
            this, &DrawingFrame::indexChanged);

    layout = new QVBoxLayout(this);

    layout->addWidget(frames);
//    layout->addWidget(canvas);

    setLayout(layout);

    frames->show();

    show();
}

DrawingFrame::~DrawingFrame() {
    delete canvases;
    delete frames;
    delete layout;
}

void DrawingFrame::updateFrameList(std::vector<DrawingCanvas *> *frameList) {
    canvases = frameList;
    frames->clear();

    qDebug() << "foo: " << frameList->size();

    frames->addItem(tr("Select Frame"));

    for (size_t i = 1; i <= frameList->size(); i++) {
        frames->addItem("Frame " + QString::number(i));
    }
}

void DrawingFrame::indexChanged(int n) {
    if (canvases->size() > 0 && n >= 1) {

        if (canvas != Q_NULLPTR) {
            canvas->hide();
        }

        layout->removeWidget(canvas);

        canvas = canvases->at(n - 1);
        layout->addWidget(canvas);
        canvas->fitInView(canvas->scene()->itemsBoundingRect(),
                          Qt::KeepAspectRatio);
        canvas->show();
//        layout->update();

        update();
    } else if (n == 0) {
        if (canvas != Q_NULLPTR) {
            canvas->hide();
        }

        layout->removeWidget(canvas);

    }
}
