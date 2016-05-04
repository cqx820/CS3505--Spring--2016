#include "typetypecallbackserver.h"

#include <string>

#include "callbackfunctor.h"
#include "networkcontroller.h"

TypeTypeCallbackServer::TypeTypeCallbackServer() {
    CallbackFunctor<TypeTypeCallbackServer> callback(
                &TypeTypeCallbackServer::clientConnectedCallback, this);
    NetworkController::Server_Awaiting_Client_Loop(callback, PORT);
}

void TypeTypeCallbackServer::clientConnectedCallback(NetworkState* state) {
    std::string html;
    html = "HTTP/1.1 200 OK\r\nConnection: close\n"
            "Content-Type: text/html; charset=UTF-8\n"
            "\n";
    html += "<HTML>\n";
    html += "<HEAD>\n";
    html += "table, th, td {\n\tborder-collapse: collapse;\n"
            "\tborder: 2px solid black;\n"
            "\tbackground-color: Linen;\n"
            "}\n";
    html += "</HEAD>\n";
    html += "<BODY>\n";
    html += "Here is some body text";
    html += "</BODY>/n";
    html += "</HTML>";
    sf::Packet toSend;
    toSend << html;
    CallbackFunctor<TypeTypeCallbackServer> callback(
                &TypeTypeCallbackServer::disconnectSocket, this);
    state->callback = callback;
    NetworkController::send(state, toSend);
}

void TypeTypeCallbackServer::disconnectSocket(NetworkState *state) {
    state->socket.disconnect();
}
