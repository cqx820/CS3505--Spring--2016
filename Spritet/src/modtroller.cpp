/**
 * Filename: modtroller.h
 * Author: Terrifying Nitpickers
 * Date: 24 March 2016
 */

#include "modtroller.h"

#include <QApplication>
#include <QLibraryInfo>
#include <QTranslator>
#include <algorithm>
#include <QKeyEvent>
#include <QDebug>
#include <Magick++.h>

#include "drawingcanvas.h"
#include "spritetgui.h"
#include "tool.h"
#include "toolbox.h"
#include "pencil.h"
#include "eraser.h"
#include "line.h"

ModTroller::ModTroller() {
    drawingHeight = 50;
    drawingWidth = 50;
    currentColor = new QColor(0, 0, 0, 255);
    secondaryColor = new QColor(255, 255, 255, 255);
    penSize = 1;
}

ModTroller::~ModTroller() {
    delete spritet;
    delete view;

    for (auto frame : frames) {
        delete frame;
    }

    delete currentColor;
    delete secondaryColor;

    delete currentTool;
}

void ModTroller::saveToFile(QString filename) {

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << Q_FUNC_INFO << "not right type";
        return;
    }
    QTextStream outputStream(&file);
    int frames_size = frames.size();
    qDebug() << frames.size();
    outputStream << drawingHeight << " " << drawingWidth << "\n";
    outputStream << frames_size << "\n";
    for (int i = 0; i < frames_size; i++) {
        DrawingCanvas *tmpCanvas = frames[i];
        for (unsigned row = 0; row < drawingHeight; row++) {
            for (unsigned column = 0; column < drawingWidth; column++) {
                QColor pixelColor = tmpCanvas->getPixel(row, column);
                outputStream << pixelColor.red() << " "
                << pixelColor.green() << " "
                << pixelColor.blue() << " "
                << pixelColor.alpha();
                if (column == drawingWidth - 1) {
                    outputStream << "\n";
                }
                else {
                    outputStream << " ";
                }
            }
        }
    }
    file.close();
}


void ModTroller::loadFromFile(QString filename) {

    for (auto frame : frames) {
        removeFrame(frame);
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << Q_FUNC_INFO << "not right type";
        return;
    }
    QTextStream inputStream(&file);
    QString line = inputStream.readLine();
    QStringList rowColumnList = line.split(" ");
    if (rowColumnList.size() != 2) {
        qDebug() << Q_FUNC_INFO << "insufficient information";
        return;
    }
//  try{
    QString heightRow = rowColumnList[0];
    QString widthColumn = rowColumnList[1];
    bool heightSuccessful, widthSuccessful;
    int height = heightRow.toInt(&heightSuccessful);
    int width = widthColumn.toInt(&widthSuccessful);
    if (!(heightSuccessful && widthSuccessful)) {
        qDebug() << Q_FUNC_INFO << "unsuccessful conversion";
        return;
    }
    line = inputStream.readLine();
    QStringList framesNumList = line.split(" ");
    if (framesNumList.size() != 1) {
        qDebug() << Q_FUNC_INFO << "insufficient information";
        return;
    }
    QString framesNumString = framesNumList[0];
    bool framesSuccessful;
    int framesNum = framesNumString.toInt(&framesSuccessful);
    if (!framesSuccessful) {
        qDebug() << Q_FUNC_INFO << "unsuccessful conversion";
        return;
    }
    QStringList currentRowColor;
    int currentColorRgba;
    QString redString, greenString, blueString, alphaString;
    bool redSuccessful, greenSuccessful, blueSuccessful, alphaSuccessful;
    int red, green, blue, alpha;
    for (int i = 0; i < framesNum; i++) {
        DrawingCanvas *newCanvas = addNewFrame(i);
        for (int row = 0; row < height; row++) {
            line = inputStream.readLine();
            currentRowColor = line.split(" ");
            currentColorRgba = 0;
            if (currentRowColor.size() != (width * 4)) {
                qDebug() << Q_FUNC_INFO << "insufficient color at row " << row;
                return;
            }
            for (int column = 0; column < width; column++) {
                redString = currentRowColor[currentColorRgba];
                greenString = currentRowColor[currentColorRgba + 1];
                blueString = currentRowColor[currentColorRgba + 2];
                alphaString = currentRowColor[currentColorRgba + 3];
                red = redString.toInt(&redSuccessful);
                green = greenString.toInt(&greenSuccessful);
                blue = blueString.toInt(&blueSuccessful);
                alpha = alphaString.toInt(&alphaSuccessful);
                if (!(redSuccessful && greenSuccessful
                      && blueSuccessful && alphaSuccessful)) {
                    qDebug() << Q_FUNC_INFO << "unsuccessful conversion";
                    return;
                }
                QRgb tmpColor = qRgba(red, green, blue, alpha);
                newCanvas->setPixel(row, column, 1, tmpColor);
                currentColorRgba += 4;
                newCanvas->redraw();
            }
        }
    }

    //}
    //QString heightRow = rowColumnList[0];
    emit updateFrameList(&frames);

}

