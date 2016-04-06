/**
 * Filename: spritetgui.cpp
 * Author: Terrifying Nitpickers
 * Date: 4 April 2016
 */

#include <QKeyEvent>
#include <QMainWindow>
#include <QMenuBar>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QStatusBar>
#include <stdlib.h>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include "drawingcanvas.h"
#include "drawingframe.h"
#include "spritetgui.h"
#include "framecontainer.h"
#include "framepanel.h"
#include "menu.h"
#include "tool.h"
#include "toolbox.h"

SpritetGUI::SpritetGUI(QWidget *parent) : QMainWindow(parent) {
    menu = new Menu(this);

    frames.push_back(new FrameContainer);
    //canvas = new DrawingCanvas(50,50);

    toolbox = new ToolBox(this);
    framepanel = new FramePanel();

    connect(this, &SpritetGUI::frameRemoved, framepanel,
            &FramePanel::removeFrame);
    connect(this, &SpritetGUI::addFrame, framepanel
            , &FramePanel::addFrame);
    connect(this, &SpritetGUI::updateFrameList, frames[0],
            &FrameContainer::updateFrameList);
    connect(this, &SpritetGUI::frameSizeSet, framepanel,
            &FramePanel::frameSizeSetted);
    connect(framepanel, &FramePanel::addFrameToGUI, this,
            &SpritetGUI::newFrame);
    connect(framepanel, &FramePanel::removeFrameRequest, this,
            &SpritetGUI::removeFrameRequest);
    connect(framepanel, &FramePanel::moveDownFrameSignal, this,
            &SpritetGUI::moveFrameDown);
    connect(framepanel, &FramePanel::moveUpFrameSignal, this,
            &SpritetGUI::moveFrameUp);


    qDebug() << "SpritedGUI constructor framepanel reached";
    hotkeypanel = new HotkeyPanel(this);

    this->setCentralWidget(frames[0]);
    this->addDockWidget(Qt::TopDockWidgetArea, hotkeypanel);
    this->addDockWidget(Qt::LeftDockWidgetArea, toolbox);
    this->addDockWidget(Qt::RightDockWidgetArea, framepanel);
    update();

    frames[0]->show();


    setStatusBarText(tr("Ready!"));
    qDebug() << "SpritedGUI constructor status bar reached";
    /*connect(canvas, &DrawingCanvas::mouseDragged,
            this, &SpritetGUI::mouseEventHandler);*/

    connect(toolbox, &ToolBox::setTool,
            this, &SpritetGUI::setTool);

    connect(toolbox, &ToolBox::switchColorsButtonClicked,
            this, &SpritetGUI::switchColorsButtonClicked);

    connect(toolbox, &ToolBox::primaryColorChanged,
            this, &SpritetGUI::primaryColorChanged);

    connect(toolbox, &ToolBox::penSizeChanged,
            this, &SpritetGUI::penSizeChanged);

    /* hotkey connections */
    connect(hotkeypanel, &HotkeyPanel::hotkeyClicked,
            this, &SpritetGUI::hotkeyClicked);

    connect(this, &SpritetGUI::setHotkey,
            hotkeypanel, &HotkeyPanel::setHotkey);

    connect(this, &SpritetGUI::hotkeyNumber,
            hotkeypanel, &HotkeyPanel::hotkeyNumber);

    connect(hotkeypanel, &HotkeyPanel::applyHotkey,
            this, &SpritetGUI::applyHotkey);
    /* end hotkey connections */

    connect(this, &SpritetGUI::addCanvasFrame,
            frames[0], &FrameContainer::addCanvasFrame);

    /*connect(frames[0], &FrameContainer::mouseDragged,
            this, &SpritetGUI::mouseMoved);

    connect(frames[0], &FrameContainer::mousePressed,
            this, &SpritetGUI::mousePressed);

    connect(frames[0], &FrameContainer::mouseReleased,
            this, &SpritetGUI::mouseReleased);*/
}

SpritetGUI::~SpritetGUI() {
    delete framepanel;
    delete menu;

    for (auto frameContainer : frames) {
        delete frameContainer;
    }

    delete toolbox;
//    delete framepanel;
    delete hotkeypanel;
}

