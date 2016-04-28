/**
 * Filename: networkcontroller.h
 * Author: //TO DO: Teamname
 * Date: 26 April 2016
 * Description: This class wraps sf::socket to preform asynchronous networking
 */

#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <SFML/Network.hpp>

/**
 * This is basically a bucket which stores data between sends
 */
class NetworkState {

public:
    NetworkState(void (*connectionCallback)(NetworkState), sf::Socket);

    enum ConnectionStates {
        /// <summary>
        /// The socket is in the connected state, with no data waiting to be read.
        /// </summary>
        CONNECTED,
        /// <summary>
        /// The socket is in the disconnected state.
        /// </summary>
        DISCONNECTED,
        /// <summary>
        /// The socket is in the connected state with data waiting to be read.
        /// </summary>
        HAS_DATA
    };
    void (*callback)(NetworkState);

    uint8_t buffer[];
};

class NetworkController {

public:
    const int PACKET_SIZE = 1024;

    static sf::Packet connectToServer(void (*connectionCallback)(NetworkState),
                               std::string hostName);

protected:
    NetworkController();
};

#endif // NETWORKCONTROLLER_H
