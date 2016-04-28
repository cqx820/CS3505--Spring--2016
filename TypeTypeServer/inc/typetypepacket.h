#include "define.h"

#include <SFML/Network.hpp>
#include <time.h>
#include <map>

#ifndef TYPETYPEPACKET_H
#define TYPETYPEPACKET_H

class Packet {
public:
	sf::Uint8 type;
	sf::Packet *packet;
	packet_state state;
	std::map<time_t, packet_state> history;
};

#endif
