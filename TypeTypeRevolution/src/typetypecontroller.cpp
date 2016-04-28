/**
 * Filename: typetypecontroller.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 */

#include "typetypecontroller.h"

#include <SFML/Network.hpp>

#include <QDir>
#include <QDebug>

TypeTypeController::TypeTypeController(TypeTypeGUI *gui, QObject *parent)
    : QObject(parent), gui(gui) {
    seaWidth=1000;
    seaHeight=100;
    seaPosX=0;
    seaPosY=-600;
    gravity=-10;
    connect(this, &TypeTypeController::newLesson,
            gui, &TypeTypeGUI::setLesson);
    connect(this, &TypeTypeController::sendWord,
            gui, &TypeTypeGUI::sendWordToHandler);
    connect(this, &TypeTypeController::popNextWord,
            gui, &TypeTypeGUI::popWord);
    connect(this, &TypeTypeController::sendErrorToUser,
            gui, &TypeTypeGUI::connectionFailedHandler);
    connect(this, &TypeTypeController::sendInformationToUser,
            gui, &TypeTypeGUI::connectionSuccessHandler);
    connect(gui, &TypeTypeGUI::poppedWord,
            this, &TypeTypeController::receivePoppedWord);
    connect(gui, &TypeTypeGUI::outOfWords,
            this, &TypeTypeController::outOfWordsHandler);
    connect(gui, &TypeTypeGUI::connectButtonPressed,
            this, &TypeTypeController::connectButtonPressedHandler);

    //Connections for the GUI menu events
    connect(gui, &TypeTypeGUI::chooseLessonConnectionInfo,
            this, &TypeTypeController::chooseLessonConnectionInfoHandler);
    connect(gui, &TypeTypeGUI::changeWPM,
            this, &TypeTypeController::setWPMTimer);
    connect(gui, &TypeTypeGUI::startButtonPressed,
            this, &TypeTypeController::startButtonHandler);
    connect(gui, &TypeTypeGUI::abortButtonPressed,
            this, &TypeTypeController::abortButtonHandler);
    connect(this, &TypeTypeController::toggleStartAbortButton,
            gui, &TypeTypeGUI::toggleStartAbortButton);
    //End connections for the GUI menu events

    setWPMTimer(WPM);
    connect(&wordPopTimer, &QTimer::timeout,
            this, &TypeTypeController::wordPopTimerHandler);

    connect(gui, &TypeTypeGUI::characterSuccess,
            this, &TypeTypeController::characterSuccess);
    connect(gui, &TypeTypeGUI::characterFailure,
            this, &TypeTypeController::characterFailure);
    world = new b2World(b2Vec2(0, -10));
    listner=new MyContactListner();


    box2DTimer.setInterval(15);
    connect(&box2DTimer, &QTimer::timeout,this,&TypeTypeController::updateWorld);
    connect(this,&TypeTypeController::addEntity,gui,&TypeTypeGUI::addEntity);
    connect(this,&TypeTypeController::updateWorldSignal,gui,&TypeTypeGUI::updateWorldSignal);
    connect(this,&TypeTypeController::updateScore,gui,&TypeTypeGUI::updateScore);
    connect(this,&TypeTypeController::toggleCrateSignal,gui,&TypeTypeGUI::toggleCrateSignal);
    box2DTimer.start();


    Entity* entity= new Entity(world);
    entity->LoadWalls(seaPosX,seaPosY,seaWidth,seaHeight);
    emit addEntity(entity,"crate");
    ship = new Entity(world);
    ship->LoadCrate(seaWidth*.5,seaPosY*.8,seaWidth/4,33);
    ship->body->SetGravityScale(1);
    emit addEntity(ship,"");
    emit updateWorldSignal(world);
    world->SetContactListener(listner);
    thisBuoyancy = new Buoyancy(listner);
}

