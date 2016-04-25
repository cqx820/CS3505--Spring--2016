/*
Reference Sources: 
http://www.sourcetricks.com/2011/06/c-tries.html#.VrJEcLIrKUl
https://gist.github.com/jl2/4660503
http://www.sanfoundry.com/cpp-program-implement-trie/
http://www.cplusplus.com/reference/string/string/
Author: Qixiang Chao				
*/
#include <vector>
#include <iostream>
using namespace std;

class TrieNode
{
    vector<TrieNode*> children;
    
	char mContent;
public:
    TrieNode();
	~TrieNode();
	bool is_word;
	vector<TrieNode*> getChildren();
	bool isWord();
	void setWord(bool _is_word);
	TrieNode* getChild(int index);
    char content();
    void setContent(char c);
    void setWordMarker();
    TrieNode* findChild(char c);
	int getIndex(char c);
	TrieNode* getNode(char c);
	void setChild(TrieNode* avi, char c);
};
