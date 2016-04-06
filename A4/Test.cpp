/*
* Author: Yiliang Shi, Qixiang Chao
* reference for friend testing: http://stackoverflow.com/questions/14186245/unit-testing-c-how-to-test-private-members
*/
#include "gtest/gtest.h"
#include "Trie.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
int refCount = 0;
int newCount=0;
int deleteCount=0;
/* 
 * Helper method to read lists of words from txt file for easy testing
 */
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
/*
 * Tests the construction of a Trie. After the trie is constructed, there should be 1 node in existance
 */
TEST(TrieConstruction, emptyTrieNode){
	Trie trie;
	EXPECT_EQ(1,refCount);
}

/*
 * Tests that the empty string is a word if the trie if its added to the file
 */
TEST(TrieIsWord,emptyStringTrie){
    Trie trie;
    ASSERT_FALSE(trie.isWord(""));
}

/*
 * Tests that the right number of nodes are added when two words with the same prefix are added to a trie
 */
TEST(TrieAdd, nodeConstruction){
	Trie trie;
	trie.addWord("a");
	EXPECT_EQ(2, refCount);
	trie.addWord("all");
	EXPECT_EQ(4,refCount);
}

/* 
 * Checks that equal number of nodes are created and destructed when an empty Trie moves out of scope
 */
TEST(TrieDestruction, nodeRemoval){
	{
		Trie trie;
		EXPECT_EQ(1,refCount);
	}
	EXPECT_EQ(0,refCount);
}

/*
 * Explicited count the number of adds and deletes to ensure that there are no memory leaks after content is added to the trie
 */
TEST(MemoryTest,newDeleteNum){
    {
        Trie trie;
        trie.addWord("ddfsfsd");
        trie.addWord("dsff");
    }
    ASSERT_EQ(newCount,deleteCount);

}

/*
 * Checks that the destructor deletes all nodes that should be in a tree
 */
TEST(TrieDestruction, nestedNodeRemoval){
	{	
		Trie trie;
		trie.addWord("all");
		trie.addWord("alter");
		trie.addWord("ball");
		trie.addWord("altan");
		EXPECT_EQ(13,refCount);
	}
	EXPECT_EQ(0,refCount);
}
/*
 * White box test that checks that all alphabets are added to the right place in the Node's array
 */
TEST(AddwordTest,singleLetter){
	Trie trie;
	for(int i=0;i<26;i++)
	{
	    string s;
	    s.push_back((char)('a'+i));
		trie.addWord(s);
		ASSERT_NE(nullptr,trie.root->branches[i]);
		ASSERT_TRUE(trie.root->branches[i]->endFlag);
		for(int j=(int)i+1;j<26;j++)
			ASSERT_EQ(nullptr,trie.root->branches[j]);
	}	
}

/*
 * White box test that confirms the location of each node added to the trie by iterating through the tree
 */
TEST(AddwordTest,multiwordBranch){
	Trie trie;
    Trie::Node* node;
    Trie::Node* node2;

	trie.addWord("hall");
	trie.addWord("happy");
	
	//Test ha
	node=trie.root;
	ASSERT_NE(nullptr,node->branches['h'-'a']);
	node=node->branches['h'-'a'];
	ASSERT_NE(nullptr,node->branches['a'-'a']);
	node=node->branches['a'-'a'];
	//Test l and p
	ASSERT_NE(nullptr,node->branches['l'-'a']);
	ASSERT_NE(nullptr,node->branches['p'-'a']);
	//Test hall
	node2=node->branches['p'-'a'];
	node=node->branches['l'-'a'];
	ASSERT_NE(nullptr,node->branches['l'-'a']);
	node=node->branches['l'-'a'];
	ASSERT_TRUE(node->endFlag);

	//Test happy
	ASSERT_NE(nullptr,node2->branches['p'-'a']);
	node2=node2->branches['p'-'a'];	
	ASSERT_NE(nullptr,node2->branches['y'-'a']);
	node2=node2->branches['y'-'a'];
	ASSERT_TRUE(node2->endFlag);
	
}

/*
 * White box test that checks that the node array is not affected when adding an empty string
 */
TEST(AddwordTest,addEmptyString){
	Trie trie;
	trie.addWord("");
	ASSERT_TRUE(trie.root->endFlag);
	for(int i=0;i<26;i++){
		ASSERT_EQ(nullptr, trie.root->branches[i]);
	}
}

/*
 * Tests that an empty trie does not contains words
 */
TEST(isWordTest, emptyStringTest)
{
	Trie trie;
	ASSERT_FALSE(trie.isWord("abc"));
}

/*
 * Stress test that addword and isWord works by adding and looking for all words in a dictionary
 */
