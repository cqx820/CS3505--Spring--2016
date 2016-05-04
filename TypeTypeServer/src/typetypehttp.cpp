#include "typetypehttp.h"
#include "typetypedb.h"

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
					char in[1024];
					std::size_t len;
					if (client.receive(in, 1024, len) == sf::Socket::Done) {
						std::string message = html();
						client.send(message.c_str(), message.length());
						client.disconnect();
					}
				}				
			}
		}
	}
}

std::string TypeTypeHttp::html() {
	TypeTypeDB db;
	std::string m = "HTTP/1.1 200 OK\r\nConnection: close\r\nContent - Type: text / html; charset = UTF - 8\r\n\r\n";
	m += "<html><head>";
	m += "<title>TypeTypeRevolution</title></head>";
	m += "<body>";
	m += "<h1>TypeTypeRevolution Statistics</h1>";
	m += "<table><thead>";
	m += "<tr><th>Material</th><th>Nickname</th><th></th></tr></thead>";
	m += db.db_stat();
	m += "</table>";
	m += "</body></html>";
	return m;
}
