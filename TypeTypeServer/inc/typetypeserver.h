#include "typetypeclient.h"

#include <iostream>
#include <string>
#include <list>
#include <map>

#include <SFML/Network.hpp>

#ifndef TYPETYPESERVER_H
#define TYPETYPESERVER_H

#define PORT 1337
#define IP "173.230.241.105"
#define MAX_LEN 1024

class TypeTypeServer {
	std::list<Client*> clients;
	sf::SocketSelector *selector;
	sf::TcpListener *server;
	sf::Thread *rthread, *pthread;
	sf::Mutex lock;

public:
	TypeTypeServer();
	~TypeTypeServer();

	void kill();

private:
	bool live;

	void broadcast(sf::Packet *);
	void broadcast(char const *, size_t len);
	void broadcast(const std::list<Client*>, sf::Packet *);
	void broadcast_less(const std::list<Client*>, sf::Packet *);
	void disconnect(Client*);
	void poll();
	void proc();
	void listen();
	void send(Client*, char const *, size_t);
	void send(Client*, sf::Packet *);

public:

};

#endif
