#include "Tree25.h"

#include <string>
#include <iostream>

using namespace std;

// constructor
Tree25::Tree25() {
  root = NULL;
}

// destructor
Tree25::~Tree25() {

}

bool Tree25::search(string word) {
  // STUB
  return false;
}

void Tree25::insert(string word) {
  cout << word << endl;
  insert(root, word);
  cout << word << " inserted\n" << endl;
}

void Tree25::insert(Node*& node, string word) {
  if (node == NULL) {
    cout << "node is NULL. create a new node and add " << word << endl;
    node = new Node();
    node->data1 = new Word;
    node->data1->word = word;
    return;
  }

  if (nodeContainsWord(node, word)) {
    cout << "node contains word" << endl;
    insertExistingWord(node, word);
    return;
  }

  if (isFiveNode(node)) {
    cout << "node is a five-node" << endl;
    Word* mid = node->data2;
    Node* newLeft = new Node();
    newLeft->data1 = node->data1;
    newLeft->child1 = node->child1;
    newLeft->child2 = node->child2;
    newLeft->parent = node->parent;
    Node* newRight = new Node();
    newRight->data1 = node->data3;
    newRight->data2 = node->data4;
    newRight->child1 = node->child3;
    newRight->child2 = node->child4;
    newRight->child3 = node->child5;
    newRight->parent = node->parent;

    if (isRoot(node)) {
      cout << "node is a five-node root" << endl;
      Node* newRoot = new Node();
      newRoot->data1 = mid;
      newRoot->child1 = newLeft;
      newRoot->child2 = newRight;
      newRoot->child1->parent = newRoot;
      newRoot->child2->parent = newRoot;
      root = newRoot;
      cout << "created new root" << endl;
      if (word < root->data1->word) {
	cout << "descend into left child" << endl;
	nodeInsert(root->child1, word);
      }
      else if (word > root->data1->word) {
	cout << "descend into right child" << endl;
	nodeInsert(root->child2, word);
      }
    }
    else {
      cout << "node is a five-node leaf" << endl;
      pushToParent(node, node->parent, mid, newLeft, newRight);
      if (word < mid->word)
	nodeInsert(newLeft, word);
      else if (word > mid->word)
	nodeInsert(newRight, word);
    }
  }
  else {
    if (isLeaf(node)) {
      cout << "node is a leaf" << endl;
      nodeInsert(node, word);
    }
    else {
      cout << "node is an internal node" << endl;
      if (node->data1 != NULL && word < node->data1->word) {
	cout << "descend into child 1" << endl;
	insert(node->child1, word);
      }
      else if ((node->data2 == NULL) ||
	       (node->data2 != NULL && word >= node->data1->word && word < node->data2->word)) {
	cout << "descend into child 2" << endl;
	insert(node->child2, word);
      }
      else if ((node->data3 == NULL) ||
	       (node->data3 != NULL && word >= node->data2->word && word < node->data3->word)) {
	cout << "descend into child 3" << endl;
	insert(node->child3, word);
      }
      else if ((node->data4 == NULL) ||
	       (node->data4 != NULL && word >= node->data3->word && word < node->data4->word)) { 
	cout << "descend into child 4" << endl;
	insert(node->child4, word);
      }
      else {
	cout << "descend into child 5" << endl;
	insert(node->child5, word);
      }
    }
  }
}

bool Tree25::nodeContainsWord(Node* node, string word) {
  if ((node->data1 != NULL && node->data1->word == word) ||
      (node->data2 != NULL && node->data2->word == word) ||
      (node->data3 != NULL && node->data3->word == word) ||
      (node->data4 != NULL && node->data4->word == word))
    return true;
  
  return false;
}

void Tree25::insertExistingWord(Node* node, string word) {
  if (node->data1->word == word)
    incrementWordCount(node->data1);
  else if (node->data2->word == word)
    incrementWordCount(node->data2);
  else if (node->data3->word == word)
    incrementWordCount(node->data3);
  else if (node->data4->word == word)
    incrementWordCount(node->data4);
}

bool Tree25::isFiveNode(Node* node) {
  if (node->data1 != NULL && node->data2 != NULL &&
      node->data3 != NULL && node->data4 != NULL)
    return true;

  return false;
}

bool Tree25::isRoot(Node* node) {
  if (node->parent == NULL)
    return true;

  return false;
}

bool Tree25::isLeaf(Node* node) {
  if (node->child1 == NULL && node->child2 == NULL && node->child3 == NULL &&
      node->child4 == NULL && node->child5 == NULL) {
    return true;
  }

  return false;
}

