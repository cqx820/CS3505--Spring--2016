#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "spritetgui.h"

class SpritetGUI;

class Menu : public QObject {
Q_OBJECT
public:
    explicit Menu(SpritetGUI *parent = Q_NULLPTR);

signals:

public slots:

private:
    SpritetGUI *gui;
    QMenuBar *menu;

    QMenu *fileMenu;
    QAction *fileNew;
    QAction *fileOpen;
    QAction *fileSave;
    QAction *fileSaveAs;
    QAction *fileExport;
    QAction *fileExit;

    QAction *help;
};

#endif // MENU_H
