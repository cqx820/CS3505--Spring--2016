#include "define.h"
#include "typetypepacket.h"

#include <SFML/Network.hpp>
#include <time.h>
#include <map>
#include <list>
#include <queue>


#ifndef TYPETYPECLIENT_H
#define TYPETYPECLIENT_H

class Client {
public:
	sf::TcpSocket *socket;
	int id;
	int story;
	
	std::queue<sf::Packet*> obuf;
	std::queue<sf::Packet*> ibuf;

	Client();
	~Client();
};

#endif
