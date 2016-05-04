/**
 * Filename: chooselessondialog.cpp
 * Author: //TO DO: Teamname
 * Date: 22 April 2016
 */

#include "include/chooselessondialog.h"

#include <QBoxLayout>
#include <QGroupBox>
#include <QLayout>


ChooseLessonDialog::ChooseLessonDialog(QWidget *parent) : QWidget(parent) {

    layout = new QVBoxLayout(this);

    this->setLayout(layout);

    //Mode Selection
    modeSelection = new QGroupBox(tr("Choose Mode"), this);
    modeSelectionLayout = new QHBoxLayout(modeSelection);

    storyModeButton = new QRadioButton(tr("Story Mode"), this);
    lessonModeButton = new QRadioButton(tr("Lesson Mode"), this);
    randomModeButton = new QRadioButton(tr("Random Mode"), this);

    modeSelectionLayout->addWidget(storyModeButton);
    modeSelectionLayout->addWidget(lessonModeButton);
    modeSelectionLayout->addWidget(randomModeButton);

    QString upgradeText(tr("Subscribe to the gold edition to unlock!"));

    storyModeButton->setChecked(true);
    lessonModeButton->setEnabled(false);
    lessonModeButton->setToolTip(upgradeText);
    randomModeButton->setEnabled(false);
    randomModeButton->setToolTip(upgradeText);

    modeSelection->setLayout(modeSelectionLayout);

    layout->addWidget(modeSelection);
    //End Mode Selection

    //Lesson Section
    availableLessons = new QGroupBox(tr("Lesson Selection"), this);

    availableLessonLayout = new QVBoxLayout();
    availableLessons->setLayout(availableLessonLayout);

    layout->addWidget(availableLessons);
    //End Notification Selection

    okButton = new QPushButton(tr("Submit"), this);
    connect(okButton, &QPushButton::pressed,
            this, &ChooseLessonDialog::okButtonPressHandler);
    layout->addWidget(okButton);
}

ChooseLessonDialog::~ChooseLessonDialog() {
    delete layout;
    layout = Q_NULLPTR;

    delete storyModeButton;
    storyModeButton=Q_NULLPTR;

    delete lessonModeButton;
    lessonModeButton=Q_NULLPTR;

    delete randomModeButton;
    randomModeButton=Q_NULLPTR;

    delete modeSelectionLayout;
    modeSelectionLayout=Q_NULLPTR;

    delete availableLessonLayout;
    availableLessonLayout=Q_NULLPTR;

    delete modeSelection;
    modeSelection = Q_NULLPTR;

    delete okButton;
    okButton = Q_NULLPTR;

    delete availableLessons;
    availableLessons=Q_NULLPTR;

    delete okButton;
    okButton=Q_NULLPTR;

}

QString ChooseLessonDialog::getCurrentlySelectedLesson() {
    return lastSelectedLesson;
}

QString ChooseLessonDialog::getNextLessonInStory() {
    return lastSelectedLesson;
}

void ChooseLessonDialog::updateAvailableLessons(lessonsArray newLessons) {
    for (QRadioButton* button : lessonButtons) {
        disconnect(button, &QPushButton::pressed,
                   this, &ChooseLessonDialog::lessonButtonHandler);
        availableLessonLayout->removeWidget(button);
        delete button;
    }

    for (QString lesson : newLessons) {
        QRadioButton *newButton = new QRadioButton(lesson, this);
        connect (newButton, &QPushButton::pressed,
                 this, &ChooseLessonDialog::lessonButtonHandler);
        availableLessonLayout->addWidget(newButton);
        lessonButtons.push_back(newButton);
    }
}

QString ChooseLessonDialog::convertTitleToChapterName(QString title) {
    /*
    title.replace(" ", "_");
    title.append("-");
    title.append(
                QString::number(lessonPart).rightJustified(3, '0'));
    title.append(".txt");
    */
    return title;
}

void ChooseLessonDialog::lessonButtonHandler() {
    if (!((QRadioButton*)sender())->isChecked()) {
        QString buttonText = ((QRadioButton*)sender())->text();
        lastSelectedLesson = convertTitleToChapterName(buttonText);
    }
}

void ChooseLessonDialog::okButtonPressHandler() {
    lessonPart = 1;
    emit chooseLessonConnectionInfo(lastSelectedLesson);
    this->hide();
}
