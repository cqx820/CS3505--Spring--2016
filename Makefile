main.o : main.cpp
	g++ -c main.cpp

test : main.o
	g++ -o test main.o
