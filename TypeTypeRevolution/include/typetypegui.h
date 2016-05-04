/**
 * Filename: typetypegui.h
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This is the main GUI of the Type Type Revolution application
 */

#ifndef TYPETYPEGUI_H
#define TYPETYPEGUI_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QRegularExpression>

#include "chooselessondialog.h"
#include "fallingcanvas.h"
#include "serverconnectdialog.h"
#include "typetypemenu.h"
#include "wordbox.h"
#include "keyboardhandler.h"
#include "entity.h"

class TypeTypeGUI : public QMainWindow {
    Q_OBJECT

public:
    TypeTypeGUI(QWidget *parent = 0);
    ~TypeTypeGUI();
    virtual QSize sizeHint() const;

signals:
    void characterSuccess(bool isLastLetter, int toTypeIndex);
    void characterFailure();
    void connectButtonPressed(QString URL, QString username, QString password,
                              bool isLogin, QString email, QString realName);
    void sendWordToHandler(QString word);
    void characterAttempt(QKeyEvent *event);
    void updateWorldSignal(b2World*);
    void addEntity(Entity*,std::string);
    void toggleCrateSignal(Entity*,bool);
    void highlightTextOnCrate(Entity*,int);

    /**
     * Emitted after the popWord slot is called if there is a word to return
     */
    void popWord(const QRegularExpression&);

    /**
     * Emitted when the word box attempts to pop a word but there is nothing to
     * pop
     */
    void outOfWords();
    void poppedWord(QString);
    void startButtonPressed();
    void abortButtonPressed();
    void changeWPM(double);
    void updateScore(int);
    void toggleStartAbortButton();

    /**
     * Emitted when the user presses okay on the choose lesson dialog or
     * requests the next lesson in a story. The parameter contains the data
     * of the lesson needing to be passed to the server
     */
    void chooseLessonConnectionInfo(const QString&);
    /**
     * Emitted to tell the GUI which titles the user can select from
     */
    void updateAvailableLessons(ChooseLessonDialog::lessonsArray);


public slots:
    void connectionFailedHandler(QString errorMessage);
    void connectionSuccessHandler(QString infoMessage);
    void setLesson(const QString&);
    void setFullscreen(bool);


protected:
    FallingCanvas *canvas=NULL;
    QWidget *centralWidget=NULL;
    ChooseLessonDialog *lessonChooser;
    ServerConnectDialog *serverChooser;
    /**
     * @brief lessonBox Used to store and display the lesson
     */
    WordBox *lessonBox=NULL;

    QVBoxLayout *layout=NULL;
    TypeTypeMenu *menubar=NULL;

    void keyPressEvent(QKeyEvent *event);
    // Filter for unsavory keys
    bool eventFilter(QObject *obj, QEvent *event);
    KeyboardHandler *handler;

protected slots:
    void showLessonChooser();
    void showServerDialog();
};

#endif // TYPETYPEGUI_H
