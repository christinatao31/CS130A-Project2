#ifndef node_h
#define node_h

class Node {

 public:
  // constructor
  Node(string word);

  // destructor
  ~Node();

  Node* getNext();
  Node* getLeft();
  Node* getRight();
  string getWord();
  int getWordCount();
  int getIndex();
  void incrementCount();
  
 private:
  Node* next;
  Node* left;
  Node* right;
  string word;
  int wordCount, index;
  
};

#endif
