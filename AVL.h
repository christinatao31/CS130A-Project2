#ifndef	AVL_h
#define AVL_h
#include <string>

using namespace std;

struct AvlNode {
  Comparable element;
  AvlNode *left;
  AvlNode *right;
  int height;
  AvlNode(const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0)
    : element{ele}, left{lt}, right{rt}, heigh{h} { }
  AvlNode(Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
    : element{std:move(ele)}, left{lt}, right{rt}, height{h} { }

};

class AVL {

public:
	AVL();
	~AVL();
  	void printInorder();
  	bool search(string word);  //search function
  	int height(AvlNode *t);
    void insert(const Comparable & x, AvlNode * & t);
    void balance(AvlNode * & t);
    void rotateWithLeftChild(AvlNode * & k2);
    void doubleWithLeftChild(AvlNode * & k3);
    void rotateWithRightChild(AvlNode * & k2);
    void doubleWithRightChild(AvlNode * & k3);
    void remove(const Comparable & x, AvlNode *& t) 
  	Node* getRoot();
  	void sort(); 				//sort function
  	void rangeSearch(string startWord, string endWord); //rangeSearch function 
  	int countWords();
  	void destroyTree();

private:
  	Node* root;
  	void printInorder(AvlNode* node);
  	void sort(AvlNode* node, ofstream& outFile);
  	void rangeSearch(AvlNode* node, string startWord, string endWord);
  	int countWords(AvlNode* node);
  	void destroyTree(AvlNode* node);

};

#endif