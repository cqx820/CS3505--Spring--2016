/*
 * Author: Yiliang Shi
 * Description: A trie class useful for retrieving dictionary words
 * Date:2/2/16
 */

#ifndef TRIE_H
#define TRIE_H
#include <string>
#include <vector>
#include "gtest/gtest_prod.h"

extern int refCount;
extern int newCount;
extern int deleteCount;

class Trie{
    private:
        class Node{
            public:
            Node();
            ~Node();
            Node *branches[26]={nullptr};
            bool endFlag=false;
        };
        FRIEND_TEST(AddwordTest,multiwordBranch); 
        FRIEND_TEST(AddwordTest,singleLetter);
        FRIEND_TEST(AddwordTest,addEmptyString);
        FRIEND_TEST(copyConstructorTest, singleNodeRoot);
        FRIEND_TEST(copyConstructorTest, singleNodeRootContent);
        Node *root;
        void FreeNodes(Node* n);
        void CopyNode(Node* other, Node* node);
        void getWords(Node* node, std::string& prefix, std::vector<std::string>& result);
        
        

    public:
        Trie();
        ~Trie();
        Trie(const Trie& other);
        Trie& operator=(Trie other);

        void addWord(std::string word);
        bool isWord(std::string word);
        std::vector<std::string> allWordsWithPrefix(std::string prefix);

};


#endif
