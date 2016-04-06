/**
 * Filename: hotkeypanel.h
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */
#ifndef hotkeypanel_H
#define hotkeypanel_H

#include <QToolButton>
#include <QWidget>
#include <QDockWidget>
#include <QString>

#include "tool.h"

class HotkeyPanel : public QDockWidget {
Q_OBJECT

public:
    HotkeyPanel(QWidget *parent = Q_NULLPTR);

    ~HotkeyPanel();

public slots:

    void setHotkey(int, Tool *);

    void hotkeyNumber(int);

signals:

    void hotkeyClicked(int);

    void applyHotkey(Tool *);

private:
    std::map<int, QToolButton *> buttons;
    std::map<int, Tool *> tools;

};

#endif // hotkeypanel_H
