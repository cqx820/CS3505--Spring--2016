#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include <QWidget>
#include "drawingcanvas.h"
#include <QGraphicsView>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Thumbnail : public QWidget {
Q_OBJECT
public:
    Thumbnail(QWidget *parent, DrawingCanvas *panel);

    ~Thumbnail();

    bool isChecked();

signals:

    void moveUp(DrawingCanvas *);

    void moveDown(DrawingCanvas *);

    void changeVisibility(DrawingCanvas *, bool);

public slots:

    void upButtonPressed();

    void downButtonPressed();

    void checkBoxChanged();

private:
    QVBoxLayout *buttons;
    QHBoxLayout *layout;
    QGraphicsView *view;
    QPushButton *upButton;
    QPushButton *downButton;
    QCheckBox *checkbox;
    DrawingCanvas *canvas;
    bool visible;

    virtual QSize sizeHint() const;
};

#endif // THUMBNAIL_H
