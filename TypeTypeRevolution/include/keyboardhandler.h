/**
 * Filename: typetypecontroller.h
 * Author: //TO DO: Teamname
 * Date: 18 April 2016
 * Description: This class handles
 *      - Keyboard entry
 *      - Comparing against the current word
 *      - Scoring
 *      - Getting the next word
 *      - todo: signaling that the lesson has been finished
 */

#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <QObject>
#include <QKeyEvent>

class KeyboardHandler : public QObject {
    Q_OBJECT
public:
    explicit KeyboardHandler();
    ~KeyboardHandler();

signals:
    void characterAttemptSuccess(bool isLastLetter);
    void characterAttemptFailure();


public slots:
    void receiveWord(QString word);
    void receiveCharacterAttempt(QKeyEvent *event);

private:
    QString currentWord;
    int letterIndex;

};

#endif //KEYBOARDHANDLER_H
