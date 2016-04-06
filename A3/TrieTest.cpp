/*
Author: Qixiang Chao
*/
#include <iostream>
#include "Trie.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

vector<string> readWordsFromFile(string fileName);

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		cout << "Please enter valide input" << endl;
		return EXIT_FAILURE;
	}
	Trie* trie = new Trie();
	string dictionary = argv[1];
	string query = argv[2];
	vector<string> dictionaryList = readWordsFromFile(dictionary);
	vector<string> queryList = readWordsFromFile(query);
	if(dictionaryList.size() == 0)
	{
		cout << "Empty dictionary file, try again" << endl;
		return EXIT_FAILURE;
	}
	if(queryList.size() == 0)
	{
		cout << "Empty query file, try again" << endl;
		return EXIT_FAILURE;
	}
	for(unsigned int i = 0; i < dictionaryList.size(); i++)
	{
		trie->addWord(dictionaryList.at(i));
	}
	for(unsigned int i = 0; i < queryList.size(); i++)
	{
		if(trie->isWord(queryList.at(i)))
		{
			cout << "Word is found" << endl;
		}
		else
		{
			cout << "Word not found, did you mean:   " << endl;
			vector<string> otherWords = trie->allWordsWithPrefix(queryList.at(i));
			for(unsigned int j = 0; j < otherWords.size(); j++)
			{
				cout << otherWords.at(j) << "   " << endl;
			}
		}
	}
	return 0;
}

vector<string> readWordsFromFile(string fileName)
{
	vector<string> returnList;
	ifstream file(fileName);
	string input;
	while(getline(file, input))
	{
		returnList.push_back(input);
	}
	file.close();
	return returnList;
}

