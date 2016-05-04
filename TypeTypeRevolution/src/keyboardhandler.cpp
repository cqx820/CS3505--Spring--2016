//
// Created by Guy Watson on 4/18/16.
//

#include <QObject>
#include <QKeyEvent>
#include <QDebug>
#include "keyboardhandler.h"

KeyboardHandler::KeyboardHandler() {
    //todo: connect dat shit
}

KeyboardHandler::~KeyboardHandler() {
    //uuhhhhhh... nothing?
    //todo: revisit
}

void KeyboardHandler::receiveWord(QString word) {
    currentWord = word;
    letterIndex = 0;
    qDebug() << "[INFO] KeyboardHandler received word: " << currentWord;
}

void KeyboardHandler::receiveCharacterAttempt(QKeyEvent *event) {
    if (currentWord.isEmpty() || event->text().isEmpty()) {
        return;
    }

    if (event->text() == currentWord.at(letterIndex)) {
        letterIndex++;
        bool isLastLetter = false;
        if (letterIndex >= currentWord.size()) {
            qDebug() << "[INFO] finished word: " << currentWord;
            isLastLetter = true;
            currentWord = "";
        }
        emit characterAttemptSuccess(isLastLetter, letterIndex);
    } else {
        emit characterAttemptFailure();
    }
}




