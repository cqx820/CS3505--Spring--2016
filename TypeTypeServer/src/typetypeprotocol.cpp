#include "typetypeprotocol.h"
#include "typetypeclient.h"
#include "typetypedb.h"

#include <SFML/Network.hpp>
#include <iostream>
#include <fstream>

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
	server_story proto;

	/*std::fstream fs;
	fs.open ("material/story/Alice In Wonderland/Alice In Wonderland-001.txt", std::fstream::in);
	std::string temp;
	while (fs >> temp)
		proto.content += temp + " ";	
	*/

	proto.content = "The quick brown fox jumps over the lazy dog";

	sf::Packet out;
	out << proto;
	client->socket->send(out);
}

void Protocol::report(Client *client, sf::Packet packet) {
	client_report proto;
	packet >> proto;

	TypeTypeDB db;
	bool status = db.db_report(proto);

	std::cout << "report: " << proto.user << " | " << status << std::endl;

	Bool(client, status);

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
