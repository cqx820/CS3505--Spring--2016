/**
 * Filename: drawingcanvas.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description: This class handles everything to do with drawing in Spritet
 */

#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QMouseEvent>
#include <QRgb>
#include <QDebug>

struct ToolEvent;

class DrawingCanvas : public QGraphicsView {
Q_OBJECT

public:
    DrawingCanvas(int width, int height, QWidget *parent = 0);

    ~DrawingCanvas();

    QGraphicsScene *getScene();

    size_t getWidth();

    size_t getHeight();

signals:

    /**
     * @brief mousePressed emitted when the mouse is clicked in the specified canvas
     * @param x x coordinate within the virtual canvas
     * @param y y coordinate within the virtual canvas
     */
    void mousePressed(DrawingCanvas *, QPointF *, QMouseEvent *event);

    void mouseDragged(DrawingCanvas *, QPointF *, QMouseEvent *event);

    void mouseReleased(DrawingCanvas *, QPointF *, QMouseEvent *event);

    void frameChanged(DrawingCanvas *);

public slots:

    /**
     * Sets the pixel at the specified coordinate to the specified color
     * @param x x coordinate within the virtual canvas
     * @param y y coordinate within the virtual canvas
     * @param size size of the pixel to draw
     * @param color If no alpha is specified, d
     */
    void setPixel(double x, double y, int size, QRgb color);

    QColor getPixel(int x, int y);

    /**
     * Overlays a transparent preview on the drawn image
     * @param pixels List of x, y coordinates to draw
     * @param size Pen size
     * @param color Preview color
     */
    void showPreview(std::vector<QPointF> pixels, int size, QRgb color);

    void clearPreview();

    void redraw();

protected:
    //Stores the image currently drawn
    QImage *backingImage;
    //Shows the pixmap currently drawn
    QGraphicsPixmapItem *backingPixmap;
    //Used to show a preview
    QImage *previewImage;
    QGraphicsPixmapItem *previewPixmap;

    void setPixel(double x, double y, int size, QRgb color, QImage *);

    //Used by the mouseMoveEvent to determine if the mouse has moved a full pixel
    int lastX;
    int lastY;

    size_t width;
    size_t height;

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);
};

#endif // DRAWINGCANVAS_H
