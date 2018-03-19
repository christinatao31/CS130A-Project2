#include "Tree25.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// constructor
Tree25::Tree25() {
  root = NULL;
}

// destructor
Tree25::~Tree25() {

}

bool Tree25::search(string word) {
  cout << "search: " << word << endl;
  return search(root, word);
}

bool Tree25::search(Node* node, string word) {
  if (node == NULL) {
    cout << word << " is not in the tree" << endl;
    return false;
  }

  if (nodeContainsWord(node, word)) {
    cout << word << " is in the tree" << endl;
    return true;
  }
  
  if (node->data1 != NULL && word < node->data1->word) {
    cout << "descend into child1" << endl;
    return search(node->child1, word);
  }
  else if (word > node->data1->word && (node->data2 == NULL || word < node->data2->word)) {
    cout << "descend into child2" << endl;
    return search(node->child2, word);
  }
  else if (word > node->data2->word && (node->data3 == NULL || word < node->data3->word)) {
    cout << "descend into child3" << endl;
    return search(node->child3, word);
  }
  else if (word > node->data3->word && (node->data4 == NULL || word < node->data4->word)) {
    cout << "descend into child4" << endl;
    return search(node->child4, word);
  }
  else {
    cout << "descend into child5" << endl;
    return search(node->child5, word);
  }

  cout << word << " is not in the tree" << endl;
  return false;
    
}

void Tree25::insert(string word) {
  cout << "insert " << word << endl;
  insert(root, word);
  //  printInorder();
  cout << "insert " << word << " finished" << endl << endl;
}

