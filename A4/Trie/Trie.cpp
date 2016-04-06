/*=========================================================================
 *
 * Author:Yiliang Shi
 * Description: Implementation of trie class that accepts lower cased words
 * Date:2/2/16
 *
 * ========================================================================*/
#include <string>
#include <vector>
#include "Trie.h"

using namespace std;

Trie::Trie(){
    newCount++;
    root =new Node; 
}

Trie::~Trie(){
    FreeNodes(root);
   }

Trie::Node::Node(){
	refCount++;
}

Trie::Node::~Node(){
	refCount--;
}

void Trie::FreeNodes(Node* node){
    for(int i=0;i<26;i++){
        if(node->branches[i]!=nullptr){
            FreeNodes(node->branches[i]);
        }
    }

    if(node!=nullptr){
        delete node;
        deleteCount++;
    }

}

Trie::Trie(const Trie& other){
    newCount++;
    root=new Node;
    CopyNode(other.root,root);
}

void Trie::CopyNode(Node* other, Node* node){
    for(int i=0;i<26;i++){
        if(other->endFlag){
            node->endFlag=true;
        }
        if(other->branches[i]!=nullptr){
            newCount++;
            node->branches[i]=new Node;
            CopyNode(other->branches[i],node->branches[i]);
        }
    }
}
Trie& Trie::operator=(Trie other){
    swap(root,other.root);
    return *this;
}

void Trie::addWord(string word){

    Node *currentNode=root;
    for(unsigned int i=0;i<word.length();i++){    
        //Convert char to int starting from 0 which is equal to 'a'
        int index = word[i]-'a';
        //If letter/branch exist, travel down the tree
        if(currentNode->branches[index]!=nullptr){
            currentNode=currentNode->branches[index];
        }
        //If letter/branch doesn't exist, create new branch,then go to new branch
        else{
            newCount++;
            Node *newNode = new Node;
            currentNode->branches[index]=newNode;
            currentNode=newNode;
        }
    }
    //Set end of word
    currentNode->endFlag=true;
}

bool Trie::isWord(string word){
    Node *currentNode=root;
    for(unsigned int i=0;i<word.length();i++){
         //Convert char to int starting from 0 which is equal to a
        int index = word[i]-97;
        //If letter/branch exist, travel down the tree
        if(currentNode->branches[index]!=nullptr){
            currentNode=currentNode->branches[index];
        }
        else
            return false;

    }
    //Check if its an end of word
    if(currentNode->endFlag)
        return true;
    return false;
}

vector<string> Trie::allWordsWithPrefix(string prefix){
    vector<string> result;
    Node *currentNode=root;
    //iterates to the current node
    for(unsigned int i=0;i<prefix.length();i++){
         //Convert char to int starting from 0 which is equal to a
        int index = prefix[i]-97;
        //If letter/branch exist, travel down the tree
        if(currentNode->branches[index]!=nullptr){
            currentNode=currentNode->branches[index];
        }

    }
	getWords(currentNode,prefix,result);
    return result;
}

void Trie::getWords(Node* node, string& prefix,vector<string>& result){
//if prefix is a word, add it to result it
   			if(node->endFlag){
        		result.push_back(prefix);
			}
    for(int i=0;i<26;i++){
        char element = 'a'+i;
        if(node->branches[i]!=nullptr){

            prefix.push_back(element);
			
            getWords(node->branches[i],prefix,result);
            prefix.pop_back();
        }       
    }

}