void SpritetGUI::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_0:
            emit hotkeyNumber(10);
            break;
        case Qt::Key_1:
            emit hotkeyNumber(1);
            break;
        case Qt::Key_2:
            emit hotkeyNumber(2);
            break;
        case Qt::Key_3:
            emit hotkeyNumber(3);
            break;
        case Qt::Key_4:
            emit hotkeyNumber(4);
            break;
        case Qt::Key_5:
            emit hotkeyNumber(5);
            break;
        case Qt::Key_6:
            emit hotkeyNumber(6);
            break;
        case Qt::Key_7:
            emit hotkeyNumber(7);
            break;
        case Qt::Key_8:
            emit hotkeyNumber(8);
            break;
        case Qt::Key_9:
            emit hotkeyNumber(9);
            break;
        case Qt::Key_N:
            emit addCanvasFrame();
            break;
        default:
            break;
    }

    /*if (event->key() == Qt::Key_Shift){
        emit shiftPressed();
    }*/
    emit keyPressed(event);
}

void SpritetGUI::keyReleaseEvent(QKeyEvent *event) {
    /*if (event->key() == Qt::Key_Shift){
        emit shiftReleased();
    }*/
    emit keyReleased(event);
}

void SpritetGUI::setStatusBarText(QString text) {
    statusBar()->showMessage(text);
}

void SpritetGUI::getFrameSize() {
    bool ok;
    int x = QInputDialog::getInt(this, tr("Get Frame Dimensions"),
                                 tr("Width (px):"), 50, 1, 10000, 1, &ok);
    if (ok) {
        int y = QInputDialog::getInt(this, tr("Get Frame Dimensions"),
                                     tr("Height (px):"), 50, 1, 10000, 1, &ok);
        if (ok) {
            emit frameSizeSet(x, y);
            qDebug() << x << "set request sent" << y;
        }
    }

}

void SpritetGUI::newFrame(int index) {

    qDebug() << "SpritedGUI pass index to controller" << index;
    emit addFrameRequest(index);
}

void SpritetGUI::addNewFrameToGUI(DrawingCanvas *frame) {
    qDebug() << "SpritedGUI pass on to canvas" << frame;
    emit addFrame(frame);
}

void SpritetGUI::removeFrameFromGUI(DrawingCanvas *frame) {
    qDebug()<<"SpritedGUI frameRemoved"<<frame;
    emit frameRemoved(frame);
}

void SpritetGUI::hideToolbox() {
    toolbox->setEnabled(false);
}

void SpritetGUI::saveAsTriggered() {
    filename = QFileDialog::getSaveFileName(this, tr("Save File"),
                                            QDir::currentPath(),
                                            tr("All (*.*)"));
    if (filename == NULL) {
        return;
    }
    filename.append(".ssp");
    emit (saveToFileSignal(filename));

}

void SpritetGUI::loadTriggered() {
    filename = QFileDialog::getOpenFileName(this, tr("Open File"),
                                            QDir::currentPath(),
                                            tr("All Files (*.*);;Ssp Files(*.ssp)"));
    if (filename == NULL) {
        return;
    }
    emit(loadFromFileSignal(filename));
}

void SpritetGUI::saveTriggered() {
    if (filename != NULL) {
        emit(saveFileSignal(filename));
    }
    else {
        saveAsTriggered();
    }
}

void SpritetGUI::exportTriggered() {
    filename = QFileDialog::getSaveFileName(this, tr("Export Gif"),
                                            QDir::currentPath(),
                                            tr("All Files (*.*);;Gif Files(*.gif)"));
    if (filename == NULL) {
        return;
    }
    emit(exportToFileSignal(filename));
}

/*
void SpritetGUI::mouseEventHandler(double x, double y){
    canvas->setPixel(x, y, 4, qRgba(255,0,0,255));
    QString text;
    text.append(QString::number(x));
    text.append(", ");
    text.append(QString::number(y));
    setStatusBarText(text);
    qDebug() << Q_FUNC_INFO << x << ", " << y;
    update();
}*/
