/**
 * Filename: colorswitcher.h
 * Author: Terrifying Nitpickers
 * Date: 4 April 2016
 * Description: This element shows a primary and seconday color along with a
 * button to switch the two and the ability to click on it to change those
 * colors
 */

#ifndef COLORSWITCHER_H
#define COLORSWITCHER_H

#include <QColorDialog>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

class ColorSwitcher : public QWidget {
Q_OBJECT
public:
    explicit ColorSwitcher(QWidget *parent = 0);

    ~ColorSwitcher();

public slots:

    void updateColorDisplay();

    void changePrimaryColor(QColor);

signals:

    void switchColorsButtonClicked();

    /**
     * This signal is emitted whenever the primary color is changed by the user
     */
    void primaryColorChanged(QColor);

protected:
    void mousePressEvent(QMouseEvent *);

private:
    QColor *primaryColor;
    QColor *secondaryColor;

    QWidget *primaryColorDisplay;
    QWidget *secondaryColorDisplay;

    QGridLayout *colorSwitcherLayout;
    QToolButton *switchButton;

    QColorDialog *colorPicker;
};

#endif // COLORSWITCHER_H