void TypeTypeController::updateWorld(){
    if(ship->body->GetPosition().y<seaPosY*.75){
        qDebug()<<"Called !!!!!!!!!!!!!!!!!!!!!!!!!!";
        ship->body->ApplyForce(b2Vec2(0,ship->body->GetMass() * 10),ship->body->GetWorldCenter(),true);
    }

    for (auto it = crateMap.begin(); it != crateMap.end();){
        Entity* crate=it->second;

        if (crate->body->GetPosition().y<seaPosY*.4)
        {
            emit toggleCrateSignal(crate,true);
            if(crate->crateTyped){
                crate->body->ApplyForce(b2Vec2(0,crate->body->GetMass() * -10),crate->body->GetWorldCenter(),true);
            }
            else{
//                b2Vec2 vel=crate->body->GetLinearVelocity();
//                vel.y=0;
//                crate->body->SetLinearVelocity(vel);
                crate->body->ApplyForce(b2Vec2(0,crate->body->GetMass() * -20),crate->body->GetWorldCenter(),true);
                crate->body->ApplyForce(b2Vec2(crate->body->GetMass() * -50,0),crate->body->GetWorldCenter(),true);
            }

        }
        if (crate->body->GetPosition().x<-10||crate->body->GetPosition().x>seaWidth+10||crate->body->GetPosition().y<-1000){
            world->DestroyBody(crate->body);
            delete crate;
            crateMap.erase(it++);
        }
        else{
            ++it;
        }

    }
    world->Step(1/ 30.0f, 6, 2);
    thisBuoyancy->Step();
    emit updateWorldSignal(world);
    //Change this to when the score actually change
    emit updateScore(score);
}

void TypeTypeController::receivePoppedWord(QString word) {
    if (word.simplified() == "") {
        //String is empty or all white space. Move along. Nothing to see.
        return;
    }
    //qDebug() << Q_FUNC_INFO << "word reached";
    wordMap[wordIndex]=word;
    Entity* entity= new Entity(world);
    entity->LoadCrate(rand()%((int)(seaWidth*.8))+seaWidth/25,0,seaWidth/40,seaWidth/40);
    crateMap[wordIndex++]=entity;
    emit addEntity(entity,word.toStdString());
}

void TypeTypeController::outOfWordsHandler() {
    emit toggleStartAbortButton();
}

void TypeTypeController::wordTyped(QString word){
    int key = 0;
      for (auto i = wordMap.begin(); i != wordMap.end();) {
         if (i->second==word) {
            key = i->first;
            wordMap.erase(i++);
            break;
         }
      }

      auto it= crateMap.find(key);
      it->second->crateTyped=true;


}

void TypeTypeController::chooseLessonConnectionInfoHandler(const QString& info) {
    //TODO: Make this method use the network, etc.
    QString lesson = "This is some text with a few words.";
    lesson += "\n";
    lesson += info;
    storedLesson = lesson.split(" ", QString::SkipEmptyParts);
    emit newLesson(lesson);
    emit sendWord(storedLesson.at(currentIndex));
}

void TypeTypeController::setWPMTimer(double WPM) {
    //60,000 ms per minute
    wordPopTimer.setInterval((int) (60000 / WPM));

    if (currentIndex >= storedLesson.size()) {
        emit sendWord("");
    } else {
        emit sendWord(storedLesson[currentIndex]);
    }

}

void TypeTypeController::wordPopTimerHandler() {
    emit popNextWord(QRegularExpression("\\s"));
}

void TypeTypeController::characterSuccess(bool isLastLetter) {
    score++;
    if (isLastLetter) {
        score += 10;
        getNextWord();
    }
}

void TypeTypeController::getNextWord() {
    if (currentIndex == storedLesson.size() - 1) {
        return;
        //todo: implement end of lesson behavior
    }
    emit sendWord(storedLesson.at(++currentIndex));
}

void TypeTypeController::startButtonHandler() {
    wordPopTimer.start();
}

void TypeTypeController::abortButtonHandler() {
    //This should probably do something like clear the word box, but eh.
    wordPopTimer.stop();
}

void TypeTypeController::characterFailure() {
    score--;
}

void TypeTypeController::connectButtonPressedHandler(QString URL,
                                            QString username, QString password,
                                            bool isLogin, QString email,
                                            QString realName) {
    sf::IpAddress remoteIP(URL.toStdString());
    if (remoteIP == sf::IpAddress::None) {
        emit sendErrorToUser(tr("Connection failed: Invalid hostname or IP"));
        return;
    }
    //Check if the socket is already connected. Connect if not.
    if (connectionStatus != sf::Socket::Done) {
        connectionStatus = socket.connect(URL.toStdString(), PORT);
    }
    //Check that the connection was successful
    if (connectionStatus != sf::Socket::Done){
        //TODO: Figure out error handling for sockets
        emit sendErrorToUser(tr("Connection Failed after DNS resolution"));
    } else {
        emit sendInformationToUser(tr("Successfully connected to ") + URL);
        sf::Packet data;
        if (isLogin) {
            data << uint8(102)
                 << username.toStdString()
                 << password.toStdString();
        } else { //Register user
            data << uint8(101)
                 << username.toStdString()
                 << email.toStdString()
                 << realName.toStdString()
                 << password.toStdString();
        }
        socket.send(data);
    }
}

TypeTypeController::~TypeTypeController() {
    delete gui;
    delete world;
    delete thisBuoyancy;
}

