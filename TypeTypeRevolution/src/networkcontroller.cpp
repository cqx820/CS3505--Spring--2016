#include "networkcontroller.h"

#include <SFML/Network.hpp>

#include <iostream>
#include <thread>

NetworkController::NetworkController() {

}

NetworkState* NetworkController::connectToServer(sf::IpAddress server, int port) {
    NetworkState *toReturn = new NetworkState();

    toReturn->SFMLStatus = toReturn->socket.connect(server, port);

    if (toReturn->SFMLStatus != sf::Socket::Done) {
        toReturn->state = NetworkState::DISCONNECTED;
    } else {
        toReturn->state = NetworkState::CONNECTED;
    }

    return toReturn;
}

void NetworkController::requestMoreData(NetworkState *state) {
    std::thread asyncReceiveThread (receiveThread, state);
    asyncReceiveThread.detach();
}

void NetworkController::receiveThread(NetworkState *state) {
    state->SFMLStatus = state->socket.receive(state->data);
    state->callback(state);
}

void NetworkController::send(NetworkState *state, sf::Packet packet) {
    std::thread asyncSendThread (sendThread, state, packet);
    asyncSendThread.detach();
}

void NetworkController::sendThread(NetworkState *state, sf::Packet packet) {
    state->socket.send(packet);
    //state->callback(state);
    //NO CALLBACKS FOR SEND FUNCTIONS (WELL, MAYBE, BUT I CAN'T GET IT TO WORK)
}

void NetworkController::Server_Awaiting_Client_Loop(
        NetworkState::ConnectionCallback callback, int port) {
    std::thread thread(clientConnectThread, callback, port);
    thread.detach();
}

void NetworkController::clientConnectThread(
        NetworkState::ConnectionCallback callback, int port) {
    sf::TcpListener listener;

    // bind the listener to a port
    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cerr << "NetworkController: Unable to bind to port " << port << std::endl;
        return;
    } else {
        std::cout << "NetworkController: Succesfully bound listening port " << port << std::endl;
    }


    while (true) {
        // accept a new connection
        NetworkState *state = new NetworkState();
        state->SFMLStatus = listener.accept(state->socket);
        if (state->SFMLStatus != sf::Socket::Done)
        {
            std::cerr << "NetworkController: Error reveiving client connection" << std::endl;
        }
        std::thread(callback, state).detach();
    }
}

NetworkState::NetworkState() : callback(defaultSendCallback){
}

void NetworkState::defaultSendCallback(NetworkState*) {
    //Do nothing
}
