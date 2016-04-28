/**
 * Filename: typetypemenu.h
 * Author: //TO DO: Teamname
 * Date: 14 April 2016
 * Description: This class represents a menu for the TypeTypeRevolution program
 */

#ifndef TYPETYPEMENU_H
#define TYPETYPEMENU_H

#include <QMenuBar>

class TypeTypeMenu : public QMenuBar {
Q_OBJECT
public:
    TypeTypeMenu(QWidget *parent);
    ~TypeTypeMenu();

signals:
    void loadLessonPressed();
    void connectButtonPressed();
    void exitPressed();
    void fullscreenPressed(bool);
    void startButtonPressed();
    void abortButtonPressed();
    void changeWPM(double WPM);

public slots:
    void toggleStartAbortButton();

protected:
    double easyWPM = 30.0;
    double mediumWPM = 60.0;
    double hardWPM = 90.0;
    //File Menu Items
    QMenu *fileMenu;
    QAction *loadLesson;
    QAction *connectToServer;
    QAction *startButton;
    QAction *abortButton;
    QAction *exit;
    //End File Menu Items
    //Difficulty Menu Items
    QMenu *difficulty;
    QAction *WPMEasy;
    QAction *WPMMedium;
    QAction *WPMHard;
    QAction *WPMCustom;
    //End Difficulty Menu Items
    //View Menu Items
    QMenu *viewMenu;
    QAction *fullscreen;
    //End View Menu Items

protected slots:
    void startAbortButtonHandler();
    void WPMHandler();

};

#endif // TYPETYPEMENU_H
