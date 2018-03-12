#ifndef 25tree_h
#define 25tree_h

struct Node {
  string data1, data2, data3, data4;
  Node *child1, *child2, *child3, *child4, *child5, *parent;

  Node() {
    data1 = data2 = data3 = data4 = "";
    child1 = child2 = child3 = child4 = child5 = parent = NULL;
  }
  
};

class 25Tree {

 public:
  // constructor
  25Tree();

  // destructor
  ~25Tree();

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

#endif 25tree_h
