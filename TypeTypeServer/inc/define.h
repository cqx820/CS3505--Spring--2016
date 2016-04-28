#include <SFML/Network.hpp>

#ifndef DEFINE_H
#define DEFINE_H

enum struct client_state {
	CONN,
	AUTH,
	SERVER_DISC,
	CLIENT_DISC
};

enum struct packet_state {
	SENT,
	RECV,
	PROC
};

enum BYTE : sf::Uint8 {
	SERVER_SUCC = 1,
	SERVER_FAIL = 2,
	CLIENT_REGISTER = 101,
	CLIENT_LOGIN = 102,
	SERVER_STORIES = 200,
	CLIENT_STORIES = 201,
	CLIENT_STORY = 202,
	CLIENT_REPORT = 203,
	SERVER_STORY = 204,
};
#endif
