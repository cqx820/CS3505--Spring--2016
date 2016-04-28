#include <SFML/Network.hpp>

#include <iostream>
#include <string>

#ifndef TYPETYPEHTTP_H
#define TYPETYPEHTTP_H

#define HTTP_PORT 1338

class TypeTypeHttp {
	sf::SocketSelector *selector;
	sf::TcpListener *server;
	sf::Thread *httpThread;

	std::string html = "Hello World!";

	void listen();
	void poll();

	bool live = true;
public:
	TypeTypeHttp();
	~TypeTypeHttp();
};

#endif