void Tree25::insert(Node*& node, string word) {
  if (node == NULL) {
    cout << "node is NULL. create a new node and add " << word << endl;
    node = new Node;
    node->data1 = new Word;
    node->data1->word = word;
    node->data1->count = 1;
    return;
  }

  if (nodeContainsWord(node, word)) {
    cout << word << " already exists. increment count" << endl;
    insertExistingWord(node, word);
    return;
  }
  
  // If the current node is a 5-node:
  if (isFiveNode(node)) {
    cout << "node is a 5-node" << endl;
    
    // Save the middle value, which will be data2
    Word* mid = new Word;
    mid->word = node->data2->word;
    mid->count = node->data2->count;
    cout << "mid is " << mid->word << "(" << mid->count << ")" << endl;

    Node* leftChild = new Node;
    leftChild->data1 = new Word;
    leftChild->data1->word = node->data1->word;
    leftChild->data1->count = node->data1->count;
    cout << "left child is " << leftChild->data1->word << "(" << leftChild->data1->count << ")" << endl;
    leftChild->child1 = new Node;
    leftChild->child1 = node->child1;
    if (leftChild->child1 != NULL)
      leftChild->child1->parent = leftChild;
    leftChild->child2 = new Node;
    leftChild->child2 = node->child2;
    if (leftChild->child2 != NULL)
      leftChild->child2->parent = leftChild;
    Node* rightChild = new Node;
    rightChild->data1 = new Word;
    rightChild->data1->word = node->data3->word;
    rightChild->data1->count = node->data3->count;
    rightChild->data2 = new Word;
    rightChild->data2->word = node->data4->word;
    rightChild->data2->count = node->data4->count;
    cout << "right child is " << rightChild->data1->word << "(" << rightChild->data1->count << "), " <<
      rightChild->data2->word << "(" << rightChild->data2->count << ")" << endl;
    rightChild->child1 = new Node;
    rightChild->child1 = node->child3;
    if (rightChild->child1 != NULL)
      rightChild->child1->parent = rightChild;
    rightChild->child2 = new Node;
    rightChild->child2 = node->child4;
    if (rightChild->child2 != NULL)
      rightChild->child2->parent = rightChild;
    rightChild->child3 = new Node;
    rightChild->child3 = node->child5;
    if (rightChild->child3 != NULL)
      rightChild->child3->parent = rightChild;
    
    // Insert the word into the corresponding left or right child
    if (word < mid->word) {
      cout << "insert in left child" << endl;
      insert(leftChild, word);
      // cout << "left child is " << leftChild->data1->word << "(" << leftChild->data1->count << "), " <<
      //   leftChild->data2->word << "(" << leftChild->data2->count << ")" << endl;
    }
    else if (word > mid->word) {
      cout << "insert in right child" << endl;
      insert(rightChild, word);
    }
    
    // If the node is the root, the saved middle value becomes the new root
    // Ascend into the root and set child1 and child2 to be the left and right child, respectively
    if (isRoot(node)) {
      cout << "node is the root" << endl;
      Node* newRoot = new Node;
      // newRoot->data1 = new Word;
      // newRoot->data1->word = mid->word;
      // newRoot->data1->count = mid->count;
      newRoot->data1 = mid;
      newRoot->child1 = leftChild;
      newRoot->child2 = rightChild;
      // Set the parent of child1 and child2 equal to the new root
      newRoot->child1->parent = newRoot;
      newRoot->child2->parent = newRoot;
      root = newRoot;
      node = root;
      cout << "new root is " << root->data1->word << endl;
    }
    
    // Otherwise, push the middle value up into the parent node
    // Reorganize the children, adding in the new left and right children
    else {
      cout << "node is not the root" << endl;
      Node* parent = node->parent;
      cout << "parent data1 = " << parent->data1->word << endl;
      if (mid->word < parent->data1->word) {
	parent->data4 = parent->data3;
	parent->data3 = parent->data2;
	parent->data2 = parent->data1;
	parent->data1 = mid;
	parent->child5 = new Node;
	parent->child5 = parent->child4;
	if (parent->child5 != NULL) {
	  parent->child5->parent = parent;
	  cout << "set parent of child5" << endl;
	}
	parent->child4 = parent->child3;
	if (parent->child4 != NULL) {
	  parent->child4->parent = parent;
	  cout << "set parent of child4" << endl;
	}
	parent->child3 = parent->child2;
	if (parent->child3 != NULL) {
	  parent->child3->parent = parent;
	  cout << "set parent of child3" << endl;
	}
	parent->child2 = rightChild;
	parent->child1 = leftChild;
	parent->child2->parent = parent;
	parent->child1->parent = parent;
	cout << "pushed mid to parent data1" << endl;
      }
      else if (mid->word > parent->data1->word && (parent->data2 == NULL || mid->word < parent->data2->word)) {
	parent->data4 = parent->data3;
	parent->data3 = parent->data2;
	parent->data2 = mid;
	parent->child5 = parent->child4;
	if (parent->child5 != NULL) {
	  parent->child5->parent = parent;
	  cout << "set parent of child5" << endl;
	}
	parent->child4 = parent->child3;
	if (parent->child4 != NULL) {
	  parent->child4->parent = parent;
	  cout << "set parent of child4" << endl;
	}
	parent->child3 = rightChild;
	parent->child2 = leftChild;
	parent->child3->parent = parent;
	parent->child2->parent = parent;
	cout << "pushed mid to parent data2" << endl;
      }
      else if (mid->word > parent->data2->word && (parent->data3 == NULL || mid->word < parent->data3->word)) {
	parent->data4 = parent->data3;
	parent->data3 = mid;
	parent->child5 = parent->child4;
	if (parent->child5 != NULL) {
	  parent->child5->parent = parent;
	  cout << "set parent of chid5" << endl;
	}
	parent->child4 = rightChild;
	parent->child3 = leftChild;
	parent->child4->parent = parent;
	parent->child3->parent = parent;
	cout << "pushed mid to parent data3" << endl;
      }
      else {
	cout << "parent data3 = " << parent->data3->word << endl;
	parent->data4 = mid;
	parent->child5 = rightChild;
	parent->child4 = leftChild;
	parent->child5->parent = parent;
	parent->child4->parent = parent;
	cout << "pushed mid to parent data4" << endl;
      }
    }
    
  }
  else {
    // If the node is a leaf, insert the value into the node
    if (isLeaf(node)) {
      cout << "node is a leaf" << endl;
      insertIntoLeaf(node, word);
      return;
    }

    // Otherwise, find the child whose interval contains the value to be inserted
    // Recursively call insert on that child
    if (node->data1 != NULL && word < node->data1->word) {
      cout << "descend into child1" << endl;
      insert(node->child1, word);
    }
    else if (word > node->data1->word && (node->data2 == NULL || word < node->data2->word)) {
      cout << "descend into child2" << endl;
      insert(node->child2, word);
    }
    else if (word > node->data2->word && (node->data3 == NULL || word < node->data3->word)) {
      cout << "descend into child3" << endl;
      insert(node->child3, word);
    }
    else if (word > node->data3->word && (node->data4 == NULL || word < node->data4->word)) {
      cout << "descend into child4" << endl;
      insert(node->child4, word);
    }
    else {
      cout << "descend into child5" << endl;
      insert(node->child5, word);
    }
  }
}