void Tree25::pushToParent(Node*& node, Node*& parent, Word* data, Node* left, Node* right) {
  node->data2 = node->data3;
  node->data3 = node->data4;
  node->data4 = NULL;
  cout << "mid replaced" << endl;

  if (parent->data2 == NULL) {
    cout << "data1 " << parent->data1->word << endl;
    parent->data2 = new Word;
    parent->data2 = data;
    cout << "mid pushed to parent data2" << endl;
    cout << "data2 " << parent->data2->word << endl;
    parent->child2 = left;
    parent->child3 = right;
  }
  else if (parent->data3 == NULL) {
    cout << "data1 " << parent->data1->word << endl;
    cout << "data2 " << parent->data2->word << endl;
    parent->data3 = new Word;
    parent->data3 = data;
    cout << "mid pushed to parent data3" << endl;
    cout << "data3 " << parent->data3->word << endl;
    parent->child3 = left;
    parent->child4 = right;
  }
  else if (parent->data4 == NULL) {
    cout << "data1 " << parent->data1->word << endl;
    cout << "data2 " << parent->data2->word << endl;
    cout << "data3 " << parent->data3->word << endl;
    parent->data4 = new Word;
    parent->data4 = data;
    cout << "mid pushed to parent data4" << endl;
    cout << "data4 " << parent->data4->word << endl;
    parent->child4 = left;
    parent->child5 = right;
  }
}

void Tree25::nodeInsert(Node*& node, string word) {
  Word* newWord = new Word;
  newWord->word = word;
  newWord->count = 1;
  if (node->data1 == NULL) {
    node->data1 = newWord;
    cout << "inserted into data1" << endl;
  }
  else if (node->data2 == NULL) {
    if (word < node->data1->word) {
      node->data2 = node->data1;
      node->data1 = newWord;
      cout << "inserted into data1" << endl;
    }
    else {
      node->data2 = newWord;
      cout << "inserted into data2" << endl;
    }
  }
  else if (node->data3 == NULL) {
    if (word < node->data1->word) {
      node->data3 = node->data2;
      node->data2 = node->data1;
      node->data1 = newWord;
      cout << "inserted into data1" << endl;
    }
    else if (word > node->data1->word && word < node->data2->word) {
      node->data3 = node->data2;
      node->data2 = newWord;
      cout << "inserted into data2" <<endl;
    }
    else {
      node->data3 = newWord;
      cout << "inserted into data3" << endl;
    }
  }
  else if (node->data4 == NULL) {
    if (word < node->data1->word) {
      node->data4 = node->data3;
      node->data3 = node->data2;
      node->data2 = node->data1;
      node->data1 = newWord;
      cout << "inserted into data1" << endl;
    }
    else if (word > node->data1->word && word < node->data2->word) {
      node->data4 = node->data3;
      node->data3 = node->data2;
      node->data2 = newWord;
      cout << "inserted into data2" << endl;
    }
    else if (word > node->data2->word && word < node->data3->word) {
      node->data4 = node->data3;
      node->data3 = newWord;
      cout << "inserted into data3" << endl;
    }
    else {
      node->data4 = newWord;
      cout << "inserted into data4" << endl;
    }
  }
}

void Tree25::remove(string word) {
  remove(root, word);
}