void ModTroller::exportToGif(QString filename) {
    std::vector<Magick::Image> exportFrames;

    filename = filename + ".gif";

    for (DrawingCanvas *frame : frames) {
        Magick::Image exportFrame(
                Magick::Geometry(drawingWidth, drawingHeight),
                Magick::Color("White"));
        for (size_t x = 0; x < drawingWidth; x++) {
            for (size_t y = 0; y < drawingHeight; y++) {
                QColor pixel = frame->getPixel(x, y);
                Magick::Color exportColor(pixel.red() * 256,
                                          pixel.green() * 256,
                                          pixel.blue() * 256, pixel.alpha());
                exportFrame.pixelColor(x, y, exportColor);
            }
        }
        exportFrame.animationDelay(50);
        exportFrames.push_back(exportFrame);
    }
    /*
    Magick::Image frame1 (Magick::Geometry(drawingWidth, drawingHeight),
                          Magick::Color("White"));
    frame1.pixelColor(10,10, Magick::Color("Red") );
    frame1.animationDelay(50);
    exportFrames.push_back(frame1);

    Magick::Image frame2 (Magick::Geometry(drawingWidth, drawingHeight),
                          Magick::Color("White"));
    frame2.pixelColor(10,10, Magick::Color("Green") );
    frame2.pixelColor(20,20, Magick::Color("Red") );
    frame2.animationDelay(50);
    exportFrames.push_back(frame2);*/

    Magick::writeImages(exportFrames.begin(), exportFrames.end(),
                        filename.toStdString());
}

