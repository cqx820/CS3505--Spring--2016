/**
 * Filename: menu.cpp
 * Author: Terrifying Nitpickers
 * Date: 4 April 2016
 */

#include "menu.h"

#include <QAction>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>
#include <QVBoxLayout>

#include "define.h"
#include "spritetgui.h"

Menu::Menu(SpritetGUI *parent) : QObject(parent) {
    menu = new QMenuBar(0);

    /* File Menu */
    fileMenu = new QMenu(tr("&File"));

    fileNew = new QAction(tr("&New"), parent);
    fileMenu->addAction(fileNew);

    fileOpen = new QAction(tr("&Open"), parent);
    connect(fileOpen, &QAction::triggered,
            parent, &SpritetGUI::loadTriggered);
    fileMenu->addAction(fileOpen);

    fileSave = new QAction(tr("&Save"), parent);
    connect(fileSave, &QAction::triggered,
            parent, &SpritetGUI::saveTriggered);
    fileMenu->addAction(fileSave);

    fileSaveAs = new QAction(tr("Save &As"), parent);
    connect(fileSaveAs, &QAction::triggered,
            parent, &SpritetGUI::saveAsTriggered);

    fileMenu->addAction(fileSaveAs);

    fileExport = new QAction(tr("&Export"), parent);
    connect(fileExport, &QAction::triggered,
            parent, &SpritetGUI::exportTriggered);
    fileMenu->addAction(fileExport);

    fileExit = new QAction(tr("E&xit"), parent);
    //fileExit->setShortcut(QKeySequence("Alt+F,Ctrl+X"));
    fileExit->setStatusTip(tr("Close Spritet"));
    connect(fileExit, &QAction::triggered,
            parent, &QMainWindow::close);
    fileMenu->addAction(fileExit);

    menu->addMenu(fileMenu);
    /* End File Menu */

    /* Help Menu */
    help = new QAction(tr("&Help"), parent);

    connect(help, &QAction::triggered,
            [&] {
                const QString *helpText = new QString(tr("Spritet\n\n"
              "Tools: Pencil, Line, Box, Fill, Mirror, Eraser, Color Picker,\n"
              "       Selection, lighten/darken, Color Replace.\n"
              "Help for individual tools is provided through the tool button\n"
              "       tooltips and status bar messages.\n\n"
              "Other features include: Multiple Canvases, Frame Management\n"
              "       with preview, and a Hotkey system.\n"
              "Press n on the canvas to split it. There can be up to four\n"
              "canvases at once\n"
              "To assign a hotkey, click on a tool then click on a button in\n"
              "the top bar. The button will show the number key assigned."));

                QWidget *helpWindow = new QWidget;
                QLabel *helpLabel = new QLabel(*helpText, helpWindow);
                QVBoxLayout *layout = new QVBoxLayout;

                layout->addWidget(helpLabel);

                helpWindow->setLayout(layout);
                helpWindow->show();
            });

    menu->addAction(help);
    /* End Help Menu */

    parent->setMenuBar(menu);
}

