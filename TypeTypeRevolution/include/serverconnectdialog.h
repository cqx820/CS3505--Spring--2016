/**
 * Filename: servreconnectdialog.h
 * Author: //TO DO: Teamname
 * Date: 24 April 2016
 * Description: This class provides the user a place to enter the server
 *              connection information
 */

#ifndef SERVERCONNECTDIALOG_H
#define SERVERCONNECTDIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QWidget>

class ServerConnectDialog : public QWidget
{
    Q_OBJECT
public:
    explicit ServerConnectDialog(QWidget *parent = 0);
    ~ServerConnectDialog();

signals:
    void connectButtonPressed(QString URL, QString username, QString password,
                              bool isLogin, QString email, QString realName);

public slots:

protected:
    QLayout *layout;
    QLayout *leftLayout;
    QLayout *rightLayout;

    QWidget *leftWidget;
    QWidget *rightWidget;

    QLabel *serverURLLabel;
    QLabel *usernameLabel;
    QLabel *passwordLabel;
    QLabel *emailLabel;
    QLabel *nameLabel;

    QLineEdit *serverURLBox;
    QLineEdit *usernameBox;
    QLineEdit *passwordBox;
    QLineEdit *emailBox;
    QLineEdit *nameBox;

    QRadioButton *newAccountChoiceButton;
    QRadioButton *loginChoiceButton;

    QPushButton *submitButton;

protected slots:
    /**
     * Used to handle the loginChoiceButton and newAccountChoiceButton
     */
    void accountChoiceHandler();

    /**
     * Collects the data from the text boxes and emits connectButtonPressed
     */
    void submitButtonHandler();
};

#endif // SERVERCONNECTDIALOG_H
