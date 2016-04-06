CXX ?= g++
CFLAGS = -g -Wall -std=c++11
IDIR=-I ~/gtest/include -ITrie/
LIBS= -lgtest -lgtest_main -lpthread
LIBLOC= -L ~/gtest/

Test : Test.o Trie.o
	$(CXX) $(CFLAGS) -o Test Test.o Trie.o $(LIBLOC) $(LIBS)
Test.o : Test.cpp
	$(CXX) -c $(CFLAGS) Test.cpp $(IDIR)

Trie.o : Trie/Trie.cpp
	$(CXX) -c $(CFLAGS) Trie/Trie.cpp $(IDIR)

.PHONY: test clean

clean :
	\rm -f *.o Test

test :
	./Test
