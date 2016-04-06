CC = g++
CFLAGS = -Wall -std=c++11 

TrieTest: TrieTest.o Trie.o TrieNode.o
	$(CC) $(CFLAGS) -o TrieTest TrieTest.o Trie.o TrieNode.o
	
TrieTest.o: TrieTest.cpp Trie.h TrieNode.h
	$(CC) $(CFLAGS) -c TrieTest.cpp
	
Trie.o: Trie.cpp Trie.h
	$(CC) $(CFLAGS) -c Trie.cpp			

TrieNode.o: TrieNode.cpp TrieNode.h
	$(CC) $(CFLAGS) -c TrieNode.cpp		
	
clean:
	rm -f TrieTest *.o

test:
	./TrieTest "dictionary.txt" "query.txt"
