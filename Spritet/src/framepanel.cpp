/**
 * Filename: framepanel.cpp
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 */

#include "framepanel.h"
#include "thumbnail.h"
#include <QDockWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QWidget>
#include <stdlib.h>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <preview.h>
#include <QScrollArea>
#include <QListWidget>
#include <QHBoxLayout>


FramePanel::FramePanel(QWidget *parent) :
        QDockWidget(parent) {
    this->setBaseSize(200, 600);
    framePanel = new QWidget(this);
    layout = new QVBoxLayout();
    //Creates an animation and connect slots for it
    animationPreview = new Preview(this);
    connect(this, &FramePanel::addFrameSignalToPreview, animationPreview,
            &Preview::addCanvas);
    connect(this, &FramePanel::removeFrameSignal, animationPreview,
            &Preview::deleteScene);
    connect(this, &FramePanel::moveDownFrameSignal, animationPreview,
            &Preview::moveCanvasDown);
    connect(this, &FramePanel::moveUpFrameSignal, animationPreview,
            &Preview::moveCanvasUp);
    connect(this, &FramePanel::frameUnchecked, animationPreview,
            &Preview::deleteScene);
    connect(this, &FramePanel::frameChecked, animationPreview,
            &Preview::addCanvas);
    connect(this, &FramePanel::frameSizeSetted, animationPreview,
            &Preview::setCanvasSize);
    //The thumbnail list contains a list of thumbnails showing all canvas in the project
    thumbnailList = new QListWidget(this);
    thumbnailList->setBaseSize(300, 800);
    //Container for add and remove buttons
    buttonsLayout = new QHBoxLayout();
    addButton = new QPushButton("+", this);
    removeButton = new QPushButton("-", this);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    //When the add button is clicked, send signal to controller to add a frame
    //after the selected frame, or to the end of the list if no frame is selected
    connect(addButton, &QPushButton::clicked, [&]() {
        if (thumbnailList->currentRow() != -1) {
            emit addFrameToGUI(thumbnailList->currentRow() + 1);
        } else {
            emit addFrameToGUI(thumbnailList->count());
        }
    });
    connect(removeButton, &QPushButton::clicked, [&]() {
        if (thumbnailList->currentRow() != -1) {
            emit removeFrameRequest(canvasList[thumbnailList->currentRow()]);
        }
    });
    layout->addWidget(animationPreview);
    layout->addWidget(thumbnailList);
    layout->addLayout(buttonsLayout);
    setWidget(framePanel);
    framePanel->setLayout(layout);
    framePanel->show();
    update();
}

FramePanel::~FramePanel() {
    delete removeButton;
    delete addButton;
    delete buttonsLayout;
    for (auto const &item : canvasThumbnailMap) {
        removeFrame(item.first);
    }
    delete thumbnailList;
    delete animationPreview;
    delete layout;
    delete framePanel;
}

QSize  FramePanel::sizeHint() const {
    QSize theSize(200, 600);
    return theSize;
}

//Slot that adds a drawingcanvas to the elements of the framepanel
void FramePanel::addFrame(DrawingCanvas *frame) {
    Thumbnail *newFrame = new Thumbnail(this, frame);
    QListWidgetItem *item = new QListWidgetItem();
    if (thumbnailList->currentRow() == -1) {
        thumbnailList->addItem(item);
        emit addFrameSignalToPreview(frame, thumbnailList->count());
        canvasList.push_back(frame);
    } else {
        thumbnailList->insertItem(thumbnailList->currentRow() + 1, item);
        emit addFrameSignalToPreview(frame, thumbnailList->currentRow() + 1);
        canvasList.insert(canvasList.begin() + thumbnailList->currentRow() + 1,
                          frame);
    }
    item->setSizeHint(newFrame->minimumSizeHint());
    thumbnailList->setItemWidget(item, newFrame);
    connect(newFrame, &Thumbnail::moveUp, this, &FramePanel::moveFrameUp);
    connect(newFrame, &Thumbnail::moveDown, this, &FramePanel::moveFrameDown);
    connect(newFrame, &Thumbnail::changeVisibility, this,
            &FramePanel::changeVisiblity);
    canvasThumbnailMap[frame] = item;
}

//Slot that removes elements from the framepanel upon signal and alerts the controller
void FramePanel::removeFrame(DrawingCanvas *frame) {
    int row = thumbnailList->currentRow();
    emit removeFrameSignal(frame);
    qDebug()<<"FramePanel remove Frame "<<frame;
    QListWidgetItem *item = canvasThumbnailMap[frame];
    QWidget *widget = thumbnailList->itemWidget(item);
    thumbnailList->takeItem(row);
    canvasThumbnailMap.erase(frame);
    delete widget;
    delete item;
    canvasList.erase(std::remove(canvasList.begin(), canvasList.end(), frame),
                     canvasList.end());
}

