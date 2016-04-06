/**
 * Filename: drawingcanvas.cpp
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 */

#include "drawingcanvas.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QPointF>
#include <QRgb>
#include <QDebug>

struct ToolEvent;

DrawingCanvas::DrawingCanvas(int width, int height, QWidget *parent) :
        QGraphicsView(parent) {
    this->height = height;
    this->width = width;
    setScene(new QGraphicsScene(this));
    this->width = width;
    this->height = height;
    backingImage = new QImage(width, height, QImage::Format_ARGB32);
    previewImage = new QImage(width, height, QImage::Format_ARGB32);
    QImage alphaBackground(width, height, QImage::Format_ARGB32);
    //Set all pixels in the image to white and transparent
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            QRgb value = qRgba(255, 255, 255, 0);
            backingImage->setPixel(j, i, value);
            previewImage->setPixel(j, i, value);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            QRgb value;
            if ((j % 2 == 1) ^ (i % 2 == 1)) { // Grey box condition
                value = qRgba(235, 235, 235, 255);
            } else { // White box
                value = qRgba(255, 255, 255, 255);
            }
            alphaBackground.setPixel(j, i, value);
        }
    }
    scene()->addPixmap(QPixmap::fromImage(alphaBackground));
    //backingImage->setPixel(width / 2, height / 2, qRgba(255, 0, 0, 255));
    backingPixmap = scene()->addPixmap(QPixmap::fromImage(*backingImage));
    previewPixmap = scene()->addPixmap(QPixmap::fromImage(*previewImage));
}

DrawingCanvas::~DrawingCanvas() {
    delete backingImage;
    delete previewImage;
    delete backingPixmap;
    delete previewPixmap;
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    QPointF coordinates = QGraphicsView::mapToScene(event->pos());
    lastX = coordinates.x();
    lastY = coordinates.y();
    emit mousePressed(this, &coordinates, event);
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    QPointF coordinates = QGraphicsView::mapToScene(event->pos());
    if (!(lastX == (int) coordinates.x() && lastY == (int) coordinates.y())) {
        lastX = coordinates.x();
        lastY = coordinates.y();
        emit mouseDragged(this, &coordinates, event);
    }
}

void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
    QPointF coordinates = QGraphicsView::mapToScene(event->pos());
    emit mouseReleased(this, &coordinates, event);
}

QGraphicsScene *DrawingCanvas::getScene() {
    return this->scene();
}

void DrawingCanvas::setPixel(double x, double y, int size, QRgb color) {
    setPixel(x, y, size, color, backingImage);
}

void DrawingCanvas::redraw() {
    backingPixmap->setPixmap(QPixmap::fromImage(*backingImage));
    emit frameChanged(this);
}

QColor DrawingCanvas::getPixel(int x, int y) {
    QRgb rawColor = backingImage->pixel(x, y);
    //QRgb values are typedef'd ints of the form 0xAARRGGBB
    int alpha = (rawColor >> (4 * 6)) & 0x000000FF;
    int red = (rawColor >> (4 * 4)) & 0x000000FF;
    int green = (rawColor >> (4 * 2)) & 0x000000FF;
    int blue = (rawColor >> (4 * 0)) & 0x000000FF;
    return QColor(red, green, blue, alpha);
}

void DrawingCanvas::showPreview(std::vector<QPointF> pixels, int size,
                                QRgb color) {
    for (QPointF pixel : pixels) {
        setPixel(pixel.x(), pixel.y(), size, color, previewImage);
    }
    previewPixmap->setPixmap(QPixmap::fromImage(*previewImage));
}

void DrawingCanvas::clearPreview() {
    for (int i = 0; i < previewImage->height(); i++) {
        for (int j = 0; j < previewImage->width(); j++) {
            QRgb value = qRgba(255, 255, 255, 0);
            previewImage->setPixel(i, j, value);
        }
    }
    previewPixmap->setPixmap(QPixmap::fromImage(*previewImage));
}

size_t DrawingCanvas::getHeight() {
    return height;
}

size_t DrawingCanvas::getWidth() {
    return width;
}

void DrawingCanvas::setPixel(double x, double y, int size, QRgb color,
                             QImage *image) {
    if (size % 2 == 1) { // Size is odd. Draw evenly around the given point
        // We will have to go this far from the center
        int distance = (size - 1) / 2.0;
        int paintX = (int) x - distance;
        int paintY = (int) y - distance;
        while (true) {
            image->setPixel(paintX, paintY, color);
            paintX = paintX + 1;
            if (paintX > x + distance) {
                paintX = (int) x - distance;
                paintY = paintY + 1;
                if (paintY > y + distance) {
                    break;
                }
            }
        }
    } else {
        // Size is even. Draw skewed in the direction that the user clicked
        // relative to the center of the pixel. I.e., if x > 0.5, skew towards
        // 1. If x < 0.5, skew towards 0. If x == 0.5, choose one.
        int skewX;
        int skewY;

        if ((x - (int) x) > 0.5) {
            skewX = 1;
        } else {
            skewX = -1;
        }

        if ((y - (int) y) > 0.5) {
            skewY = 1;
        } else {
            skewY = -1;
        }
        //Paint the majority of the mark
        this->setPixel(x + skewX, y + skewY, size - 1, color);
        //Print a one-pixel border in the opposite direction
        int startX = x - (skewX * ((size - 1) / 2));
        int stopX = x + (skewX * (size / 2));
        //We need to save the corner for painting
        int paintX = startX;

        if (startX < stopX) {
            int temp = startX;
            startX = stopX;
            stopX = temp;
        }

        int startY = y - (skewY * ((size - 1) / 2));
        int stopY = y + (skewY * (size / 2));
        //We need to save the corner for painting
        int paintY = startY;

        if (startY < stopY) {
            int temp = startY;
            startY = stopY;
            stopY = temp;
        }


        while (startX >= stopX) {
            image->setPixel(startX, paintY, color);
            startX = startX - 1;
        }

        while (startY >= stopY) {
            image->setPixel(paintX, startY, color);
            startY = startY - 1;
        }
    }
}
