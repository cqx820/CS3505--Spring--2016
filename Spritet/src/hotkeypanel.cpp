/**
 * Filename: hotkeypanel.cpp
 * Author: Terrifying Nitpickers
 * Date: 29 March 2016
 */

#include "hotkeypanel.h"
#include <QHBoxLayout>
#include <QWidget>
#include <QString>

HotkeyPanel::HotkeyPanel(QWidget *parent) : QDockWidget(parent) {
    QWidget *hotkeypanels = new QWidget(this);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setSpacing(0);

    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    for (int i = 1; i < 11; i++) {
        buttons[i] = new QToolButton(this);
        layout->addWidget(buttons[i]);

        connect(buttons[i], &QToolButton::clicked,
                [=] { emit hotkeyClicked(i); });
    }

    setWidget(hotkeypanels);
    hotkeypanels->setLayout(layout);
    hotkeypanels->show();
    //hotkeypanels->setMaximumWidth(600);
}

HotkeyPanel::~HotkeyPanel() {
    for (int i = 1; i < 11; i++) {
        delete buttons[i];
    }
}

void HotkeyPanel::setHotkey(int button, Tool *tool) {
    buttons[button]->setText(QString::number(button));
    tools[button] = tool;
}

void HotkeyPanel::hotkeyNumber(int button) {
    auto iter = tools.find(button);
    if (iter != tools.end()) {
        emit applyHotkey(tools[button]);
    }
}
