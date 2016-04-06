/**
 * Filename: framecontainer.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */

#include "framecontainer.h"

#include <QGridLayout>

FrameContainer::FrameContainer(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    DrawingFrame *frame = new DrawingFrame(this);

    connect(this, &FrameContainer::updateFrameList,
            frame, &DrawingFrame::updateFrameList);

    /*connect(frame, &DrawingFrame::mouseDragged,
            this, &FrameContainer::mouseDragged);

    connect(frame, &DrawingFrame::mousePressed,
            this, &FrameContainer::mousePressed);

    connect(frame, &DrawingFrame::mouseReleased,
            this, &FrameContainer::mouseReleased);*/

    frames.push_back(frame);

    layout->addWidget(frame, 0, 0, 1, 1);

    setLayout(layout);

    show();
}

FrameContainer::~FrameContainer() {
    for (auto drawingFrame : frames) {
        delete drawingFrame;
    }

    delete layout;
}

void FrameContainer::addDrawingFrame(int row, int col, int rowSpan,
                                     int colSpan) {
    DrawingFrame *frame = new DrawingFrame(this);

    connect(this, &FrameContainer::updateFrameList,
            frame, &DrawingFrame::updateFrameList);

    /*connect(frame, &DrawingFrame::mouseDragged,
            this, &FrameContainer::mouseDragged);

    connect(frame, &DrawingFrame::mousePressed,
            this, &FrameContainer::mousePressed);

    connect(frame, &DrawingFrame::mouseReleased,
            this, &FrameContainer::mouseReleased);*/

    layout->addWidget(frame, row, col, rowSpan, colSpan);
    frames.push_back(frame);
}

void FrameContainer::addCanvasFrame() {
    switch (frames.size()) {
        case 1:
            addDrawingFrame(0, 1, 1, 1);
            break;
        case 2:
            addDrawingFrame(1, 0, 1, 1);
            break;
        case 3:
            addDrawingFrame(1, 1, 1, 1);
            break;
        default:
            break;
    }
}

