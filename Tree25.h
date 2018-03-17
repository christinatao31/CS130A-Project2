#ifndef tree25_h
#define tree25_h

#include <string>

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
  
 private:
  Node* root;
  int height;
  void initNode(Node*& node);
  void insert(Node*& node, string word);
  bool nodeContainsWord(Node* node, string word);
  void insertExistingWord(Node* node, string word);
  bool isFiveNode(Node* node);
  bool isRoot(Node* node);
  bool isLeaf(Node* node);
  void pushToParent(Node*& node, Node*& parent, Word* data, Node* left, Node* right);
  void nodeInsert(Node*& node, string word);
  int getWordCount(Word* word) { return word->count; }
  void incrementWordCount(Word*& word) { word->count++; }

 
};

#endif
