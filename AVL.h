#ifndef	AVL_h
#define AVL_h
#include <string>

using namespace std;

struct NodeAVL{
	NodeAVL *left, *right;
	string word;
	int wordCount;
	int height;

	NodeAVL(string word) {
		left = NULL;
		right = NULL;
		this->word = word;
		wordCount = 1;
		height = 0;
	}
};

class AVL {

public:
	AVL();
	~AVL();
  	void printInorder();
  	bool search(string word);  //search function
  	void insert(string word);	//insert function
  	NodeAVL* getRoot();
  	void deleteWord(string word);	//delete function
  	void sort(); 				//sort function
  	void rangeSearch(string startWord, string endWord); //rangeSearch function 
  	int countWords();
  	void destroyTree();

private:
  	NodeAVL* root;
  	void printInorder(NodeAVL* node);
  	bool search(NodeAVL* node, string word);
  	int height(NodeAVL* node);
  	int getDiff(NodeAVL* node);
  	void leftRotate(NodeAVL*& node);
  	void rightRotate(NodeAVL*& node);
  	void insert(NodeAVL*& node, string word);
	void balance(NodeAVL*& node);
  	void deleteWord(NodeAVL*& node, string word);
  	void sort(NodeAVL* node, ofstream& outFile);
  	void rangeSearch(NodeAVL* node, string startWord, string endWord);
  	int countWords(NodeAVL* node);
  	void destroyTree(NodeAVL* node);

};

#endif
