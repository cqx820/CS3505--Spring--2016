/**
 * Filename: typetypecontroller.h
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 * Description: This class is the puppet-master for the TypeTypeGUI
 */

#ifndef TYPETYPECONTROLLER_H
#define TYPETYPECONTROLLER_H

#include <SFML/Network.hpp>

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

public slots:
    void characterSuccess(bool isLastLetter);
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
    void wordTyped(QString word);
    void outOfWordsHandler();

    /**
     * This method should use the network, etc. to get a new lesson. It then
     * emits the "newLesson" signal
     */
    void chooseLessonConnectionInfoHandler(const QString&);


protected:

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
    void getNextWord();

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

    int seaWidth;
    int seaHeight;
    int seaPosX;
    int seaPosY;
    int gravity;
    std::map<int,Entity*> crateMap;
    std::map<int,QString> wordMap;
    sf::TcpSocket socket;
    sf::Socket::Status connectionStatus = sf::Socket::Disconnected;

private:
    //I'm going into model territory here...
    // todo: come to a consensus on where this should be
    QStringList storedLesson;
    int score = 0;
    int currentIndex = 0;
    int wordIndex=0;
    Entity* ship;

};

#endif // TYPETYPECONTROLLER_H
