/**
 * Filename: preview.h
 * Author: Terrifying Nitpickers
 * Date: 3 April 2016
 */
#include "preview.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QObject>
#include <QDebug>

Preview::Preview(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    scrollLayout = new QVBoxLayout();
    previewArea = new QScrollArea(this);
    previewArea->setLayout(scrollLayout);
    previewArea->setContentsMargins(0, 0, 0, 0);
    stack = new QStackedWidget(previewArea);
    scrollLayout->addWidget(stack);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setMaximum(100);
    slider->setMinimum(1);
    slider->setValue(60);
    this->setBaseSize(200, 200);
    layout->addWidget(slider);
    layout->addWidget(previewArea);
    //layout->addWidget(actualSizeCheckbox);
    tempFrameIndex = 0;
    timer = new QTimer(this);
    connect(slider, &QSlider::valueChanged, this, &Preview::fpsChange);
    connect(timer, &QTimer::timeout, this, &Preview::canvasDisplay);
    timer->start(1000 / slider->value());
    update();

}

Preview::~Preview() {
    for (auto const &item : canvasMap) {
        deleteScene(item.first);
    }
    delete stack;
    delete scrollLayout;
    delete previewArea;
    delete slider;
    delete layout;
    delete timer;
}

void Preview::fpsChange(int value) {
    timer->stop();
    timer->start(1000 / value);
}

void Preview::canvasDisplay() {
    stack->setCurrentIndex(tempFrameIndex);
    tempFrameIndex++;
    if (tempFrameIndex >= (stack->count())) {
        tempFrameIndex = 0;
    }
}

void Preview::addCanvas(DrawingCanvas *previewCanvas, int pos) {
    qDebug() << previewCanvas->getWidth() << "preview," <<
    previewCanvas->getHeight();
    QGraphicsView *view = new QGraphicsView(previewCanvas->scene(), this);
    canvasMap[previewCanvas] = view;
    stack->resize(previewCanvas->getWidth(), previewCanvas->getHeight());

    view->resize(previewCanvas->getWidth(), previewCanvas->getHeight());
//    view->fitInView(view->scene()->itemsBoundingRect()
//                                     ,Qt::KeepAspectRatioByExpanding);
    stack->insertWidget(pos, view);
}

void Preview::deleteScene(DrawingCanvas *deleteScene) {
    QGraphicsView *tmpCanvas = canvasMap.find(deleteScene)->second;
    canvasMap.erase(deleteScene);
    stack->removeWidget(tmpCanvas);
    delete tmpCanvas;

}

void Preview::moveCanvasUp(DrawingCanvas *thisCanvas) {
    QGraphicsView *currentCanvas = canvasMap.find(thisCanvas)->second;
    int index = stack->indexOf(currentCanvas);
    if (index > 0) {
        QGraphicsView *tmpCanvas = dynamic_cast<QGraphicsView *>(stack->widget(
                index - 1));
        stack->removeWidget(stack->widget(index - 1));
        stack->insertWidget(index, tmpCanvas);
    }
}

void Preview::moveCanvasDown(DrawingCanvas *thisCanvas) {
    QGraphicsView *currentCanvas = canvasMap.find(thisCanvas)->second;
    int index = stack->indexOf(currentCanvas);
    if (index < (stack->count() - 1)) {
        QGraphicsView *tmpCanvas = dynamic_cast<QGraphicsView *>(stack->widget(
                index + 1));
        stack->removeWidget(stack->widget(index + 1));
        stack->insertWidget(index, tmpCanvas);
    }
}

void Preview::setCanvasSize(size_t x, size_t y) {
    drawingHeight = y;
    drawingWidth = x;
    qDebug() << x << ", " << y;
}


