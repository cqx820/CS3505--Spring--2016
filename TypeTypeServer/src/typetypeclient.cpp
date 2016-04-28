#include "typetypeclient.h"

Client::Client() {

}

Client::~Client() {
	delete socket;

	sf::Packet *temp;
	while (obuf.empty() == false) {
		temp = obuf.front();
		delete temp;
		obuf.pop();
	}

	while (ibuf.empty() == false) {
		temp = ibuf.front();
		delete temp;
		obuf.pop();
	}
}
