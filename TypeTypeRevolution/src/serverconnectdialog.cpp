/**
 * Filename: servreconnectdialog.h
 * Author: //TO DO: Teamname
 * Date: 24 April 2016
 */

#include "serverconnectdialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QBoxLayout>

ServerConnectDialog::ServerConnectDialog(QWidget *parent) : QWidget(parent) {

    layout = new QHBoxLayout();
    leftLayout = new QVBoxLayout();
    rightLayout = new QVBoxLayout();

    layout->setSizeConstraint(QLayout::SetFixedSize);
    leftLayout->setSizeConstraint(QLayout::SetFixedSize);
    rightLayout->setSizeConstraint(QLayout::SetFixedSize);

    leftWidget = new QWidget(this);
    rightWidget = new QWidget(this);

    serverURLLabel = new QLabel(tr("Server URL"), this);
    leftLayout->addWidget(serverURLLabel);

    serverURLBox = new QLineEdit(this);
    rightLayout->addWidget(serverURLBox);

    usernameLabel = new QLabel(tr("Nickname"), this);
    leftLayout->addWidget(usernameLabel);

    usernameBox = new QLineEdit(this);
    rightLayout->addWidget(usernameBox);

    passwordLabel = new QLabel(tr("Password"), this);
    leftLayout->addWidget(passwordLabel);

    passwordBox = new QLineEdit(this);
    rightLayout->addWidget(passwordBox);
    passwordBox->setEchoMode(QLineEdit::Password);

    newAccountChoiceButton = new QRadioButton(tr("New Account"), this);
    leftLayout->addWidget(newAccountChoiceButton);
    connect(newAccountChoiceButton, &QRadioButton::pressed,
            this, &ServerConnectDialog::accountChoiceHandler);

    loginChoiceButton = new QRadioButton(tr("Login"), this);
    rightLayout->addWidget(loginChoiceButton);
    connect(loginChoiceButton, &QRadioButton::pressed,
            this, &ServerConnectDialog::accountChoiceHandler);

    emailLabel = new QLabel(tr("Email"), this);
    leftLayout->addWidget(emailLabel);

    emailBox = new QLineEdit(this);
    rightLayout->addWidget(emailBox);

    nameLabel = new QLabel(tr("Real Name"), this);
    leftLayout->addWidget(nameLabel);

    nameBox = new QLineEdit(this);
    rightLayout->addWidget(nameBox);

    submitButton = new QPushButton(tr("Submit"), this);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::pressed,
            this, &ServerConnectDialog::hide);
    connect(submitButton, &QPushButton::pressed,
            this, &ServerConnectDialog::submitButtonHandler);

    leftWidget->setLayout(leftLayout);
    rightWidget->setLayout(rightLayout);

    layout->addWidget(leftWidget);
    layout->addWidget(rightWidget);

    this->setLayout(layout);

    //Set up the GUI by pushing the "Login" button
    loginChoiceButton->animateClick(0);
}

ServerConnectDialog::~ServerConnectDialog() {
    delete layout;
    layout = Q_NULLPTR;

    delete leftLayout;
    leftLayout = Q_NULLPTR;

    delete rightLayout;
    rightLayout = Q_NULLPTR;

    delete leftWidget;
    leftWidget = Q_NULLPTR;

    delete rightWidget;
    rightWidget = Q_NULLPTR;
}

void ServerConnectDialog::accountChoiceHandler() {
    if (sender() == newAccountChoiceButton) {
        loginChoiceButton->setChecked(false);
        emailLabel->show();
        emailBox->show();
        nameLabel->show();
        nameBox->show();
    } else if (sender() == loginChoiceButton) {
        newAccountChoiceButton->setChecked(false);
        emailLabel->hide();
        emailBox->hide();
        nameLabel->hide();
        nameBox->hide();
    }
}

void ServerConnectDialog::submitButtonHandler() {
    emit connectButtonPressed(serverURLBox->text(),
                              usernameBox->text(),
                              passwordBox->text(),
                              loginChoiceButton->isChecked(),
                              emailBox->text(),
                              nameBox->text());
}