void Tree25::remove(string word) {
  remove(root, word);
}

void Tree25::remove(Node*& node, string word) {
  if (nodeContainsWord(node, word)) {
    // If the element is in the node and the node is a leaf containing at elast 2 keys, just
    // remove it from the node
    if (isLeaf(node) && containsTwoKeys(node)) {
      cout << "word is in a leaf with at least two keys" << endl;
      removeFromLeaf(node, word);
    }
    else if (!isLeaf(node)) {
      cout << "word is in an internal node" << endl;
      // If the element's left child has at least 2 keys, replace the element with its predecessor
      // p and then recursively delete p

      // If the element's right child has at least 2 keys, replace the element with its successor
      // s and recursively delete s

      // If both children have only 1 key, merge the right child into the left child and push the
      // element to delete into the left child
      // Free the right child and recursively delete the element to delete from the left child
    }
  }
  else {
    cout << "node does not contain " << word;
    // Find the child to descend into

    // If the child has only key and has an immediate sibling with at least 2 keys,
    // move an element down from the parent into the child and move an element from the
    // sibling into the parent

    // If both the child and its immediate siblings have only 1 key each, merge the child node
    // with one of the siblings and move an element down from the parent node into the merged node
    // The element from the parent will be in the middle of the node
    // Free the node whose elements were merged into the other node

    // Descend into the child, and recursively call remove on that child
  }
}

void Tree25::sort() {
  ofstream outFile;
  outFile.open("output.txt");
  sort(root, outFile);
  outFile << endl;
  outFile.close();
}

void Tree25::sort(Node* node, ofstream& outFile) {
  if (node == NULL)
    return;

  sort(node->child1, outFile);
  outFile << node->data1->word << endl;
  sort(node->child2, outFile);
  if (node->data2 != NULL)
    outFile << node->data2->word << endl;
  sort(node->child3, outFile);
  if (node->data3 != NULL)
    outFile << node->data3->word << endl;
  sort(node->child4, outFile);
  if (node->data4 != NULL)
    outFile << node->data4->word << endl;
  sort(node->child5, outFile);
}

void Tree25::rangeSearch(string startWord, string endWord) {
  rangeSearch(root, startWord, endWord);
}

void Tree25::rangeSearch(Node* node, string startWord, string endWord) {
  if(node == NULL)
    return;

  rangeSearch(node->child1, startWord, endWord);
  if(node->data1->word >= startWord && node->data1->word <= endWord)
    cout << node->data1->word << endl;
  
  rangeSearch(node->child2, startWord, endWord);
  if (node->data2 != NULL && node->data2->word >= startWord && node->data2->word <= endWord)
      cout << node->data2->word << endl;

  rangeSearch(node->child3, startWord, endWord);
  if (node->data3 != NULL && node->data3->word >= startWord && node->data3->word <= endWord)
    cout << node->data3->word << endl;

  rangeSearch(node->child4, startWord, endWord);
  if (node->data4 != NULL && node->data4->word >= startWord && node->data4->word <= endWord)
    cout << node->data4->word  << endl;

  rangeSearch(node->child5, startWord, endWord);
}

bool Tree25::nodeContainsWord(Node* node, string word) {
  if (node == NULL)
    return false;

  if ((node->data1 != NULL && node->data1->word == word) ||
      (node->data2 != NULL && node->data2->word == word) ||
      (node->data3 != NULL && node->data3->word == word) ||
      (node->data4 != NULL && node->data4->word == word))
    return true;

  return false;
}

bool Tree25::isFiveNode(Node* node) {
  if (node == NULL)
    return false;

  if (node->data1 != NULL && node->data2 != NULL &&
      node->data3 != NULL && node->data4 != NULL)
    return true;

  return false;
}

void Tree25::insertExistingWord(Node*& node, string word) {
  if (node->data1->word == word) {
    cout << "word exists at data1" << endl;
    cout << "old count: " << node->data1->count;
    incrementWordCount(node->data1);
    cout << "new count: " << node->data1->count;
  }
  else if (node->data2->word == word) {
    cout << "word exists at data2" << endl;
    cout << "old count: " << node->data2->count;
    incrementWordCount(node->data2);
    cout << "new count: " << node->data2->count;
  }
  else if (node->data3->word == word) {
    cout << "word exists at data3" << endl;
    cout << "old count: " << node->data3->count;
    incrementWordCount(node->data3);
    cout << "new count: " << node->data3->count;
  }
  else if (node->data4->word == word) {
    cout << "word exists at data4" << endl;
    cout << "old count: " << node->data4->count;
    incrementWordCount(node->data4);
    cout << "new count: " << node->data4->count;
  }
}

