/**
 * Filename: chooselessondialog.h
 * Author: //TO DO: Teamname
 * Date: 22 April 2016
 * Description: This class provides a quick way to select the next lesson
 */

#ifndef CHOOSELESSONDIALOG_H
#define CHOOSELESSONDIALOG_H

#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

class ChooseLessonDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ChooseLessonDialog(QWidget *parent = 0);
    ~ChooseLessonDialog();

    /**
     * When sending "complicated things" over thread boundries, special
     * precautions have to be taken
     * https://forum.qt.io/topic/2826/solved-cross-thread-signal-cannot-queue-arguments-of-type-qvector-qvector-int/2
     */
    typedef QVector<QString> lessonsArray;

    /**
     * Return lastSelectedLesson
     */
    QString getCurrentlySelectedLesson();

    /**
     * Parse lastSelectedLesson
     */
    QString getNextLessonInStory();

signals:
    /**
     * Emitted when the user presses okay on the choose lesson dialog or
     * requests the next lesson in a story. The parameter contains the data
     * of the lesson needing to be passed to the server
     */
    void chooseLessonConnectionInfo(const QString&);

public slots:
    /**
     * Deletes the current knowledge of lessions and adds the passed ones
     */
    void updateAvailableLessons(lessonsArray);

protected:
    QString lastSelectedLesson;
    /**
     * Increment by 1 every time we ask for the next lesson,
     * (re)set when we get a new lesson
     */
    int lessonPart = 1;

    QLayout *layout;

    QGroupBox *modeSelection;
    QLayout *modeSelectionLayout;
    QRadioButton *storyModeButton;
    QRadioButton *lessonModeButton;
    QRadioButton *randomModeButton;

    QGroupBox *availableLessons;
    QLayout *availableLessonLayout;
    std::vector<QRadioButton*> lessonButtons;
    QPushButton *okButton;

    QString convertTitleToChapterName(QString);


protected slots:
    void lessonButtonHandler();
    void okButtonPressHandler();

};

#endif // CHOOSELESSONDIALOG_H
