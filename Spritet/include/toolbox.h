/**
 * Filename: toolbox.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description:
 */

#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QObject>
#include <QDockWidget>
#include <QToolButton>
#include <QLabel>
#include <QWidget>
#include <map>
#include <QDebug>
#include <QSpinBox>
#include "colorswitcher.h"
#include "define.h"
#include "tool.h"
#include "toolbutton.h"

class ColorSwitcher;

class ToolBox : public QDockWidget {
Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = Q_NULLPTR);

    ~ToolBox();

public slots:

    void toolSelected();

signals:

    void switchColorsButtonClicked();

    void setTool(Tool *);

    void penSizeChanged(int value);

    void primaryColorChanged(QColor);

private:
    QWidget *buttonArea;
    QVBoxLayout *toolLayout;

    QSpinBox *penSizeSpinBox;

    std::map<QString, ToolButton *> toolButtons;
    std::map<QString, Tool *> tools;

    ColorSwitcher *colorSwitcher;
};

#endif // TOOLBOX_H
