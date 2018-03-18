#ifndef	avl_h
#define avl_h
#include <string>

using namespace std;

class AVL {

 public:
  AVL();
  ~AVL();
  struct AVLNode* newNode(string key);
  int max(int a, int b);
  int height(struct AVLNode *N);
  struct AVLNode *rightRotate(struct AVLNode *y);
  struct AVLNode *leftRotate(struct AVLNode *x);
  int getBalance(struct AVLNode *N);
  struct AVLNode* insert(struct AVLNode* node, string key);
  void inOrder(struct AVLNode *root);

  bool search(struct AVLNode* node, string key);

  struct AVLNode* minValueNode(struct AVLNode* node);
  struct AVLNode* deleteNode(struct AVLNode* root, string key);

  void sort(struct AVLNode* root);
  void sort(struct AVLNode* root, ofstream& outFile);

  void rangeSearch(struct AVLNode* root, string startKey, string endKey);

};


#endif
