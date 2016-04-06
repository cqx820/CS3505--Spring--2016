/*
Reference Sources: 
http://www.sourcetricks.com/2011/06/c-tries.html#.VrJEcLIrKUl
https://gist.github.com/jl2/4660503
http://www.sanfoundry.com/cpp-program-implement-trie/
http://www.cplusplus.com/reference/string/string/
Author: Qixiang Chao				
*/
#include "Trie.h"
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>
#include <utility>
using namespace std;

Trie::Trie()
{
    root = new TrieNode();
}

Trie::Trie(const Trie& other)
{
	root = new TrieNode();
	copyConstructor(other.root, root);
}

Trie::~Trie()
{
	destructHelper(root);
}

void Trie::copyConstructor(TrieNode* otherNode, TrieNode* thisNode)
{
	for(unsigned int i = 0; i < 26; i++)
	{
		if(otherNode->getChildren().at(i) != NULL)
		{
			thisNode->getChildren().at(i) = new TrieNode();
			copyConstructor(otherNode->getChildren().at(i), thisNode->getChildren().at(i));
		}
	}
}

void Trie::destructHelper(TrieNode* node)
{
	vector<TrieNode*>::iterator it = (node->getChildren()).begin();
 
    for (; it != (node->getChildren()).end(); ++it)
    {
        if (*it != NULL)
		{
            destructHelper((TrieNode*)(*it));
		}
    }
    delete root;
} 


void Trie::addWord(string s)
{
	TrieNode* current = this->root;
	if(s.length() == 0)
	{
		current->setWordMarker();
		return;
	}
	unsigned int i;
	for(i = 0; i < s.length(); i++)
	{
		TrieNode* child = current->findChild(s[i]);
        if (child != NULL)
        {
            current = child;
        }
        else
        {
            TrieNode* tmp = new TrieNode();
            tmp->setContent(s[i]);
			current->setChild(tmp, s[i]);
            current = tmp;
        }
    }
	current->setWordMarker();
}

Trie& Trie::operator=(const Trie& other)
{
	if(this == &other)
	{
		return *this;
	}
	swap(*root, *other.root);
	return *this;
}

bool Trie::isWord(string s)
{
	if(s.length() == 0)
	{
		return false;
	}
	int index;
	TrieNode* current = root;
	for(char& c : s)
	{
		index = (int) c - 97;
		current = current->getChildren().at(index);
		if(current == NULL)
		{
			return false;
    	}
  	}
  	return current->isWord();
}
	
vector<string> Trie::allWordsWithPrefix(string s)
{
	vector<string> tempList;
	if(s.length() == 0)
	{
		return tempList;
	}
	int index;
	TrieNode* current = root;	
	for(char&c : s)
	{
		index = (int) c - 97;
		current = current->getChildren().at(index);

    	if(current == NULL)
		{
			return vector<string>();
		}
	}

  allWordsWithPrefixRecursive(&tempList, current, s);
  return tempList;	
}

void Trie::allWordsWithPrefixRecursive(vector<string>* list, TrieNode* node, string s)
{
	char c;
	unsigned int i;
	for(i = 0; i < 26; i++)
	{
		c = (char) i + 97;
		TrieNode* tempNode = node->getChildren().at(i);
		if(tempNode != NULL)
		{
			string newString = s;
			newString.push_back(c);
			allWordsWithPrefixRecursive(list, tempNode, newString);
		}
		
	}
	if(node->isWord())
	{
		list->push_back(s);
	}
}
	

bool Trie::searchWord(string s)
{
    TrieNode* current = root;

    while (current != NULL)
    {
        for (unsigned int i = 0; i < s.length(); i++ )
        {
            TrieNode* tmp = current->findChild(s[i]);
            if (tmp == NULL)
			{
                return false;
			}
            current = tmp;
        }

        if (current->isWord())
		{
            return true;
		}
        else
		{
            return false;
    	}
	}

    return false;
}









