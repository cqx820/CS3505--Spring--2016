#include "typetypeclient.h"
#include "define.h"

#include <SFML/Network.hpp>
#include <list>
#include <iostream>

#ifndef PROTO_H
#define PROTO_H

#define SALT "saltysaltness"

class Protocol {
	void Bool(Client*, bool);
public:
	void registerc(Client*, sf::Packet);
	void login(Client*, sf::Packet);
	void stories(Client*);
	void story(Client*, sf::Packet);
	void report(Client*, sf::Packet);
};

struct proto {
	sf::Uint8 code;
};

struct server_succ : public proto {
	const sf::Uint8 code = BYTE::SERVER_SUCC;
	friend sf::Packet & operator<<(sf::Packet& packet, const server_succ& proto) {
		return packet << proto.code;
	}
};

struct server_fail : public proto {
	const sf::Uint8 code = BYTE::SERVER_FAIL;
	friend sf::Packet & operator<<(sf::Packet& packet, const server_fail& proto) {
		return packet << proto.code;
	}
};

struct client_register : public proto {
	const sf::Uint8 code = BYTE::CLIENT_REGISTER;
	std::string nick;
	std::string name;
	std::string email;
	std::string pass;
	friend sf::Packet & operator<<(sf::Packet &packet, const client_register &proto) {
		return packet << proto.code << proto.nick << proto.name << proto.email << proto.pass;
	}
	friend sf::Packet & operator>>(sf::Packet &packet, client_register &proto) {
		return packet >> proto.nick >> proto.name >> proto.email >> proto.pass;
	}
};

struct client_login : public proto {
	const sf::Uint8 code = BYTE::CLIENT_LOGIN;
	std::string nick;
	std::string pass;
	friend sf::Packet & operator<<(sf::Packet& packet, const client_login& proto) {
		return packet << proto.code << proto.nick << proto.pass;
	}
	friend sf::Packet & operator>>(sf::Packet& packet, client_login& proto) {
		return packet >> proto.nick >> proto.pass;
	}
};

struct client_stories : public proto {
	const sf::Uint8 code = BYTE::CLIENT_STORIES;
	friend sf::Packet & operator<<(sf::Packet& packet, const client_stories& proto) {
		return packet << proto.code;
	}
};

struct server_stories : public proto {
	const sf::Uint8 code = BYTE::SERVER_STORIES;
	sf::Uint8 count;
	std::vector<std::string> stories;
	//std::vector<sf::Uint8> progress;
	//std::vector<sf::Uint8> amount;
	friend sf::Packet & operator<<(sf::Packet& packet, const server_stories& proto) {
		packet << proto.code << proto.count;
		for (int i = 0; i < (int)proto.count; i++)
			packet << proto.stories[i];
			//packet << proto.stories[i] << proto.progress[i] << proto.amount[i];
		return packet;
	}
	friend sf::Packet & operator>>(sf::Packet& packet, server_stories& proto) {
		packet >> proto.count;
		std::string story;
		//sf::Uint8 pro;
		//sf::Uint8 amt;
		for (int i = 0; i < proto.count; i++) {
			packet >> story;
			//packet >> story >> pro >> amt;
			proto.stories.push_back(story);
			//proto.progress.push_back(pro);
			//proto.amount.push_back(amt);
		}
		return packet;
	}
};

struct client_story : public proto {
	const sf::Uint8 code = BYTE::CLIENT_STORY;
	std::string story;
	friend sf::Packet & operator<<(sf::Packet& packet, const client_story& proto) {
		return packet << proto.code << proto.story;
	}
	friend sf::Packet & operator>>(sf::Packet& packet, client_story& proto) {
		return packet >> proto.story;
	}
};

struct server_story : public proto {
	const sf::Uint8 code = BYTE::SERVER_STORY;
	std::string content;
	friend sf::Packet & operator<<(sf::Packet& packet, const server_story& proto) {
		return packet << proto.code << proto.content;
	}
	friend sf::Packet & operator>>(sf::Packet& packet, server_story& proto) {
		return packet >> proto.content;
	}
};

struct client_report : public proto {
	const sf::Uint8 code = BYTE::CLIENT_REPORT;
	std::string story;
	std::string user;
	sf::Uint32 started; //time
	sf::Uint32 elapsed; //time
	sf::Uint8 completed; //buckets
	sf::Uint8 difficulty; // speed
	friend sf::Packet & operator<<(sf::Packet& packet, const client_report& proto) {
		return packet << proto.code << proto.story << proto.user << proto.started << proto.elapsed << proto.completed << proto.difficulty;
	}
	friend sf::Packet & operator>>(sf::Packet& packet, client_report& proto) {
		return packet >> proto.story >> proto.user >> proto.started >> proto.elapsed >> proto.completed >> proto.difficulty;;
	}
};

#endif
