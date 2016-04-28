#include "typetypehttp.h"

TypeTypeHttp::TypeTypeHttp() {
	selector = new sf::SocketSelector;
	server = new sf::TcpListener;
	
	listen();

	httpThread = new sf::Thread(&TypeTypeHttp::poll, this);
	httpThread->launch();

}

TypeTypeHttp::~TypeTypeHttp() {
	delete server;
}

void TypeTypeHttp::listen() {
	if (server->listen(HTTP_PORT) != sf::Socket::Done)
		std::cout << "http not listening 0.0.0.0:" << HTTP_PORT << std::endl;
	else
		std::cout << "http Listening 0.0.0.0:" << HTTP_PORT << std::endl;

	selector->add(*server);
}

void TypeTypeHttp::poll() {
	while (live) {
		if (selector->wait()) {
			if (selector->isReady(*server)) {
				sf::TcpSocket client;
				if (server->accept(client) == sf::Socket::Done) {
					client.send(html.c_str(), html.length());
					client.disconnect();
				}				
			}
		}
	}
}
