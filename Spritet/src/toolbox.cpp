/**
 * Filename: toolbox.cpp
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 */

#include "toolbox.h"

#include <QCoreApplication>
#include <QDockWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>
#include <map>
#include <string>
#include <QDebug>
#include <QToolButton>
#include <QLabel>
#include "define.h"

#include "tool.h"
#include "pencil.h"
#include "eraser.h"
#include "line.h"
#include "selection.h"
#include "box.h"
#include "fill.h"
#include "lightendarken.h"
#include "mirror.h"

#include "colourreplacer.h"

ToolBox::ToolBox(QWidget *parent) :
        QDockWidget(parent) {

    //general blueprint for adding stuff
    // make a holder for a toolLayout
    // make a toolLayout
    // add widgets to the toolLayout
    // set the toolLayout of the holder to the created toolLayout


    buttonArea = new QWidget(this);


    toolLayout = new QVBoxLayout;

    QLabel *penSizeLabel = new QLabel(tr("Pen size:"), this);
    toolLayout->addWidget(penSizeLabel);

    penSizeSpinBox = new QSpinBox(this);
    penSizeSpinBox->setSuffix(" px");
    penSizeSpinBox->setMinimum(1);
    penSizeSpinBox->setMaximum(500);
    penSizeSpinBox->setMaximumWidth(75);
    connect(penSizeSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &ToolBox::penSizeChanged);
    toolLayout->addWidget(penSizeSpinBox);

    for (QString tool : tools_str) {
        toolButtons[tool] = new ToolButton(tool, this);
        toolLayout->addWidget(toolButtons[tool]);
    }

    tools["Pencil"] = new PencilTool;
    connect(toolButtons["Pencil"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Eraser"] = new EraserTool;
    connect(toolButtons["Eraser"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Line"] = new LineTool;
    connect(toolButtons["Line"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Replacer"] = new ColorReplacer;
    connect(toolButtons["Replacer"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Selection"] = new SelectionTool;
    connect(toolButtons["Selection"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Box"] = new BoxTool;
    connect(toolButtons["Box"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Fill"] = new FillTool;
    connect(toolButtons["Fill"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["LightenDarken"] = new LightenDarkenTool;
    connect(toolButtons["LightenDarken"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);

    tools["Mirror"] = new MirrorTool;
    connect(toolButtons["Mirror"], &ToolButton::clicked,
            this, &ToolBox::toolSelected);


    //Set the name of the buttons to the translated version
    for (QString tool : tools_str) {
        toolButtons[tool]->setToolButtonStyle(Qt::ToolButtonIconOnly);
        //set the icon from the alias of the resource specified in resources/icons.qrc
        toolButtons[tool]->setIcon(QIcon(":/" + tool + "-icon"));
        //toolButtons[tool]->setIconSize(QSize(15, 15));
        //toolButtons[tool]->setText(tools[tool]->getName());
    }

    //Add the color switcher to the toolbox
    colorSwitcher = new ColorSwitcher(this);
    toolLayout->addWidget(colorSwitcher);
    connect(colorSwitcher, &ColorSwitcher::switchColorsButtonClicked,
            this, &ToolBox::switchColorsButtonClicked);
    connect(colorSwitcher, &ColorSwitcher::primaryColorChanged,
            this, &ToolBox::primaryColorChanged);

    //set the widget for the entire panel
    setWidget(buttonArea);
    buttonArea->setLayout(toolLayout);
    buttonArea->show();

    // make it pretty
    toolLayout->insertStretch(toolLayout->count());

}

ToolBox::~ToolBox() {
    for (auto tool : tools_str) {
        delete toolButtons[tool];
    }

    for (auto tool : tools_str) {
        delete tools[tool];
    }

    delete penSizeSpinBox;
    delete toolLayout;
    delete buttonArea;
    delete colorSwitcher;
}


void ToolBox::toolSelected() {
    ToolButton *button = qobject_cast<ToolButton *>(sender());
    QString tool = button->getName();
    emit setTool(tools[tool]);
}

