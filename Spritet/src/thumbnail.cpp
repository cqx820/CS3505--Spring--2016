/**
 * Filename: thumbnail.cpp
 * Author: Terrifying Nitpickers
 * Date: 4 April 2016
 */

#include "thumbnail.h"
#include "drawingcanvas.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

Thumbnail::Thumbnail(QWidget *, DrawingCanvas *panel) {
    layout = new QHBoxLayout(this);
    visible = true;
    canvas = panel;
    checkbox = new QCheckBox(this);
    checkbox->setChecked(visible);
    connect(checkbox, &QCheckBox::stateChanged, this,
            &Thumbnail::checkBoxChanged);

    view = new QGraphicsView(canvas->scene(), this);
    view->fitInView(view->scene()->itemsBoundingRect(),
                    Qt::KeepAspectRatioByExpanding);
    view->setFixedSize(100, 100);
    upButton = new QPushButton("^", this);
    downButton = new QPushButton("v", this);
    connect(upButton, &QPushButton::clicked, this, &Thumbnail::upButtonPressed);
    connect(downButton, &QPushButton::clicked, this,
            &Thumbnail::downButtonPressed);

    buttons = new QVBoxLayout();
    buttons->addWidget(upButton);
    buttons->addWidget(downButton);
    layout->addWidget(checkbox);
    layout->addWidget(view);
    layout->addLayout(buttons);

}

Thumbnail::~Thumbnail() {
    delete upButton;
    delete downButton;
    delete buttons;
    delete view;
    delete checkbox;
    delete layout;
}

QSize  Thumbnail::sizeHint() const {
    QSize theSize(200, 100);
    return theSize;
}

void Thumbnail::upButtonPressed() {
    emit moveUp(canvas);
}

void Thumbnail::downButtonPressed() {
    emit moveDown(canvas);
}

void Thumbnail::checkBoxChanged() {
    visible = !visible;
    emit changeVisibility(canvas, visible);
}

bool Thumbnail::isChecked() {
    return visible;
}
