/**
 * Filename: networkcontroller.h
 * Author: //TO DO: Teamname
 * Date: 26 April 2016
 * Description: This class wraps sf::socket to preform asynchronous networking
 */

#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <SFML/Network.hpp>
#include <functional>

/**
 * This is basically a bucket which stores data between sends
 */
class NetworkState {

public:
    NetworkState();

    enum ConnectionState {
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
    typedef std::function<void(NetworkState*)> ConnectionCallback;

    ConnectionCallback callback = defaultSendCallback;
    //void (*callback)(NetworkState*);
    sf::Packet data;
    sf::TcpSocket socket;
    ConnectionState state;
    sf::Socket::Status SFMLStatus;

protected:
    static void defaultSendCallback(NetworkState*);
};

class NetworkController {

public:
    //const int PACKET_SIZE = 1024;

    /**
     * Call this method first to connect the socket and generate a NetworkState
     */
    static NetworkState* connectToServer(sf::IpAddress server, int port);

    /**
     * Call this method with a NetworkState with a connected socket to send
     * the packet asynchronously
     */
    static void send(NetworkState*, sf::Packet);

    /**
     * Call this method with a NetworkState with a connected socket to wait
     * for data. The NetworkState->callback will be called when data is
     * returned
     */
    static void requestMoreData(NetworkState* state);

    /**
     * Starts off a loop which will spawn new NetworkStates with a connected
     * port for each new client. This NetworkState will go into the callback.
     * @param callback Client connected callback
     * @param port Server listener port
     */
    static void Server_Awaiting_Client_Loop(
            NetworkState::ConnectionCallback callback, int port);
protected:
    NetworkController();
    void static receiveThread(NetworkState *state);
    void static sendThread(NetworkState *state, sf::Packet data);
    void static clientConnectThread(
            NetworkState::ConnectionCallback callback, int port);
};

#endif // NETWORKCONTROLLER_H
