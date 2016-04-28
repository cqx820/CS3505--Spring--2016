#include "typetypeprotocol.h"
#include "typetypeclient.h"
#include "typetypedb.h"

#include <SFML/Network.hpp>
#include <iostream>

void Protocol::registerc(Client *client, sf::Packet packet) {
	client_register proto;
	packet >> proto;
	
	TypeTypeDB db;
	bool status = db.db_register(proto);

	std::cout << "register: " << proto.nick << " | " << status << std::endl;

	Bool(client, status);
}

void Protocol::login(Client *client, sf::Packet packet) {
	client_login proto;
	packet >> proto;

	TypeTypeDB db;
	int id = db.db_login(proto);
	client->id = id;

	std::cout << "login: " << proto.nick << " | " << id << std::endl;

	Bool(client, (id != 0));
}

void Protocol::stories(Client *client) {
	TypeTypeDB db;
	server_stories stories = db.db_stories();

	sf::Packet out;
	out << stories;
	
	for (auto foo : stories.stories)
		std::cout << foo;

	client->socket->send(out);
}

void Protocol::story(Client *client, sf::Packet packet) {
	client_story proto;
	packet >> proto;
}

void Protocol::report(Client *client, sf::Packet packet) {
	client_report proto;
	packet >> proto;
}

void Protocol::Bool(Client *client, bool status) {
	sf::Packet out;
	sf::Uint8 code = 100;
	out << code;
	if (status) {
		server_succ succ;
		out << succ;
	} else {
		server_fail fail;
		out << fail;
	}
	client->socket->send(out);
}
