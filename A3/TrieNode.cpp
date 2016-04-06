/*
Reference Sources: 
http://www.sourcetricks.com/2011/06/c-tries.html#.VrJEcLIrKUl
https://gist.github.com/jl2/4660503
http://www.sanfoundry.com/cpp-program-implement-trie/
http://www.cplusplus.com/reference/string/string/
Author: Qixiang Chao				
*/
#include "TrieNode.h"
#include <vector>
#include <cstddef>
using namespace std;

TrieNode::TrieNode()
{
	children = vector <TrieNode*>(26, nullptr);
	is_word = false;
	mContent = ' ';
}

TrieNode::~TrieNode()
{
	for(auto it = children.begin(); it != children.end(); ++it)
	{
		delete(*it);
	}
}

bool TrieNode::isWord()
{
	return is_word;
}

void TrieNode::setWord(bool _is_word)
{
	this->is_word = _is_word;
}

vector <TrieNode*> TrieNode::getChildren()
{
	return this->children;
}

TrieNode* TrieNode::getChild(int c)
{
	TrieNode* child = new TrieNode();
	children[c] = child;
	return child;
}


TrieNode* TrieNode::findChild(char c)
{
	if (children[c - 97] != NULL)
	{
		return children[c - 97];
	}	
	else
	{
		return NULL;
	}
}

void TrieNode::setWordMarker() 
{ 
	is_word = true; 
}

char TrieNode::content() 
{ 
	return mContent; 
}

void TrieNode::setContent(char c) 
{ 
	mContent = c; 
}

void TrieNode::setChild(TrieNode* avi, char c)
{
	children[c - 97] = avi;
}


