void Tree25::remove(Node*& node, string word) {
  if(nodeContainsWord(node, word)) {
    if(isLeaf(node) && containsTwoKeys(node)) {
      removeFromLeaf(node, word);
    }
    else{
      Word* wordToDelete;
      Node* leftChild, rightChild;
      if(node->data1->word == word) {
        wordToDelete = node->data1;
        leftChild = node->child1;
        rightChild = node->child2;
      }
      else if(node->data2->word == word) {
        wordToDelete = node->data2;
        leftChild = node->child2;
        rightChild = node->child3;
      }
      else if(node->data3->word == word) {
        wordToDelete = node->data3;
        leftChild = node->child3;
        rightChild = node->child4;
      }
      else if(node->data4->word == word) {
        wordToDelete = node->data4;
        leftChild = node->child4;
        rightChild = node->child5;
      }
      if(containsTwoKeys(leftChild)) {
        if(leftChild->data4 != NULL) {
          wordToDelete = leftChild->data4;
          remove(leftChild, leftChild->data4->word);
        }
	else if(leftChild->data3 != NULL) {
          wordToDelete = leftChild->data3;
          remove(leftChild, leftChild->data3->word);
        }
	else {
          wordToDelete = leftChild->data2;
          remove(leftChild, leftChild->data2->word);
        }
      }
      else if(containsTwoKeys(rightChild)) {
          wordToDelete = rightChild->data1;
          remove(rightChild, rightChild->data1->word);
        }
      else {
	merge(node, leftChild, rightChild, wordToDelete);
	remove(leftChild, word);
      }
    }
  }
  else {
    Node* childNode;
    if (word < node->data1->word)
      childNode = node->child1;
    else if (word > node->data1->word && word < node->data2->word)
      childNode = node->child2;
    else if (word > node->data2->word && word < node->data3->word)
      childNode = node->child3;
    else if (word > node->data3->word && word < node->data4->word)
      childNode = node->child4;
    else
      childNode = node->child5;

    if (hasOneKey(childNode)) {
      if (node->child1 == childNode) {
	if (containsTwoKeys(node->child2)) {
	  rotateCC(node, childNode, node->child2);
	}
	else {
	  merge(node, node->child1, node->child2, node->data1);
	}
      }
      else if (node->child2 == childNode) {
	if (containsTwoKeys(node->child1)) {
	  
	}
	else if (containsTwoKeys(node->child3)) {
	  rotateCC(node, childNode, node->child3);
	}
	else {

	}
      }
      else if (node->child3 == childNode) {
	if (containsTwoKeys(node->child2)) {

	}
	else if (containsTwoKeys(node->child4)) {
	  rotateCC(node, childNode, node->child4);
	}
	else {

	}
      }
      else if (node->child4 == childNode) {
	if (containsTwoKeys(node->child3)) {

	}
	else if (containsTwoKeys(node->child5)) {
	  rotateCC(node, childNode, node->child5);
	}
	else {

	}
      }
      else if (node->child5 == childNode) {
	if (containsTwoKeys(node->child4)) {

	}
	else {

	}
      }
    }
    remove(childNode, word);
  }
}

void Tree25::removeFromLeaf(Node*& node, string word) {
  if(word == node->data1->word) {
    if(node->data1->count > 1)
      decrementWordCount(node->data1);
    else {
      delete node->data1;
      node->data1 = node->data2;
      node->data2 = node->data3;
      node->data3 = node->data4;
      node->data4 = NULL;
    }
  }
  else if(word == node->data2->word) {
    if(node->data2->count > 1)
      decrementWordCount(node->data2);
    else {
      delete node->data2;
      node->data2 = node->data3;
      node->data3 = node->data4;
      node->data4 = NULL;
    }
  }
  else if(word == node->data3->word) {
    if(node->data3->count > 1)
      decrementWordCount(node->data3);
    else {
      delete node->data3;
      node->data3 = node->data4;
      node->data4 = NULL;
    }
  }
  else if(word == node->data4->word) {
    if(node->data4->count > 1)
      decrementWordCount(node->data4);
    else
      delete node->data4;
  }
}


bool Tree25::containsTwoKeys(Node* node) {
  if(node->data1 != NULL && node->data2 != NULL)
    return true;
  return false;
}

void Tree25::merge(Node*& node, Node*& leftChild, Node*& rightChild, Word* wordToDelete) {
  leftChild->data2 = wordToDelete;
  leftChild->data3 = rightChild->data1;
  if (node->data1 == wordToDelete) {
    node->data1 = node->data2;
    node->data2 = node->data3;
    node->data3 = node->data4;
    node->data4 = NULL;
  }
  else if (node->data2 == wordToDelete) {
    node->data2 = node->data3;
    node->data3 = node->data4;
    node->data4 = NULL;
  }
  else if (node->data3 == wordToDelete) {
    node->data3 = node->data4;
    node->data4 = NULL;
  }
  else
    node->data4 = NULL;

  delete rightChild;
}

bool Tree25:containsOneKey(Node* node) {
  if (node->data1 != NULL && node->data2 == NULL && node->data3 == NULL && node->data4 == NULL)
    return true;
  return false;
}

void Tree25::rotateCC(Node*& node, Node*& child, Node*& rightSibling) {
  child->data2 = node->data1;
  node->data1 = node->data2;
  node->data2 = node->data3;
  noede->data4 = NULL;
  if (node->data2 == NULL)
    node->data2 = rightSibling->data1;
  else if (node->data3 == NULL)
    node->data3 = rightSibling->data1;
  else
    node->data4 = rightSibling_data1;
  rightSibling->data1 = rightSibling->data2;
  rightSibling->data2 = rightSibling->data3;
  rightSibling->data3 = rightSibling->data4;
  rightSibling->data4 = NULL;
}

void Tree25::rotateCW(Node*& node, Node*& child, Node*& leftSibling) {

}

void Tree25::sort() {
  
}

void Tree25::rangeSearch(string startWord, string endWord) {

}
