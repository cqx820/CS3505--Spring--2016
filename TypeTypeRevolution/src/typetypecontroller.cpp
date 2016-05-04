/**
 * Filename: typetypecontroller.cpp
 * Author: //TO DO: Teamname
 * Date: 12 April 2016
 */

#include "typetypecontroller.h"

#include <SFML/Network.hpp>
#include "networkcontroller.h"
#include "callbackfunctor.h"

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
    connect(this, &TypeTypeController::updateAvailableLessons,
            gui, &TypeTypeGUI::updateAvailableLessons);

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
    connect(this,&TypeTypeController::highlightCrateText,gui,&TypeTypeGUI::highlightTextOnCrate);
    box2DTimer.start();


    sea= new Entity(world);
    sea->LoadWalls(seaPosX,seaPosY,seaWidth,seaHeight);
    emit addEntity(sea,"");
    ship = new Entity(world);
    ship->LoadCrate(seaWidth*.5,seaPosY*.8,seaWidth/4,33);
    ship->body->SetGravityScale(1);
    emit addEntity(ship,"");
    emit updateWorldSignal(world);
    world->SetContactListener(listner);
    thisBuoyancy = new Buoyancy(listner);

    // Register our special type so we can send it accross thread boundries
    qRegisterMetaType<ChooseLessonDialog::lessonsArray>("ChooseLessonDialog::lessonsArray");
}

TypeTypeController::~TypeTypeController() {
    for(auto it:crateMap){
        delete it.second;
    }
    delete listner;
    delete sea;
    delete ship;
    if (state != Q_NULLPTR) {
        delete state;
        state = Q_NULLPTR;
    }
    delete gui;
    delete world;
    delete thisBuoyancy;
}