//Slot that moves a frame up it there is something above it. Due to the limitations
//of QListWidget, dynamic items such as thumbnails must be completely deleted and recreated
void FramePanel::moveFrameUp(DrawingCanvas *frame) {
    QListWidgetItem *item = canvasThumbnailMap[frame];
    int row = thumbnailList->row(item) - 1;
    thumbnailList->setCurrentItem(item);
    if (row >= 0) {
        QListWidgetItem *item2 = canvasThumbnailMap[canvasList[row]];
        QWidget *widget = thumbnailList->itemWidget(item2);
        thumbnailList->takeItem(row);
        canvasThumbnailMap.erase(canvasList[row]);
        delete widget;
        delete item2;

        Thumbnail *newFrame = new Thumbnail(this, canvasList[row]);
        QListWidgetItem *item3 = new QListWidgetItem();
        thumbnailList->insertItem(thumbnailList->currentRow() + 1, item3);
        item3->setSizeHint(newFrame->minimumSizeHint());
        thumbnailList->setItemWidget(item3, newFrame);
        connect(newFrame, &Thumbnail::moveUp, this, &FramePanel::moveFrameUp);
        connect(newFrame, &Thumbnail::moveDown, this,
                &FramePanel::moveFrameDown);
        connect(newFrame, &Thumbnail::changeVisibility, this,
                &FramePanel::changeVisiblity);

        canvasThumbnailMap[canvasList[row]] = item3;
        //Uses the erase-remove idiom, though each value ought to only occur once
        canvasList.erase(
                std::remove(canvasList.begin(), canvasList.end(), frame),
                canvasList.end());
        canvasList.insert(canvasList.begin() + thumbnailList->currentRow(),
                          frame);

        if ((qobject_cast<Thumbnail *>(
                thumbnailList->itemWidget(item)))->isChecked()
            && qobject_cast<Thumbnail *>(
                thumbnailList->itemWidget(item3))->isChecked()) {
            emit moveUpFrameSignal(frame);
        }
    }
}

//Slot that moves a frame down it there is something below it. Due to the limitations of QListWidget,
//dynamic items such as thumbnails must be completely deleted and recreated
void FramePanel::moveFrameDown(DrawingCanvas *frame) {
    QListWidgetItem *item = canvasThumbnailMap[frame];
    int row = thumbnailList->row(item) + 1;
    thumbnailList->setCurrentItem(item);
    if (row < thumbnailList->count()) {
        QListWidgetItem *item2 = canvasThumbnailMap[canvasList[row]];
        QWidget *widget = thumbnailList->itemWidget(item2);
        thumbnailList->takeItem(row);
        canvasThumbnailMap.erase(canvasList[row]);
        delete widget;
        delete item2;

        Thumbnail *newFrame = new Thumbnail(this, canvasList[row]);
        QListWidgetItem *item3 = new QListWidgetItem();
        thumbnailList->insertItem(thumbnailList->currentRow(), item3);
        item3->setSizeHint(newFrame->minimumSizeHint());
        thumbnailList->setItemWidget(item3, newFrame);
        connect(newFrame, &Thumbnail::moveUp, this, &FramePanel::moveFrameUp);
        connect(newFrame, &Thumbnail::moveDown, this,
                &FramePanel::moveFrameDown);
        connect(newFrame, &Thumbnail::changeVisibility, this,
                &FramePanel::changeVisiblity);

        canvasThumbnailMap[canvasList[row]] = item3;
        canvasList.erase(
                std::remove(canvasList.begin(), canvasList.end(), frame),
                canvasList.end());
        canvasList.insert(canvasList.begin() + thumbnailList->currentRow(),
                          frame);

        if ((qobject_cast<Thumbnail *>(
                thumbnailList->itemWidget(item)))->isChecked()
            && qobject_cast<Thumbnail *>(
                thumbnailList->itemWidget(item3))->isChecked()) {
            emit moveDownFrameSignal(frame);
        }
    }
}

//Slot that controls the visibility of a frame in the preview
void FramePanel::changeVisiblity(DrawingCanvas *frame, bool visibility) {
    if (!visibility) {
        emit frameUnchecked(frame);
    } else {
        //Calculate and tells preview to insert the slide at the right position
        int visibleIndex = 0;
        for (int i = 0; i < thumbnailList->count(); i++) {
            if (frame == canvasList[i]) {
                emit frameChecked(frame, visibleIndex);
            }
            if (((Thumbnail *) (thumbnailList->itemWidget(
                    thumbnailList->item(i))))->isChecked()) {
                visibleIndex++;
            }
        }
    }
}