int ModTroller::initView(int argc, char *argv[]) {
    spritet = new QApplication(argc, argv);

    //if (QLocale::system().language() != QLocale::English) {
    QTranslator myappTranslator;
    QString translationPath = QApplication::applicationDirPath();
    translationPath = translationPath + "/translations/spritet_"
                      + QLocale::system().name();
    /*QString translationPath = "translations/spritet_"
            + QLocale::system().name();*/
    translationPath.truncate(translationPath.lastIndexOf('_'));
    if (myappTranslator.load(translationPath)) {
        qApp->installTranslator(&myappTranslator);
    } else {
        qWarning() << Q_FUNC_INFO << "Unable to load translation: "
        << translationPath;
    }
    //}

    view = new SpritetGUI;
    view->show();
    connect(view,&SpritetGUI::removeFrameRequest,
            this,&ModTroller::removeFrame);

    connect(this,&ModTroller::frameRemoved,view,
            &SpritetGUI::removeFrameFromGUI);

    connect(view, &SpritetGUI::frameSizeSet,
            this, &ModTroller::setFrameSize);

    connect(view, &SpritetGUI::saveFileSignal,
            this, &ModTroller::saveToFile);

    connect(view, &SpritetGUI::saveToFileSignal,
            this, &ModTroller::saveToFile);

    connect(view, &SpritetGUI::loadFromFileSignal,
            this, &ModTroller::loadFromFile);

    connect(view, &SpritetGUI::exportToFileSignal,
            this, &ModTroller::exportToGif);

    connect(this, &ModTroller::frameAdded, view,
            &SpritetGUI::addNewFrameToGUI);

    connect(view, &SpritetGUI::addFrameRequest, this,
            &ModTroller::addNewFrame);

    connect(view, &SpritetGUI::moveFrameDown,
            this, &ModTroller::moveFrameDown);

    connect(view, &SpritetGUI::moveFrameUp, this,
            &ModTroller::moveFrameUp);

    connect(view, &SpritetGUI::switchColorsButtonClicked,
            this, &ModTroller::switchPrimaryAndSecondaryColor);

    connect(view, &SpritetGUI::primaryColorChanged,
            this, &ModTroller::changePrimaryColor);

    connect(view, &SpritetGUI::penSizeChanged,
            this, &ModTroller::changePenSize);

    connect(view, &SpritetGUI::setTool,
            this, &ModTroller::toolSelected);

    connect(view, &SpritetGUI::mousePressed,
            this, &ModTroller::mousePressed);

    connect(view, &SpritetGUI::mouseMoved,
            this, &ModTroller::mouseMoved);

    connect(view, &SpritetGUI::mouseReleased,
            this, &ModTroller::mouseReleased);

    connect(view, &SpritetGUI::keyPressed,
            this, &ModTroller::keyPressed);

    connect(view, &SpritetGUI::keyReleased,
            this, &ModTroller::keyReleased);

    connect(view, &SpritetGUI::hotkeyClicked,
            this, &ModTroller::hotkeyClicked);

    connect(this, &ModTroller::setHotkey,
            view, &SpritetGUI::setHotkey);

    connect(view, &SpritetGUI::applyHotkey,
            this, &ModTroller::toolSelected);

    connect(this, &ModTroller::updateFrameList,
            view, &SpritetGUI::updateFrameList);

    connect(view, &SpritetGUI::addCanvasFrame,
            this, &ModTroller::addCanvasFrame);

    view->getFrameSize();

    qDebug() << "SpritetGUI hooked up";
    initTool();

    return spritet->exec();
}

void ModTroller::initTool() {
    currentTool = new EraserTool;

    connect(this, &ModTroller::toolPressed,
            currentTool, &Tool::mousePress);

    connect(this, &ModTroller::toolMoved,
            currentTool, &Tool::mouseMove);

    connect(this, &ModTroller::toolReleased,
            currentTool, &Tool::mouseRelease);
}

DrawingCanvas *ModTroller::addNewFrame(int index) {
    DrawingCanvas *newFrame = new DrawingCanvas(drawingWidth, drawingHeight);
    //connect(newFrame, &DrawingCanvas::mousePressed,
    //        this, &ModTroller::mouseEventHandler);
    frames.insert(frames.begin() + index, newFrame);
    emit frameAdded(newFrame);
    emit updateFrameList(&frames);
    qDebug() << drawingWidth << "ModTroller frame add request" << drawingHeight;
    connect(newFrame, &DrawingCanvas::mouseDragged,
            this, &ModTroller::mouseMoved);

    connect(newFrame, &DrawingCanvas::mousePressed,
            this, &ModTroller::mousePressed);

    connect(newFrame, &DrawingCanvas::mouseReleased,
            this, &ModTroller::mouseReleased);
    return newFrame;
}

void ModTroller::removeFrame(DrawingCanvas *frame) {
    qDebug() << "remove frame";
    frames.erase(std::remove(frames.begin(), frames.end(), frame),
                 frames.end());
    emit updateFrameList(&frames);
    emit frameRemoved(frame);
}

void ModTroller::moveFrameUp(DrawingCanvas *frame) {
    std::vector<DrawingCanvas *>::iterator i = frames.begin();
    i = find(frames.begin(), frames.end(), frame);
    frames.erase(i);
    frames.insert(i - 1, frame);
    emit updateFrameList(&frames);

    qDebug() << "moved up frame";
}

