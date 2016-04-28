/**
 * Filename: wordbox.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 */

#include <typeinfo>
#include <QPlainTextEdit>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include "wordbox.h"
#include "typetypegui.h"


WordBox::WordBox(QWidget *parent, const QString &lesson)
    : QPlainTextEdit(lesson, parent) {
    this->setReadOnly(true);
    this->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
}

void WordBox::popWord(const QRegularExpression& deliminator) {
    /* This is not particularly efficient. We copy all the text into the stack,
     * then remove one word and replace everything in the text box with the
     * slightly shorter text.
     * Oh. Happily, I just looked it up and QStrings are mutable. Not so bad!
     */
    QString text = this->toPlainText();
    if (text.length() == 0) {
        emit outOfWords();
        return;
    }
    this->setPlainText(text.section(deliminator, 1)); //cuts off the first word
    emit poppedWord(text.section(deliminator, 0, 0));
}
