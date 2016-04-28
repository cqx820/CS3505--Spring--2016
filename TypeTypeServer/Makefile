CC = g++
CFLAGS = -Wall -std=c++11 -g

INC = inc
SRC = src
PINC = protocol/inc
PSRC = protocol/src
LIB = -lsfml-network -lsfml-system -lmysqlclient -lm -lz

all: TypeTypeServer TypeTypeClient

TypeTypeClient: typetypetest.o typetypepacket.o typetypeprotocol.o
	$(CC) $(CFLAGS) -o TypeTypeClient -I$(INC) $(SRC)/typetypetest.o $(LIB)

typetypetest.o: typetypepacket.o typetypeprotocol.o $(SRC)/typetypetest.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypetest.o -c -I$(INC) $(SRC)/typetypetest.cpp

TypeTypeServer: typetypeserver.o typetypehttp.o typetypedb.o typetypeclient.o typetypepacket.o typetypeprotocol.o typetypeclient.o
	$(CC) $(CFLAGS) -o TypeTypeServer -I$(INC) $(SRC)/typetypeserver.o $(SRC)/typetypehttp.o $(SRC)/typetypedb.o $(SRC)/typetypeprotocol.o $(SRC)/typetypeclient.o $(LIB)

typetypeserver.o: typetypeclient.o $(INC)/typetypeserver.h $(SRC)/typetypeserver.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypeserver.o -c -I$(INC) $(SRC)/typetypeserver.cpp

typetypehttp.o: $(INC)/typetypehttp.h $(SRC)/typetypehttp.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypehttp.o -c -I$(INC) $(SRC)/typetypehttp.cpp

typetypedb.o: $(INC)/typetypedb.h $(SRC)/typetypedb.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypedb.o -c -I$(INC) $(SRC)/typetypedb.cpp

typetypeclient.o: $(INC)/typetypeclient.h $(SRC)/typetypeclient.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypeclient.o -c -I$(INC) $(SRC)/typetypeclient.cpp

typetypepacket.o: $(INC)/typetypepacket.h $(SRC)/typetypepacket.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypepacket.o -c -I$(INC) $(SRC)/typetypepacket.cpp

typetypeprotocol.o: $(INC)/typetypeprotocol.h $(SRC)/typetypeprotocol.cpp
	$(CC) $(CFLAGS) -o $(SRC)/typetypeprotocol.o -c -I$(INC) $(SRC)/typetypeprotocol.cpp

clean:
	rm TypeTypeServer
	rm TypeTypeClient
	rm $(SRC)/*.o
	rm $(INC)/.*.swp
	rm $(SRC)/.*.swp
	rm .*.swp
server:
	./TypeTypeServer

client:
	./TypeTypeClient