void ModTroller::moveFrameDown(DrawingCanvas *frame) {
    std::vector<DrawingCanvas *>::iterator i = frames.begin();
    i = find(frames.begin(), frames.end(), frame);
    frames.erase(i);
    frames.insert(i + 1, frame);
    emit updateFrameList(&frames);

    qDebug() << "moved down frame";
}

void ModTroller::mouseEventHandler(int x, int y) {
    qDebug() << Q_FUNC_INFO << x << ", " << y;
}

DrawingCanvas *ModTroller::getLastFrame() {
    return frames.back();
}

void ModTroller::toolSelected(Tool *tool) {

    disconnect(this, 0, currentTool, 0);

    currentTool = tool;

    connect(this, &ModTroller::toolPressed,
            currentTool, &Tool::mousePress);

    connect(this, &ModTroller::toolMoved,
            currentTool, &Tool::mouseMove);

    connect(this, &ModTroller::toolReleased,
            currentTool, &Tool::mouseRelease);
}

void ModTroller::mousePressed(DrawingCanvas *canvas,
                              QPointF *coordinates,
                              QMouseEvent *mouseEvent) {
    ToolEvent *toolEvent = new ToolEvent;
    toolEvent->canvas = canvas;
    toolEvent->coordinates = coordinates;
    toolEvent->event = mouseEvent;
    toolEvent->color = currentColor;
    toolEvent->penSize = penSize;
    toolEvent->shiftHeld = shiftHeld;
    emit toolPressed(toolEvent);
}

void ModTroller::mouseMoved(DrawingCanvas *canvas,
                            QPointF *coordinates,
                            QMouseEvent *mouseEvent) {
    ToolEvent *toolEvent = new ToolEvent;
    toolEvent->canvas = canvas;
    toolEvent->coordinates = coordinates;
    toolEvent->event = mouseEvent;
    toolEvent->color = currentColor;
    toolEvent->penSize = penSize;
    toolEvent->shiftHeld = shiftHeld;
    emit toolMoved(toolEvent);
}

void ModTroller::mouseReleased(DrawingCanvas *canvas,
                               QPointF *coordinates,
                               QMouseEvent *mouseEvent) {
    ToolEvent *toolEvent = new ToolEvent;
    toolEvent->canvas = canvas;
    toolEvent->coordinates = coordinates;
    toolEvent->event = mouseEvent;
    toolEvent->color = currentColor;
    toolEvent->penSize = penSize;
    toolEvent->shiftHeld = shiftHeld;
    emit toolReleased(toolEvent);
}

void ModTroller::keyPressed(QKeyEvent *event) {
    if (event->key() == Qt::Key_Shift) {
        shiftHeld = true;
    }
}

void ModTroller::keyReleased(QKeyEvent *event) {
    if (event->key() == Qt::Key_Shift) {
        shiftHeld = false;
    }
}

void ModTroller::switchPrimaryAndSecondaryColor() {
    QColor *temp = currentColor;
    currentColor = secondaryColor;
    secondaryColor = temp;
}

void ModTroller::setFrameSize(size_t x, size_t y) {
    drawingHeight = y;
    drawingWidth = x;
    emit frameSizeSetted(x, y);
    qDebug() << x << "set" << y;
}

void ModTroller::changePrimaryColor(QColor newPrimaryColor) {
    if (currentColor != Q_NULLPTR) {
        delete currentColor;
    }
    currentColor = new QColor(newPrimaryColor);
}

void ModTroller::changePenSize(int value) {
    penSize = value;
}

void ModTroller::hotkeyClicked(int button) {
    emit setHotkey(button, currentTool);
}

void ModTroller::addCanvasFrame() {
    emit updateFrameList(&frames);
}

int main(int argc, char *argv[]) {
    ModTroller *mt = new ModTroller;
    return mt->initView(argc, argv);
    delete mt;
}