bool Tree25::isLeaf(Node* node) {
  if (node->child1 == NULL && node->child2 == NULL && node->child3 == NULL &&
      node->child4 == NULL && node->child5 == NULL)
    return true;

  return false;
}

void Tree25::insertIntoLeaf(Node*& node, string word) {
  Word* newWord = new Word;
  newWord->word = word;
  newWord->count = 1;
  if (word < node->data1->word) {
    node->data4 = node->data3;
    node->data3 = node->data2;
    node->data2 = node->data1;
    node->data1 = newWord;
    cout << "insert into data1" << endl;
  }
  else if (word > node->data1->word && (node->data2 == NULL || word < node->data2->word)) {
    node->data4 = node->data3;
    node->data3 = node->data2;
    node->data2 = newWord;
    cout << "insert into data2" << endl;
  }
  else if (word > node->data2->word && (node->data3 == NULL || word < node->data3->word)) {
    node->data4 = node->data3;
    node->data3 = newWord;
    cout << "insert into data3" << endl;
  }
  else {
    node->data4 = newWord;
    cout << "insert into data4" << endl;
  }
}

bool Tree25::isRoot(Node* node) {
  if (node->parent == NULL)
    return true;

  return false;
}

void Tree25::removeFromLeaf(Node*& node, string word) {
  if (word == node->data1->word) {
    cout << "word is in data1" << endl;
    if (node->data1->count > 1) {
      cout << "decrement count" << endl;
      decrementWordCount(node->data1);
    }
    else {
      cout << "remove from data1" << endl;
      delete node->data1;
      node->data1 = node->data2;
      node->data2 = node->data3;
      node->data3 = node->data4;
      node->data4 = NULL;
    }
  }
  else if (word == node->data2->word) {
    cout << "word is in data2" << endl;
    if (node->data2-> count > 1) {
      cout << "decrement count" << endl;
      decrementWordCount(node->data2);
    }
    else {
      cout << "remove from data2" << endl;
      delete node->data2;
      node->data2 = node->data3;
      node->data3 = node->data4;
      node->data4 = NULL;
    }
  }
  else if (word == node->data3->word) {
    cout << "word is in data3" << endl;
    if (node->data3->count > 1) {
      cout << "decrement count" << endl;
      decrementWordCount(node->data3);
    }
    else {
      cout << "remove from data3" << endl;
      delete node->data3;
      node->data3 = node->data4;
      node->data4 = NULL;
    }
  }
  else {
    cout << "word is in data4" << endl;
    if (node->data4->count > 1) {
      cout << "decrement count" << endl;
      decrementWordCount(node->data4);
    }
    else {
      delete node->data4;
      node->data4 = NULL;
    }
  }
}

bool Tree25::containsTwoKeys(Node* node) {
  if (node == NULL)
    return false;

  if ((node->data2 == NULL && node->data1->count >= 2) ||
      (node->data2 != NULL && node->data1->count >= 1 && node->data2->count >=1))
    return true;

  return false;
      
}

void Tree25::printInorder() {
  printInorder(root);
}

void Tree25::printInorder(Node* node) {
  if (node == NULL)
    return;
  
  printInorder(node->child1);
  cout << "data1: " << node->data1->word << "(" << node->data1->count << ")" << endl;
  if (node->parent != NULL)
    cout << "parent of " << node->data1->word << " = " << node->parent->data1->word << endl;
  printInorder(node->child2);
  if (node->data2 != NULL) {
    cout << "data2: " << node->data2->word << "(" << node->data2->count << ")" << endl;
    if (node->parent != NULL)
      cout << "parent of " << node->data2->word << " = " << node->parent->data1->word << endl;
  }
  printInorder(node->child3);
  if (node->data3 != NULL) {
    cout << "data3: " << node->data3->word << "(" << node->data3->count << ")" << endl;
    if (node->parent != NULL)
      cout << "parent of " << node->data3->word << " = " << node->parent->data1->word << endl;
  }
  printInorder(node->child4);
  if (node->data4 != NULL) {
    cout << "data4: " << node->data4->word << "(" << node->data4->count << ")" << endl;
    if (node->parent != NULL) {
      cout << "parent of " << node->data4->word << " = " << node->parent->data1->word << endl;
    }
  }
  printInorder(node->child5);
  
}
