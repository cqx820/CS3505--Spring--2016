/**
 * Filename: wordbox.h
 * Author: //TO DO: Teamname
 * Date: 18 April 2016
 * Description: This class is used as part of the TypeTypeGUI to store and
 * display the sentences being typed.
 */

#ifndef WORDBOX_H
#define WORDBOX_H

#include <QPlainTextEdit>
#include <QRegularExpression>

class WordBox : public QPlainTextEdit {
    Q_OBJECT
public:
    /**
     * @brief WordBox
     * @param lesson The entire lesson to be typed through should be referenced
     * @param parent
     */
    explicit WordBox(QWidget *parent, const QString &lesson = "");

signals:
    /**
     * Emitted after the popWord slot is called if there is a word to return
     */
    void poppedWord(QString);
    /**
     * Emitted when the word box attempts to pop a word but there is nothing to
     * pop
     */
    void outOfWords();

public slots:
    /**
     * Removes the first word as specified by the deliminator and emits the
     * poppedWord signal
     */
    void popWord(const QRegularExpression&);



};

#endif // WORDBOX_H
