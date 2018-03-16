#ifndef tree25_h
#define tree25_h

#include <string>

using namespace std;

struct Node {
  string data1, data2, data3, data4;
  Node *child1, *child2, *child3, *child4, *child5, *parent;

  Node() {
    data1 = data2 = data3 = data4 = "";
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
  void initNode(struct Node*& node);
  void insert(struct Node*& node, string word);
  bool isFiveNode(struct Node* node);
  bool nodeIsEmpty(struct Node* node);
  bool isLeaf(struct Node* node);
  void nodeInsert(struct Node* node, string word);
  
};

#endif