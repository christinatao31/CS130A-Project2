#ifndef tree25_h
#define tree25_h

#include <string>
#include <fstream>

using namespace std;

struct Word {
  string word;
  int count;
};

struct Node {
  Word *data1, *data2, *data3, *data4;
  Node *child1, *child2, *child3, *child4, *child5, *parent;

  Node() {
    data1 = data2 = data3 = data4 = NULL;
    child1 = child2 = child3 = child4 = child5 = parent = NULL;
  }
  
};

class Tree25 {

 public:
  // constructor
  Tree25();

  // destructor
  ~Tree25();

  bool search(string word);
  void insert(string word);
  void remove(string word);
  void sort();
  void rangeSearch(string startWord, string endWord);  
  void printInorder();
  Node* getRoot() { return root; }
  
 private:
  Node* root;
  int height;
  bool search(Node* node, string word);
  void insert(Node*& node, string word);
  bool nodeContainsWord(Node* node, string word);
  void insertExistingWord(Node* node, string word);
  bool isFiveNode(Node* node);
  bool isRoot(Node* node);
  bool isLeaf(Node* node);
  void pushToParent(Node*& node, Node*& parent, Word* data, Node* left, Node* right);
  void nodeInsert(Node*& node, string word);
  void remove(Node*& node, string word);
  void removeFromLeaf(Node*& node, string word);
  bool containsTwoKeys(Node* node);
  bool containsTwoWords(Node* node);
  bool containsOneKey(Node* node);
  void merge(Node*& node, Node*& leftChild, Node*& rightChild, Word* wordToDelete);
  void rotateCC(Node*& node, Node*& child, Node*& rightSibling);
  void rotateCW(Node*& node, Node*& child, Node*& leftSibling);
  void sort(Node* node, ofstream& outFile);
  void rangeSearch(Node* node, string startWord, string endWord);
  void printInorder(Node* node);
  int getWordCount(Word* word) { return word->count; }
  void incrementWordCount(Word*& word) { word->count++; }
  void decrementWordCount(Word*& word) { word->count--; }
  
};

#endif