TEST(isWordTest, isWordTest1)
{
	Trie trie;
	vector<string> dicList = readWordsFromFile("dictionary.txt");
	for(string it : dicList)
	{
		trie.addWord(it);
	}
	for(string it : dicList)
	{
		ASSERT_TRUE(trie.isWord(it));
	}
}

/*
 * Checks that is word does not return true for prefix that has not being added to the trie
 */
TEST(isWordTest, isWordTest2)
{
	Trie trie;
	trie.addWord("hello");
	ASSERT_FALSE(trie.isWord("hell"));
}

/*
 * Test the functionality of allWordWithPrefix by checking if it returns all words in the trie when an empty string is passed into the method. It also tests if the method returns the right list the prefix if the prefix is a word and when it isn't.  
 */
TEST(allWordWithPrefixTest, test1)
{	
	Trie trie;
	vector<string> fileList = readWordsFromFile("testFile.txt");
	for(string it : fileList)
	{
		trie.addWord(it);
	}
	vector<string> tmp = trie.allWordsWithPrefix("");
	sort(fileList.begin(), fileList.end());
	sort(tmp.begin(), tmp.end());
	ASSERT_TRUE(fileList.size() == tmp.size());
	for(unsigned int i = 0; i < fileList.size(); i++)
	{
		ASSERT_TRUE(fileList.at(i) == tmp.at(i));
	}
    tmp = trie.allWordsWithPrefix("aban");
	sort(tmp.begin(), tmp.end());
	ASSERT_EQ(10,tmp.size());

	for(unsigned int i = 0; i < 10; i++)
	{
		ASSERT_TRUE(fileList.at(i) == tmp.at(i));
	}

	tmp = trie.allWordsWithPrefix("abandon");
	sort(tmp.begin(), tmp.end());
	ASSERT_EQ(10,tmp.size());

	for(unsigned int i = 0; i < 10; i++)
	{
		ASSERT_TRUE(fileList.at(i) == tmp.at(i));
	}
}

/*
 * Tests the copy constructor by constructing a tree, copying it and checking if the content has being copied with isWord. Stress test version
 */
TEST(copyConstructorTest, content){
	Trie trie;
	vector<string> dicList = readWordsFromFile("dictionary.txt");
	for(string it : dicList)
	{
		trie.addWord(it);
	}
	Trie trie2(trie);
	for(string it : dicList)
	{
		ASSERT_TRUE(trie2.isWord(it));
	}
}

/*
 * Tests if single node is copied by the copy constructor. Checks that a new Trie is created
 * */
TEST(copyConstructorTest, singleNode){
    Trie trie;
    Trie* trieRef=&trie;
    trie.addWord("a");
    Trie trie2(trie);
    Trie* trieRef2=&trie2;
    ASSERT_NE(trieRef, trieRef2);
}

/* 
 * Test if a single node is copied by checking that a new root is created
 */
TEST(copyConstructorTest, singleNodeRoot){
    Trie trie;
    trie.addWord("a");
    Trie::Node* trieRef=trie.root;
    int initCount= newCount;
    int delCount=deleteCount;

    Trie trie2(trie);
    Trie::Node* trieRef2=trie2.root;
    ASSERT_NE(trieRef, trieRef2);
    ASSERT_NE((newCount-initCount),(deleteCount-delCount));
    ASSERT_TRUE((newCount-initCount)==2+(deleteCount-delCount));
}
/*
 * Test if a single node is correctly copied by verifying the content of its root
 */
TEST(copyConstructorTest, singleNodeRootContent){
    Trie trie;
    trie.addWord("a");

    Trie trie2(trie);
    Trie::Node* trieRef2=trie2.root;
    ASSERT_NE(nullptr, trieRef2->branches[0]);
}

/*
 * Checks if the assignment operator is working by constructing 2 trees, adding content to the first, and assigning it to the 2nd. Checks if the 2nd trie has the content of the frist. 
 */
TEST(assignmentOperatorTest,content){
	Trie trie;
	vector<string> dicList = readWordsFromFile("dictionary.txt");
	for(string it : dicList)
	{
		trie.addWord(it);
	}
	Trie trie2;
	trie2=trie;
	for(string it : dicList)
	{
		ASSERT_TRUE(trie2.isWord(it));
	}
}

/*
 * Tests that duplicated words cannot be added to the trie. 
 */
TEST(addWordTest,duplicates){
    Trie trie;
    trie.addWord("hello");
    trie.addWord("hello");
    vector<string> result = trie.allWordsWithPrefix("");
    ASSERT_EQ(1,result.size());
}

/*
 * runs all tests
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
