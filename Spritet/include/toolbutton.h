/**
 * Filename: toolbutton.h
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 * Description:
 */

#ifndef TOOLBUTTON_H
#define TOOLBUTTON_H

#include <QToolButton>

class ToolButton : public QToolButton {
Q_OBJECT

public:
    ToolButton(QString name, QWidget *parent = Q_NULLPTR);

    QString getName();

    void setUserText(QString);

public slots:

signals:

private:
    QString name;
};

#endif // TOOLBUTTON_H
