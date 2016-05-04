#ifndef TYPETYPECALLBACKSERVER_H
#define TYPETYPECALLBACKSERVER_H

#include "networkcontroller.h"

class TypeTypeCallbackServer
{
public:
    const int PORT = 1338;

    TypeTypeCallbackServer();

protected:
    void clientConnectedCallback(NetworkState *state);
    void sendHTTPrequest(NetworkState *state);
    void disconnectSocket(NetworkState *state);
};

#endif // TYPETYPECALLBACKSERVER_H
