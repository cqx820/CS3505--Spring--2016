/**
 * Filename: toolbutton.cpp
 * Author: Terrifying Nitpickers
 * Date: 25 March 2016
 */

#include "toolbutton.h"
#include <QToolButton>
#include <QWidget>

ToolButton::ToolButton(QString tool_name, QWidget *parent) : QToolButton(
        parent) {
    name = tool_name;
}

QString ToolButton::getName() {
    return name;
}

void ToolButton::setUserText(QString text) {
    setText(text);
}
