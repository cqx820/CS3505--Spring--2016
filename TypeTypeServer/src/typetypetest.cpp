#include "typetypeserver.h"
#include "typetypeprotocol.h"

#include <SFML/Network.hpp>
#include <iostream>

class TypeTypeClient {
  sf::TcpSocket socket;
	bool live = true;

public:
  TypeTypeClient();
  ~TypeTypeClient();

  void connect();
  void work();
};

TypeTypeClient::TypeTypeClient() {
  connect();
}

TypeTypeClient::~TypeTypeClient() {
}

void TypeTypeClient::connect() {
  if (socket.connect("127.0.0.1", PORT) != sf::Socket::Done)
    std::cout << "Failed to connect to localhost:" << PORT << std::endl;
  else {
    std::cout << "Connected localhost:" << PORT << std::endl;
    work();
  }
}

void TypeTypeClient::work() {
	client_register cr;
	cr.nick = "foo";
	cr.name = "ross";
	cr.email = "ross@spam.im";
	cr.pass = "bar";
	sf::Packet rp;
	rp << cr;

	client_login cl;
	cl.nick = "foo";
	cl.pass = "bar";
	sf::Packet lp;
	lp << cl;

	socket.send(rp);
	
	std::string foo;
	std::cin >> foo;

	std::cout << foo;
}

int main(int cc, char **argv) {
	TypeTypeClient c;
}
