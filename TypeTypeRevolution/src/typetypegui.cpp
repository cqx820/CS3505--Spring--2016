/**
 * Filename: typetypegui.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 */

#include "typetypegui.h"

#include <QBoxLayout>
#include <QDebug>
#include <QSizePolicy>
#include <QStatusBar>

#include "chooselessondialog.h"
#include "fallingcanvas.h"
#include "typetypemenu.h"
#include "wordbox.h"


TypeTypeGUI::TypeTypeGUI(QWidget *parent)
    : QMainWindow(parent) {

    //We have to add everything to a QWidget because QMainWindow doesn't like
    //layouts
    centralWidget = new QWidget(this);

    layout = new QVBoxLayout;

    statusBar()->showMessage("Ready!");

    QSizePolicy textSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSizePolicy canvasSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    //I think 1:5 should look nice
    textSizePolicy.setVerticalStretch(1);
    canvasSizePolicy.setVerticalStretch(5);

    this->lessonBox = new WordBox(this);
    lessonBox->setPlaceholderText(tr("No Lesson Loaded"));
    lessonBox->setSizePolicy(textSizePolicy);
    layout->addWidget(lessonBox);
    connect(lessonBox, &WordBox::poppedWord,
            this, &TypeTypeGUI::poppedWord);
    connect(this, &TypeTypeGUI::popWord,
            lessonBox, &WordBox::popWord);
    connect(lessonBox, &WordBox::outOfWords,
            this, &TypeTypeGUI::outOfWords);

    canvas = new FallingCanvas(this, QPoint(0, 0), QSize(600, 300));
    canvas->setSizePolicy(canvasSizePolicy);
    layout->addWidget(canvas);
    connect(this,&TypeTypeGUI::updateWorldSignal,canvas,&FallingCanvas::updateWorld);
    connect(this,&TypeTypeGUI::addEntity,canvas,&FallingCanvas::addEntity);
    connect(this,&TypeTypeGUI::updateScore,canvas,&FallingCanvas::updateScore);
    connect(this,&TypeTypeGUI::toggleCrateSignal,canvas,&FallingCanvas::toggleCrateColor);
    connect(this,&TypeTypeGUI::highlightTextOnCrate,canvas,&FallingCanvas::highlightText);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);


    menubar = new TypeTypeMenu(this);
    this->setMenuBar(menubar);
    connect(menubar, &TypeTypeMenu::loadLessonPressed,
            this, &TypeTypeGUI::showLessonChooser);
    connect(menubar, &TypeTypeMenu::connectButtonPressed,
            this, &TypeTypeGUI::showServerDialog);
    connect(menubar, &TypeTypeMenu::startButtonPressed,
            this, &TypeTypeGUI::startButtonPressed);
    connect(menubar, &TypeTypeMenu::abortButtonPressed,
            this, &TypeTypeGUI::abortButtonPressed);
    connect(menubar, &TypeTypeMenu::exitPressed,
            this, &QMainWindow::close);
    connect(menubar, &TypeTypeMenu::changeWPM,
            this, &TypeTypeGUI::changeWPM);
    connect(menubar, &TypeTypeMenu::fullscreenPressed,
            this, &TypeTypeGUI::setFullscreen);
    connect(this, &TypeTypeGUI::toggleStartAbortButton,
            menubar, &TypeTypeMenu::toggleStartAbortButton);

    lessonChooser = new ChooseLessonDialog();
    connect(this, &TypeTypeGUI::updateAvailableLessons,
            lessonChooser, &ChooseLessonDialog::updateAvailableLessons);
    /*
    std::vector<QString> testLessons;
    //I will hardcode some lessons "for now"
    testLessons.push_back(QString("Alice In Wonderland"));
    emit updateAvailableLessons(testLessons);
    */
    connect(lessonChooser, &ChooseLessonDialog::chooseLessonConnectionInfo,
            this, &TypeTypeGUI::chooseLessonConnectionInfo);

    serverChooser = new ServerConnectDialog();
    connect(serverChooser, &ServerConnectDialog::connectButtonPressed,
            this, &TypeTypeGUI::connectButtonPressed);

    handler = new KeyboardHandler();

    //kbh --> gui
    connect(handler, &KeyboardHandler::characterAttemptSuccess,
            this, &TypeTypeGUI::characterSuccess);
    connect(handler, &KeyboardHandler::characterAttemptFailure,
            this, &TypeTypeGUI::characterFailure);

    //gui --> kbh
    connect(this, &TypeTypeGUI::sendWordToHandler,
            handler, &KeyboardHandler::receiveWord);
    // wordBox --> kbh
    connect(this, &TypeTypeGUI::characterAttempt,
            handler, &KeyboardHandler::receiveCharacterAttempt);

    //keyboard filter
    lessonBox->installEventFilter(this);
    lessonBox->setFocus(Qt::ActiveWindowFocusReason);

    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus(Qt::ActiveWindowFocusReason);

    // Register our special type so we can send it accross thread boundries
    qRegisterMetaType<ChooseLessonDialog::lessonsArray>("ChooseLessonDialog::lessonsArray");
}

TypeTypeGUI::~TypeTypeGUI() {
    delete lessonBox;
    lessonBox = Q_NULLPTR;

    delete canvas;
    canvas = Q_NULLPTR;

    delete layout;
    layout = Q_NULLPTR;

    delete centralWidget;
    centralWidget = Q_NULLPTR;

    delete lessonChooser;
    lessonChooser = Q_NULLPTR;

    delete serverChooser;
    serverChooser = Q_NULLPTR;
}

void TypeTypeGUI::connectionFailedHandler(QString errorMessage) {
    statusBar()->showMessage(errorMessage);
}

void TypeTypeGUI::connectionSuccessHandler(QString infoMessage) {
    statusBar()->showMessage(infoMessage);
}

void TypeTypeGUI::setLesson(const QString &lesson) {
    lessonBox->setPlainText(lesson);
    //lessonChooser->show();
}

void TypeTypeGUI::setFullscreen(bool checked) {
    if (checked) {
        this->setWindowState(Qt::WindowFullScreen);
    } else {
        this->setWindowState(Qt::WindowNoState);
    }
}

QSize TypeTypeGUI::sizeHint() const {
    return QSize(1280, 720);
}

bool TypeTypeGUI::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return
           || keyEvent->key() == Qt::Key_Backspace
           || keyEvent->key() == Qt::Key_Delete
           || keyEvent->key() == Qt::Key_Space) {
            qDebug("[INFO] Ate key press %d", keyEvent->key());
            return true;
        } else {
            return false;
        }
    } else {
        // standard event processing
        return QObject::eventFilter(obj, event);
    }
}

void TypeTypeGUI::keyPressEvent(QKeyEvent *event) {
    //forward the key press to the handler
    emit characterAttempt(event);
}

void TypeTypeGUI::showLessonChooser() {
    lessonChooser->show();
}

void TypeTypeGUI::showServerDialog() {
    serverChooser->show();
}

