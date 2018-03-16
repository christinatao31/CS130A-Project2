#ifndef	AVL_h
#define AVL_h
#include <string>

using namespace std;

struct AvlNode {
  string word;
  AvlNode *left;
  AvlNode *right;
  int height;
  AvlNode(const string & ele, AvlNode *lt, AvlNode *rt, int h = 0)
    : word{ele}, left{lt}, right{rt}, height{h} { }
  AvlNode(string && ele, AvlNode *lt, AvlNode *rt, int h = 0)
    : word{std:move(ele)}, left{lt}, right{rt}, height{h} { }

};

class AVL {

public:
	AVL();
	~AVL();
    void printInorder(AvlNode* node);

  	bool search(AvlNode* node, string word);  //search function
  	
    int height(AvlNode *t) const ;
    void insert(const string & x, AvlNode * & t);
    void balance(AvlNode * & t);
    void rotateWithLeftChild(AvlNode * & k2);
    void doubleWithLeftChild(AvlNode * & k3);
    void rotateWithRightChild(AvlNode * & k2);
    void doubleWithRightChild(AvlNode * & k3);
    
    void remove(const string & x, AvlNode *& t);
  	//Node* getRoot();
  	void sort(AvlNode* node, ofstream& outFile); 				//sort function
    void rangeSearch(AvlNode* node, string startWord, string endWord);
  	int countWords();
  	void destroyTree();

private:
  	AvlNode* root;
  	int countWords(AvlNode* node);
  	void destroyTree(AvlNode* node);

};

#endif