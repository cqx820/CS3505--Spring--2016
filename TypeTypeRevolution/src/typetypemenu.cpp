/**
 * Filename: typetypemenu.cpp
 * Author: //TO DO: Teamname
 * Date: 14 April 2016
 */

#include "typetypemenu.h"

TypeTypeMenu::TypeTypeMenu(QWidget *parent) : QMenuBar(parent) {
    //Constructing file menu
    fileMenu = new QMenu(tr("&File"));

    startButton = new QAction(tr("&Start"), this);
    fileMenu->addAction(startButton);
    connect(startButton, &QAction::triggered,
            this, &TypeTypeMenu::startAbortButtonHandler);
    startButton->setMenuRole(QAction::NoRole);

    abortButton = new QAction(tr("&Abort"), this);
    fileMenu->addAction(abortButton);
    abortButton->setVisible(false);
    connect(abortButton, &QAction::triggered,
            this, &TypeTypeMenu::startAbortButtonHandler);
    abortButton->setMenuRole(QAction::NoRole);

    loadLesson = new QAction(tr("&Load Lesson"), this);
    fileMenu->addAction(loadLesson);
    connect(loadLesson, &QAction::triggered,
            this, &TypeTypeMenu::loadLessonPressed);

    connectToServer = new QAction(tr("&Connect To Server"), this);
    fileMenu->addAction(connectToServer);
    connect(connectToServer, &QAction::triggered,
            this, &TypeTypeMenu::connectButtonPressed);

    exit = new QAction(tr("E&xit"), this);
    fileMenu->addAction(exit);
    connect(exit, &QAction::triggered,
            this, &TypeTypeMenu::exitPressed);

    //Finished constructing file menu
    this->addMenu(fileMenu);

    //Constructing the difficulty menu
    difficulty = new QMenu(tr("&Difficulty"));

    WPMEasy = new QAction(tr("&Easy ").append(QString::number(easyWPM)), this);
    WPMEasy->setCheckable(true);
    connect(WPMEasy, &QAction::triggered,
            this, &TypeTypeMenu::WPMHandler);
    difficulty->addAction(WPMEasy);

    WPMMedium = new QAction(tr("&Medium ").append(QString::number(mediumWPM)), this);
    WPMMedium->setCheckable(true);
    connect(WPMMedium, &QAction::triggered,
            this, &TypeTypeMenu::WPMHandler);
    difficulty->addAction(WPMMedium);

    WPMHard = new QAction(tr("&Hard ").append(QString::number(hardWPM)), this);
    WPMHard->setCheckable(true);
    connect(WPMHard, &QAction::triggered,
            this, &TypeTypeMenu::WPMHandler);
    difficulty->addAction(WPMHard);

    WPMCustom = new QAction(tr("&Custom"), this);
    WPMCustom->setCheckable(true);
    connect(WPMCustom, &QAction::triggered,
            this, &TypeTypeMenu::WPMHandler);
    difficulty->addAction(WPMCustom);

    WPMMedium->trigger();
    //Finished constructing difficulty menu
    this->addMenu(difficulty);

    //Constructing the view menu
    viewMenu = new QMenu(tr("&View"));

    fullscreen = new QAction(tr("&Fullscreen"), this);
    fullscreen->setCheckable(true);
    viewMenu->addAction(fullscreen);
    connect(fullscreen, &QAction::triggered,
            this, &TypeTypeMenu::fullscreenPressed);

    //Finished constructing the view menu
    this->addMenu(viewMenu);

}

TypeTypeMenu::~TypeTypeMenu() {
    delete fileMenu;
    fileMenu = Q_NULLPTR;
    delete loadLesson;
    loadLesson = Q_NULLPTR;
    delete exit;
    exit = Q_NULLPTR;
    delete difficulty;
    difficulty = Q_NULLPTR;
    delete WPMEasy;
    WPMEasy = Q_NULLPTR;
    delete WPMMedium;
    WPMMedium = Q_NULLPTR;
    delete WPMHard;
    WPMHard = Q_NULLPTR;
    delete WPMCustom;
    WPMCustom = Q_NULLPTR;
    delete viewMenu;
    viewMenu = Q_NULLPTR;
    delete fullscreen;
    fullscreen = Q_NULLPTR;
    delete startButton;
    startButton = Q_NULLPTR;
    delete abortButton;
    abortButton = Q_NULLPTR;
}

void TypeTypeMenu::toggleStartAbortButton() {
    if (abortButton->isVisible()) {
        abortButton->trigger();
    } else if (startButton->isVisible()) {
        startButton->trigger();
    }
}

void TypeTypeMenu::startAbortButtonHandler() {
    if (sender() == startButton) {
        startButton->setVisible(false);
        abortButton->setVisible(true);
        emit startButtonPressed();
    } else if (sender() == abortButton) {
        startButton->setVisible(true);
        abortButton->setVisible(false);
        emit abortButtonPressed();
    } else {

    }
}

void TypeTypeMenu::WPMHandler() {
    //Until I decide what to do with custom WPM, just do nothing
    if (sender() == WPMCustom) {
        WPMCustom->setChecked(false);
        return; // Not implemented
    }

    WPMEasy->setChecked(false);
    WPMMedium->setChecked(false);
    WPMHard->setChecked(false);
    WPMCustom->setChecked(false);

    if (sender() == WPMEasy) {
        WPMEasy->setChecked(true);
        emit changeWPM(easyWPM);
    } else if (sender () == WPMMedium) {
        WPMMedium->setChecked(true);
        emit changeWPM(mediumWPM);
    } else if (sender() == WPMHard) {
        WPMHard->setChecked(true);
        emit changeWPM(hardWPM);
    } else if (sender() == WPMCustom) {
        //As of now, this should never be hit because of the check at the start
        WPMCustom->setChecked(true);
    } else {
        // How did you get here anyway?
        throw Q_FUNC_INFO;
    }
}