void TypeTypeController::updateWorld(){
    auto shipPos=ship->body->GetPosition().y;
    if(shipPos<seaPosY*.75){
        ship->body->ApplyForce(b2Vec2(0,ship->body->GetMass() * 10),ship->body->GetWorldCenter(),true);
    }

    for (auto it = crateMap.begin(); it != crateMap.end();){
        Entity* crate=it->second;

        if (crate->body->GetPosition().y<seaPosY*.5)
        {
            //emit toggleCrateSignal(crate,true);
            if(crate->crateTyped){
                crate->body->ApplyForce(b2Vec2(0,crate->body->GetMass() * -10),crate->body->GetWorldCenter(),true);
            }
            else{
//                b2Vec2 vel=crate->body->GetLinearVelocity();
//                vel.y=0;
//                crate->body->SetLinearVelocity(vel);
                crate->body->ApplyForce(b2Vec2(0,crate->body->GetMass() * -20),crate->body->GetWorldCenter(),true);
                crate->body->ApplyForce(b2Vec2(crate->body->GetMass() * -50,0),crate->body->GetWorldCenter(),true);

                //Cutoff point for typing the crate.
                //Only skip if the crate hasn't been marked as such yet
                if(crate->notSkipped){
                    crate->notSkipped = false;
                    skipWord();
                }
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
    wordMap[wordIndex]=word;
    Entity* entity= new Entity(world);
    entity->LoadCrate(rand()%((int)(seaWidth*.8))+seaWidth/25,0,seaWidth/40,seaWidth/40);
    crateMap[wordIndex++]=entity;
    emit addEntity(entity,word.toStdString());

    if(keyboardIsWaitingForWord && currentListIndex < crateMap.size()) {
        //for the case where the user is typing faster than words are appearing
        //remove the flag
        keyboardIsWaitingForWord = false;

        getNextWord(currentListIndex);

        auto nextCrate = crateMap.find(currentListIndex);
        emit toggleCrateSignal(nextCrate->second, true);
    }
}

void TypeTypeController::characterSuccess(bool isLastLetter, int toTypeIndex) {
    score++;
    auto crate = crateMap.find(currentListIndex);
    emit highlightCrateText(crate->second, toTypeIndex);

    if (isLastLetter) {
        score += 10;

        crate->second->crateTyped = true;
        emit toggleCrateSignal(crate->second, false);

        currentListIndex++;
        //If the word typed is the last one in the queue, set
        // keyboardIsWaitingForWord, and let wordPoppedHandler take care of
        // getting the next word as well as crate highlighting
        if (currentListIndex >= wordIndex) {
            keyboardIsWaitingForWord = true;
            return;
        }

        getNextWord(currentListIndex);

        if (currentListIndex < crateMap.size()) {
            auto nextCrate = crateMap.find(currentListIndex);
            emit toggleCrateSignal(nextCrate->second, true);
        }
    }
}

void TypeTypeController::skipWord() {
    qDebug() << "[INFO] skipped word: " << storedLesson.at(currentListIndex);

    score -= 10;

    auto crate = crateMap.find(currentListIndex);
    emit highlightCrateText(crate->second, 0);
    emit toggleCrateSignal(crate->second, false);

    currentListIndex++;
    //If the word typed is the last one in the queue, set
    // keyboardIsWaitingForWord, and let wordPoppedHandler take care of
    // getting the next word as well as crate highlighting
    if (currentListIndex >= wordIndex) {
        keyboardIsWaitingForWord = true;
        return;
    }

    getNextWord(currentListIndex);

    if (currentListIndex < crateMap.size()) {
        auto nextCrate = crateMap.find(currentListIndex);
        emit toggleCrateSignal(nextCrate->second, true);
    }
}

void TypeTypeController::getNextWord(int index) {
    if (index >= storedLesson.size()) {
        emit sendWord("");
        sf::Packet toSend;
        toSend << REPORT_STORY
               << lastTitle.toStdString()
               << username.toStdString()
               << (sf::Int32)score;
        NetworkController::send(state, toSend);
        return;
        //todo: implement end of lesson behavior
    }
    emit sendWord(storedLesson.at(index));
}

void TypeTypeController::outOfWordsHandler() {
    /*
    toSend << REPORT_STORY
           << lastTitle.toStdString() //std::string Storyname
           << username.toStdString()//std::string Username
           << timeStarted //Uint32 timeStarted
           << ((uint32)time(NULL) - timeStarted) //Uint32 timeElapsed
           << (sf::Uint8)100 //Uint8 %complete
           << (sf::Uint8)WPM; //Uint8 difficulty
    */
    emit toggleStartAbortButton();
}

void TypeTypeController::wordTyped(){
      auto it= crateMap.find(currentListIndex - 1);
      it->second->crateTyped=true;
}

void TypeTypeController::chooseLessonConnectionInfoHandler(const QString& info) {
    if (state == Q_NULLPTR) {
        emit sendErrorToUser(tr("Not connected to a server!"));
        return;
    }
    lastTitle = info;
    sf::Packet toSend;
    toSend << STORY_REQUEST << info.toStdString();

    NetworkController::send(state, toSend);

    CallbackFunctor<TypeTypeController> callback(
                &TypeTypeController::storyRequestCallback, this);
    state->callback = callback;
    NetworkController::requestMoreData(state);
}

void TypeTypeController::setWPMTimer(double WPM) {
    //60,000 ms per minute
    wordPopTimer.setInterval((int) (60000 / WPM));
}

void TypeTypeController::wordPopTimerHandler() {
    emit popNextWord(QRegularExpression("\\s"));
}

void TypeTypeController::startButtonHandler() {
    wordPopTimer.start();
    timeStarted = time(NULL);
}

void TypeTypeController::abortButtonHandler() {
    //This should probably do something like clear the word box, but eh.
    emit newLesson("");
    wordPopTimer.stop();
}

void TypeTypeController::characterFailure() {
    if(currentListIndex < storedLesson.size()) {
        score--;
    }
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
    state = NetworkController::connectToServer(remoteIP, PORT);
    /*
    //Check if the socket is already connected. Connect if not.
    if (connectionStatus != sf::Socket::Done) {
        connectionStatus = socket.connect(URL.toStdString(), PORT);
    }
    */
    //Check that the connection was successful
    if (state->SFMLStatus != sf::Socket::Done){
        //TODO: Figure out error handling for sockets
        emit sendErrorToUser(tr("Connection Failed after DNS resolution"));
    } else {
        emit sendInformationToUser(tr("Successfully connected to ") + URL);
        sf::Packet data;
        if (isLogin) {
            data << LOGIN_REQUEST
                 << username.toStdString()
                 << password.toStdString();
        } else { //Register user
            data << REGISTER_REQUEST
                 << username.toStdString()
                 << email.toStdString()
                 << realName.toStdString()
                 << password.toStdString();
        }
        NetworkController::send(state, data);
    }
    this->username = username;
    CallbackFunctor<TypeTypeController> callback(
                &TypeTypeController::handshakeCallback, this);
    state->callback = callback;
    NetworkController::requestMoreData(state);
}

void TypeTypeController::disconnectSocket() {
    state->socket.disconnect();
    delete state;
    state = Q_NULLPTR;
}

void TypeTypeController::handshakeCallback(NetworkState *state) {
    if (state->SFMLStatus == sf::Socket::Disconnected) {
        emit sendErrorToUser(tr("Handshake error: The remote closed the connection"));
        delete state;
        state = Q_NULLPTR;
        return;
    }
    uint8_t packetCode;
    sf::Uint8 result;
    state->data >> packetCode >> result;
    if (packetCode != HANDSHAKE_RESPONSE) {
        sendErrorToUser(tr("Server replied to login handshake with invalid"
                           "packet code"));
        disconnectSocket();
        return;
    } else if (result == RESPONSE_SUCCESS) {
        emit sendInformationToUser(tr("Handshake: Login accepted"));
        sf::Packet requestTitlesPacket;
        requestTitlesPacket << TITLES_REQUEST;
        NetworkController::send(state, requestTitlesPacket);
        CallbackFunctor<TypeTypeController> callback(
                    &TypeTypeController::titlesListCallback, this);
        state->callback = callback;
        NetworkController::requestMoreData(state);
    } else {
        emit sendErrorToUser(tr("Login failed"));
        state->socket.disconnect();
        disconnectSocket();
        return;
    }
    qDebug() << "[NET]  packet code: " << packetCode <<  ", result: " << result;
}

void TypeTypeController::titlesListCallback(NetworkState *state) {
    uint8_t packetCode;

    state->data >> packetCode;

    if (packetCode != TITLES_RESPONSE){
        emit sendErrorToUser(tr("Invalid response to titles list request"));
        disconnectSocket();
        return;
    }

    QVector<QString> titles;
    sf::Uint8 numberOfStories;
    state->data >> numberOfStories;
    std::string title;
    while (state->data >> title) {
        titles.push_back(QString::fromStdString(title));
        qDebug() << "[NET]  packet code: " << packetCode << ", result: "
            << QString::fromStdString(title);
    }
    emit updateAvailableLessons(titles);
}

void TypeTypeController::storyRequestCallback(NetworkState *state) {
    uint8_t packetCode;

    state->data >> packetCode;

    if (packetCode != STORY_RESPONSE){
        emit sendErrorToUser(tr("Invalid response to story request"));
        disconnectSocket();
        return;
    }

    std::string story;
    if (!(state->data >> story)) {
        emit sendErrorToUser(tr("No story received!"));
    }

    QString lesson;
    /*lesson += "This is some text with a few words. "
            "This line should be removed. It is in the storyRequestCallback"
            "method of TypeTypeController.";
    lesson += "\n";*/
    lesson += QString::fromStdString(story);
    storedLesson = lesson.split(" ", QString::SkipEmptyParts);
    emit newLesson(lesson);
}

