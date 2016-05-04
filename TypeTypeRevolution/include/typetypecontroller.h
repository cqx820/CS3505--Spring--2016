/**
 * Filename: typetypecontroller.h
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This class is the puppet-master for the TypeTypeGUI
 */

#ifndef TYPETYPECONTROLLER_H
#define TYPETYPECONTROLLER_H

#include <SFML/Network.hpp>
#include "networkcontroller.h"

#include <QObject>
#include <Box2D/Box2D.h>
#include <QTimer>
#include "entity.h"
#include "typetypegui.h"
#include "mycontactlistener.h"
#include "buoyancy.h"

class TypeTypeController : public QObject {
    Q_OBJECT
public:
    const ushort PORT = 1337;
    const sf::Uint8 RESPONSE_FAIL = 2;
    const sf::Uint8 RESPONSE_SUCCESS = 1;

    const sf::Uint8 HANDSHAKE_RESPONSE = 100;
    const sf::Uint8 REGISTER_REQUEST = 101;
    const sf::Uint8 LOGIN_REQUEST = 102;
    const sf::Uint8 TITLES_RESPONSE = 200;
    const sf::Uint8 TITLES_REQUEST = 201;
    const sf::Uint8 STORY_REQUEST = 202;
    const sf::Uint8 REPORT_STORY = 203;
    const sf::Uint8 STORY_RESPONSE = 204;

    explicit TypeTypeController(TypeTypeGUI*, QObject *parent = 0);
    ~TypeTypeController();

signals:
    void newLesson(const QString&);
    void sendErrorToUser(QString errorMessage);
    void sendInformationToUser(QString infoMessage);
    void sendWord(QString word);
    void updateWorldSignal(b2World*);
    void addEntity(Entity*,std::string);
    void popNextWord(const QRegularExpression&);
    void updateScore(int score);
    void toggleStartAbortButton();
    void toggleCrateSignal(Entity*,bool);
    //todo:connect
    void highlightCrateText(Entity*,int);
    /**
     * Emitted to tell the GUI which titles the user can select from
     */
    void updateAvailableLessons(const ChooseLessonDialog::lessonsArray&);

public slots:
    void characterSuccess(bool isLastLetter, int toTypeIndex);
    void characterFailure();
    /**
     * Makes the specified server connection. Emits connectionFailed if
     * something goes wrong, and connectionSuccess otherwise
     */
    void connectButtonPressedHandler(QString URL, QString username,
                                     QString password, bool isLogin,
                                     QString email, QString realName);
    void updateWorld();
    void receivePoppedWord(QString word);
    void wordTyped();
    void outOfWordsHandler();

    /**
     * This method should use the network, etc. to get a new lesson. It then
     * emits the "newLesson" signal
     */
    void chooseLessonConnectionInfoHandler(const QString&);


protected:
    //Networking Data Members
    NetworkState *state = Q_NULLPTR;
    QString username;
    QString lastTitle;
    uint32 timeStarted;
    //End Networking Data Members

    b2World *world;
    QTimer box2DTimer;
    QTimer wordPopTimer;
    MyContactListner *listner;
    Buoyancy *thisBuoyancy;

    /**
     * Words per minute -- the rate at which we pop words and spawn new crates
     */
    double WPM = 60;
    TypeTypeGUI *gui;
    void getNextWord(int index);
    void skipWord();

    /**
     * Sets the timer which causes a word to be popped to have the interval
     * currently specified by WPM
     */
    void setWPMTimer(double WPM);

    /**
     * Calls for the next word to be sent down. 'Eventually' the
     * TypeTypeGUI::poppedWord signal should be triggered after calling this
     */
    void wordPopTimerHandler();

    //GUI handlers
    /**
     * Starts the simulation if not already running
     */
    void startButtonHandler();

    /**
     * Aborts the simulation if running
     */
    void abortButtonHandler();
    //End GUI handlers

    //Network handlers
    /**
     * Disconnects the socket and cleans it up
     */
    void disconnectSocket();

    /**
     * Called after the first connection and checks for server acknowlegement
     */
    void handshakeCallback(NetworkState* state);

    /**
     * Called after we request the list of titles from the server
     */
    void titlesListCallback(NetworkState* state);

    /**
     * Called after we request a story
     */
    void storyRequestCallback(NetworkState* state);

    //End Network handlers

    int seaWidth;
    int seaHeight;
    int seaPosX;
    int seaPosY;
    int gravity;
    std::map<int,Entity*> crateMap;
    std::map<int,QString> wordMap;

private:
    QStringList storedLesson;
    int score = 0;
    int currentListIndex = 0;
    int wordIndex=0;
    Entity* ship;
    Entity* sea;
    bool keyboardIsWaitingForWord = true;

};

#endif // TYPETYPECONTROLLER_H
