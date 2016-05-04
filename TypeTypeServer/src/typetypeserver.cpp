#include "typetypeserver.h"
#include "typetypeclient.h"
#include "typetypeprotocol.h"
#include "define.h"
#include "typetypehttp.h"

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

#include <SFML/Network.hpp>

TypeTypeServer::TypeTypeServer() {
	selector = new sf::SocketSelector;
	server = new sf::TcpListener;

	live = true;

	listen();
	rthread = new sf::Thread(&TypeTypeServer::poll, this);
	rthread->launch();

	pthread = new sf::Thread(&TypeTypeServer::proc, this);
	pthread->launch();
}

TypeTypeServer::~TypeTypeServer() {
	delete server;
	delete selector;
	
	for (auto client : clients)
		delete client;
}

void TypeTypeServer::listen() {
	if (server->listen(PORT) != sf::Socket::Done)
		std::cout << "Not listening 0.0.0.0:" <<  PORT << std::endl;
	else
		std::cout << "Listening 0.0.0.0:" << PORT << std::endl;

	selector->add(*server);
}

void TypeTypeServer::poll() {
	while (live) {
		lock.lock();
		if (selector->wait()) {
			if (selector->isReady(*server)) {
				sf::TcpSocket *client_socket = new sf::TcpSocket;
				if (server->accept(*client_socket) == sf::Socket::Done) {
					std::cout << "client connected" << std::endl;
					selector->add(*client_socket);
					Client *client = new Client;
					client->socket = client_socket;
					client->socket->setBlocking(false);
					clients.push_back(client);
				} else {
					delete client_socket;
				}
			} else {
				std::list<Client*> clean;
				for (auto client : clients) {
					sf::Packet *recv = new sf::Packet;
					switch (client->socket->receive(*recv)) {
						case sf::Socket::Disconnected:
							std::cout << "[" << clients.size() << "] Client disconnected" << std::endl;
							clean.push_back(client);
							break;
						case sf::Socket::Done:
							client->ibuf.push(recv);
							break;
						default:
							break;
					}
				}	
				for (auto client: clean) {
					clients.remove(client);
				}
			}
		}
		lock.unlock();
	}
}

void TypeTypeServer::proc() {
	sf::Uint8 type;
	Protocol p;
	while (live) {
		lock.lock();
		for (auto client : clients) {
			if (client->ibuf.size() > 0) {
				sf::Packet packet = (*client->ibuf.front());
				client->ibuf.pop();
				packet >> type;
				switch (type) {
					case BYTE::CLIENT_REGISTER: // client_register
						p.registerc(client, packet);
						break;
					case BYTE::CLIENT_LOGIN: // client_login
						p.login(client, packet);
						break;
					case BYTE::CLIENT_STORIES: // client_stories
						p.stories(client);
						break;
					case BYTE::CLIENT_STORY: // client_story
						p.story(client, packet);
						break;
					case BYTE::CLIENT_REPORT: // client_report
						p.report(client, packet);
						break;
					default:
						break;
				}
			}
		}
		lock.unlock();
	}
}

void TypeTypeServer::send(Client *client, sf::Packet *data) {
	if (client->socket->send(*data) != sf::Socket::Done)
		disconnect(client); // this is bad!;
}

void TypeTypeServer::send(Client *client, char const *data, size_t len) {
	if (client->socket->send(data, len) != sf::Socket::Done)
		disconnect(client); // this is bad!;
}

void TypeTypeServer::broadcast(sf::Packet *data) {
	for (auto client : clients)
		send(client, data);
}

void TypeTypeServer::broadcast(char const *data, size_t len) {
	for (auto client : clients)
		send(client, data, len);
}

void TypeTypeServer::broadcast(const std::list<Client*> recp, sf::Packet *data) {
	for (auto client : recp)
		send(client, data);
}

void TypeTypeServer::broadcast_less(const std::list<Client*> less, sf::Packet *data) {
	std::list<Client*> bc = clients;
	for (auto client : less)
		bc.remove(client);
	for (auto client: bc)
		send(client, data);
}

void TypeTypeServer::disconnect(Client *client) {
	client->socket->disconnect();
}

void TypeTypeServer::kill() {
	live = false;
}

int main(int argc, char **argv) {
	TypeTypeServer tts;
	TypeTypeHttp tthttp;

	std::string in;
	std::cin >> in;

	tts.live = false;
	tthttp.live = false;

	return 0;
}
