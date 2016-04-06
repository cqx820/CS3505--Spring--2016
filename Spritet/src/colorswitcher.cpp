/**
 * Filename: colorswitcher.cpp
 * Author: Terrifying Nitpickers
 * Date: 4 April 2016
 */


#include "colorswitcher.h"

#include <QColorDialog>
#include <QWidget>
#include <QToolButton>
#include <QGridLayout>

#include "define.h"

ColorSwitcher::ColorSwitcher(QWidget *parent) : QWidget(parent) {
    colorPicker = new QColorDialog(this);

    colorSwitcherLayout = new QGridLayout;

    primaryColor = new QColor(0, 0, 0, 255);
    secondaryColor = new QColor(255, 255, 255, 255);

    QString primaryStyle("background-color:");
    primaryStyle = primaryStyle + primaryColor->name();
    QString secondaryStyle("background-color:");
    secondaryStyle = secondaryStyle + secondaryColor->name();

    secondaryColorDisplay = new QWidget(this);
    secondaryColorDisplay->setStyleSheet(secondaryStyle);

    primaryColorDisplay = new QWidget(this);
    primaryColorDisplay->setStyleSheet(primaryStyle);

    switchButton = new QToolButton(this);

    switchButton->setAutoRaise(false);
    switchButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    //set the icon from the alias of the resource specified in resources/icons.qrc
    switchButton->setIcon(QIcon(":/switchArrow-icon"));
    switchButton->setIconSize(QSize(15, 15));

    colorSwitcherLayout->setColumnMinimumWidth(1, 20);
    colorSwitcherLayout->setColumnMinimumWidth(2, 20);
    colorSwitcherLayout->setColumnMinimumWidth(3, 20);
    colorSwitcherLayout->setColumnMinimumWidth(4, 20);

    colorSwitcherLayout->setRowMinimumHeight(1, 20);
    colorSwitcherLayout->setRowMinimumHeight(2, 20);
    colorSwitcherLayout->setRowMinimumHeight(3, 20);
    colorSwitcherLayout->setRowMinimumHeight(4, 20);

    colorSwitcherLayout->setSpacing(0);

    colorSwitcherLayout->addWidget(switchButton, 1, 4, 1, 1);
    colorSwitcherLayout->addWidget(secondaryColorDisplay, 1, 1, 3, 3);
    colorSwitcherLayout->addWidget(primaryColorDisplay, 2, 2, 3, 3);
    //colorSwitcherLayout->addWidget(primaryColorDisplay, 1, 1, 3, 3);
    //colorSwitcherLayout->addWidget(secondaryColorDisplay, 2, 2, 3, 3);
    this->setLayout(colorSwitcherLayout);
    this->setFixedSize(80, 80);

    connect(switchButton, &QToolButton::clicked,
            this, &ColorSwitcher::switchColorsButtonClicked);

    connect(this, &ColorSwitcher::switchColorsButtonClicked,
            this, &ColorSwitcher::updateColorDisplay);

    connect(this, &ColorSwitcher::primaryColorChanged,
            this, &ColorSwitcher::changePrimaryColor);
}

ColorSwitcher::~ColorSwitcher() {
    delete switchButton;
    delete primaryColorDisplay;
    delete secondaryColorDisplay;
    delete colorSwitcherLayout;
    delete primaryColor;
    delete secondaryColor;
    delete colorPicker;
}

void ColorSwitcher::updateColorDisplay() {
    QString temp = primaryColorDisplay->styleSheet();
    primaryColorDisplay->setStyleSheet(secondaryColorDisplay->styleSheet());
    secondaryColorDisplay->setStyleSheet(temp);

    QColor *tempColor = primaryColor;
    primaryColor = secondaryColor;
    secondaryColor = tempColor;
}

void ColorSwitcher::changePrimaryColor(QColor newPrimaryColor) {
    delete primaryColor;
    primaryColor = new QColor(newPrimaryColor);

    QString primaryStyle("background-color:");
    primaryStyle = primaryStyle + primaryColor->name();

    primaryColorDisplay->setStyleSheet(primaryStyle);
}

void ColorSwitcher::mousePressEvent(QMouseEvent *) {
    QColor newColor = colorPicker->getColor(*primaryColor, this,
                                            tr("Spritet Color Choser"),
                                            QColorDialog::ShowAlphaChannel);
    emit primaryColorChanged(newColor);
}
