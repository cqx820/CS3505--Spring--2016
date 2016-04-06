/*
Reference Sources: 
http://www.sourcetricks.com/2011/06/c-tries.html#.VrJEcLIrKUl
https://gist.github.com/jl2/4660503
http://www.sanfoundry.com/cpp-program-implement-trie/
http://www.cplusplus.com/reference/string/string/
Author: Qixiang Chao				
*/
#include "TrieNode.h"
#include <string>
#include <vector>
using namespace std;
class Trie
{
    TrieNode* root;
public:
    Trie();
    ~Trie();
	Trie(const Trie& other);
    Trie& operator=(const Trie&);
    void addWord(string s);
    bool isWord(string s);
    vector<string> allWordsWithPrefix(string);
	void allWordsWithPrefixRecursive(vector<string>* list, TrieNode* node, string s);
	void destructHelper(TrieNode* node);
	bool searchWord(string s);
	void copyConstructor(TrieNode* otherNode, TrieNode* thisNode);
};
