#include "Tree25.h"

#include <string>
#include <iostream>
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
  return Tree25::search(root, word);
}

bool Tree25::search(Node* node, string word) {
  if (node == NULL)
    return false;

  if (nodeContainsWord(node, word))
    return true;
  else {
    if (word < node->data1->word) {
      cout << "search descending into child1" << endl;
      return search(node->child1, word);
    }
    else if ((node->data2 == NULL && word >node->data1->word) ||
             (word > node->data1->word && word < node->data2->word)) {
      cout << "search descending into child2" << endl;
      return search(node->child2, word);
    }
    else if ((node->data3 == NULL && word > node->data2->word) ||
             (word > node->data2->word && word < node->data3->word)) {
      cout << "search descending into child3" << endl;
      return search(node->child3, word);
    }
    else if ((node->data4 == NULL && word > node->data3->word) ||
             (word > node->data3->word && word < node->data4->word)) {
      cout << "search descending into child4" << endl;
      return search(node->child4, word);
    }
    else {
      cout << "search descending into child5" << endl;
      return search(node->child5, word);
    }
  }

  return false;
}

void Tree25::insert(string word) {
  cout << word << endl;
  insert(root, word);
  cout << word << " inserted\n" << endl;
  printInorder();
  cout << endl;
}

void Tree25::insert(Node*& node, string word) {
  if (node == NULL) {
    cout << "node is NULL. create a new node and add " << word << endl;
    node = new Node();
    node->data1 = new Word;
    node->data1->word = word;
    node->data1->count = 1;
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
      cout << "created new root: " << newRoot->data1->word << endl;
      if (word < root->data1->word) {
        cout << "descend into left child: " << newRoot->child1->data1->word << endl;
        insert(root->child1, word);
      }
      else if (word > root->data1->word) {
        cout << "descend into right child: " << newRoot->child2->data1->word << ", " << newRoot->child2->data2->word << endl;
        insert(root->child2, word);
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
  if (node->data1->word == word) {
    cout << "word exists at data1" << endl;
    cout << "old count: " << node->data1->count << endl;
    incrementWordCount(node->data1);
    cout << "new count: " << node->data1->count << endl;
  }
  else if (node->data2->word == word) {
    cout << "word exists at data2" << endl;
    cout << "old count: " << node->data2->count << endl;
    incrementWordCount(node->data2);
    cout << "new count: " << node->data2->count << endl;
  }
  else if (node->data3->word == word) {
    cout << "word exists at data3" << endl;
    cout << "old count: " << node->data3->count << endl;
    incrementWordCount(node->data3);
    cout << "new count: " << node->data3->count << endl;
  }
  else if (node->data4->word == word) {
    cout << "word exists at data4" << endl;
    cout << "old count: " << node->data4->count << endl;
    incrementWordCount(node->data4);
    cout << "new count: " << node->data4->count << endl;
  }
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
    parent->data2 = new Word;
    if (data->word < parent->data1->word) {
      parent->data2->word = parent->data1->word;
      parent->data2->count = parent->data1->count;
      parent->data1->word = data->word;
      parent->data1->count = data->count;
      parent->child3 = parent->child2;
      parent->child1 = left;
      parent->child2 = right;
      cout << "mid pushed to parent data1";
    }
    else {
      parent->data2->word = data->word;
      parent->data2->count = data->count;
      parent->child2 = left;
      parent->child3 = right;
      cout << "mid pushed to parent data2";
    }
  }
  else if (parent->data3 == NULL) {
    parent->data3 = new Word;
    if (data->word < parent->data1->word) {
      parent->data3->word = parent->data2->word;
      parent->data3->count = parent->data2->count;
      parent->data2->word = parent->data1->word;
      parent->data2->count = parent->data1->count;
      parent->data1->word = data->word;
      parent->data1->count = data->count;
      parent->child4 = parent->child3;
      parent->child3 = parent->child2;
      parent->child1 = left;
      parent->child2 = right;
      cout << "mid pushed to parent data1" << endl;
      cout << parent->data3->word << endl;
    }
    else if (data->word > parent->data1->word && data->word < parent->data2->word) {
      parent->data3->word = parent->data2->word;
      parent->data3->count = parent->data2->count;
      parent->data2->word = data->word;
      parent->data2->count = data->count;
      parent->child4 = parent->child3;
      parent->child2 = left;
      parent->child3 = right;
      cout << "mid pushed to parent data2" << endl;
    }
    else {
      parent->data3->word = data->word;
      parent->data3->count = data->count;
      parent->child3 = left;
      parent->child4 = right;
      cout << "mid pushed to parent data3" << endl;
    }
  }
  else if (parent->data4 == NULL) {
    parent->data4 = new Word;
    if (data->word < parent->data1->word) {
      parent->data4->word = parent->data3->word;
      parent->data4->count = parent->data3->count;
      parent->data3->word = parent->data2->word;
      parent->data3->count = parent->data2->count;
      parent->data2->word = parent->data1->word;
      parent->data2->count = parent->data1->count;
      parent->data1->word = data->word;
      parent->data1->count = data->count;
      parent->child5 = parent->child4;
      parent->child4 = parent->child3;
      parent->child3 = parent->child2;
      parent->child1 = left;
      parent->child2 = right;
      cout << "mid pushed to parent data1" << endl;
    }
    else if (data->word > parent->data1->word && data->word < parent->data2->word) {
      parent->data4->word = parent->data3->word;
      parent->data4->count = parent->data3->count;
      parent->data3->word = parent->data2->word;
      parent->data3->count = parent->data2->count;
      parent->data2->word = data->word;
      parent->data2->count = data->count;
      parent->child5 = parent->child4;
      parent->child4 = parent->child3;
      parent->child2 = left;
      parent->child3 = right;
      cout << "mid pushed to parent data2" << endl;
    }
    else if (data->word > parent->data2->word && data->word < parent->data3->word) {
      parent->data4->word = parent->data3->word;
      parent->data4->count = parent->data3->count;
      parent->data3->word = data->word;
      parent->data3->count = data->count;
      parent->child5 = parent->child4;
      parent->child3 = left;
      parent->child4 = right;
      cout << "mid pushed to parent data3" << endl;
    }
    else {
      parent->data4->word = data->word;
      parent->data4->count = data->count;
      parent->child4 = left;
      parent->child5 = right;
      cout << "mid pushed to parent data4" << endl;
    }
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
  cout << "word to remove: " << word << endl;
  remove(root, word);
  cout << "remove successful" << endl;
}

void Tree25::remove(Node*& node, string word) {
  if (node == NULL)
    return;
  
  if(nodeContainsWord(node, word)) {
    cout << "node contains the word" << endl;
    if (node->data1 != NULL && node->data1->word == word && node->data1->count > 1) {
      decrementWordCount(node->data1);
      return;
    }
    else if (node->data2 != NULL && node->data2->word == word && node->data2->count > 1) {
      decrementWordCount(node->data2);
      return;
    }
    else if (node->data3 != NULL && node->data3->word == word && node->data3->count > 1) {
      decrementWordCount(node->data3);
      return;
    }
    else if (node->data4 != NULL && node->data4->word == word && node->data4->count > 1) {
      decrementWordCount(node->data4);
      return;
    }
    
    if(isLeaf(node) && containsTwoKeys(node)) {
      cout << "node is a leaf with at least two keys" << endl;
      removeFromLeaf(node, word);
    }
    else{
      cout << "node is an internal node" << endl;
      Word* wordToDelete;
      Node *leftChild, *rightChild;
      if(node->data1->word == word) {
        cout << "node is in data1" << endl;
        wordToDelete = node->data1;
        leftChild = node->child1;
        rightChild = node->child2;
      }
      else if(node->data2->word == word) {
        cout << "node is in data2" << endl;
        wordToDelete = node->data2;
        leftChild = node->child2;
        rightChild = node->child3;
      }
      else if(node->data3->word == word) {
        cout << "node is in data3" << endl;
        wordToDelete = node->data3;
        leftChild = node->child3;
        rightChild = node->child4;
      }
      else if(node->data4->word == word) {
        cout << "node is in data4" << endl;
        wordToDelete = node->data4;
        leftChild = node->child4;
        rightChild = node->child5;
      }

      if(containsTwoWords(leftChild)) {
        cout << "left child has at least two words" << endl;
        if(leftChild->data4 != NULL) {
          wordToDelete->word = leftChild->data4->word;
          wordToDelete->count = leftChild->data4->count;
          while (leftChild->data4 != NULL && leftChild->data4->count > 0) 
	    remove(leftChild, leftChild->data4->word);
	  cout << "replaced with data4 in left child" << endl;
        }
        else if(leftChild->data3 != NULL) {
          wordToDelete->word = leftChild->data3->word;
          wordToDelete->count = leftChild->data3->count;
	  while (leftChild->data3 != NULL && leftChild->data3->count > 0)
	    remove(leftChild, leftChild->data3->word);
          cout << "replaced with data3 in left child" << endl;
        }
        else {
          wordToDelete->word = leftChild->data2->word;
          wordToDelete->count = leftChild->data2->count;
	  Word *predecessor = leftChild->data2;
          while (leftChild->data2 != NULL && leftChild->data2->count > 0) {
	    cout << leftChild->data2->word << endl;
	    remove(leftChild, leftChild->data2->word);
	    cout << "removed" << endl;
	  }
          cout << "replaced with data2 in left child" << endl;
        }
      }
      else if(containsTwoWords(rightChild)) {
	wordToDelete->word = rightChild->data1->word;
	wordToDelete->count = rightChild->data1->count;
	string successor = rightChild->data1->word;
	while (rightChild->data1->word == successor)
	  remove(rightChild, successor);
	cout << "replaced with data1 in left child" << endl;
      }
      else {
        merge(node, leftChild, rightChild, wordToDelete);
	while (leftChild->data2->word == word)
	  remove(leftChild, word);
      }
    }
  }
  else {
    cout << "node does not contain the word" << endl;
    Node* childNode;
    if (word < node->data1->word) {
      childNode = node->child1;
      cout << "child node is child1" << endl;
    }
    else if ((node->data2 == NULL && word > node->data1->word) ||
	     (node->data2 != NULL && word > node->data1->word && word < node->data2->word)) {
      childNode = node->child2;
      cout << "child node is child2" << endl;
    }
    else if ((node->data3 == NULL && word > node->data2->word) ||
	     (node->data3 != NULL && word > node->data2->word && word < node->data3->word)) {
      childNode = node->child3;
      cout << "child node is child3" << endl;
    }
    else if ((node->data4 == NULL && word > node->data3->word) ||
	     (node->data4 != NULL && word > node->data3->word && word < node->data4->word)) {
      childNode = node->child4;
      cout << "child node is child4" << endl;
    }
    else {
      childNode = node->child5;
      cout << "child node is child5" << endl;
    }
    
    if (childNode != NULL && containsOneKey(childNode)) {
      cout << "child node has only one key" << endl;
      if (node->child1 == childNode) {
        if (containsTwoWords(node->child2)) {
	  cout << "right sibling has at least two keys" << endl;
          rotateCC(node, node->child1, node->child2);
	 }
        else {
	  cout << "siblings only have one key each" << endl;
          merge(node, node->child1, node->child2, node->data1);
        }
      }
      else if (node->child2 != NULL && node->child2 == childNode) {
        if (containsTwoWords(node->child1)) {
	  cout << "left sibling has at least two keys" << endl;
          rotateCW(node, node->child2, node->child1);
	}
        else if (containsTwoWords(node->child3)) {
	  cout << "right sibling has at least two keys" << endl;
          rotateCC(node, node->child2, node->child3);
        }
        else {
	  cout << "siblings only have one key each" << endl;
          merge(node, node->child1, node->child2, node->data1);
	  childNode = node->child1;
        }
      }
      else if (node->child3 != NULL && node->child3 == childNode) {
        if (containsTwoWords(node->child2)) {
	  cout << "left sibling has at least two keys" << endl;
          rotateCW(node, node->child3, node->child2);
        }
        else if (containsTwoWords(node->child4)) {
	  cout << "right sibling has at least two keys" << endl;
          rotateCC(node, node->child3, node->child4);
        }
        else {
	  cout << "siblings only have one key each" << endl;
          merge(node, node->child2, node->child3, node->data2);
	  childNode = node->child2;
        }
      }
      else if (node->child4 != NULL && node->child4 == childNode) {
        if (containsTwoWords(node->child3)) {
	  cout << "left sibling has at least two keys" << endl;
          rotateCW(node, node->child4, node->child3);
        }
        else if (containsTwoWords(node->child5)) {
	  cout << "right sibling has at least two keys" << endl;
          rotateCC(node, node->child4, node->child5);
        }
        else {
	  cout << "siblings only have one key each" << endl;
          merge(node, node->child3, node->child4, node->data3);
	  childNode = node->child3;
	}
      }
      else if (node->child5 != NULL && node->child5 == childNode) {
        if (containsTwoWords(node->child4)) {
	  cout << "left sibling has at least two keys" << endl;
          rotateCW(node, node->child5, node->child4);
        }
        else {
	  cout << "siblings only have one key each" << endl;
          merge(node, node->child4, node->child5, node->data4);
	  childNode = node->child4;
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
    else {
      delete node->data4;
      node->data4 = NULL;
    }
  }
}

bool Tree25::containsTwoKeys(Node* node) {
  if (node == NULL)
    return false;
  
  if ((node->data1 != NULL && node->data1->count >= 2) || (node->data2 != NULL && node->data2->count >= 1))
    return true;
  return false;
}

bool Tree25::containsTwoWords(Node* node) {
  if (node == NULL)
    return false;
  if (node->data1 != NULL && node->data2 != NULL)
    return true;
  return false;
}

void Tree25::merge(Node*& node, Node*& leftChild, Node*& rightChild, Word* wordToDelete) {
  leftChild->data2 = new Word;
  leftChild->data2->word = wordToDelete->word;
  leftChild->data2->count = wordToDelete->count;
  cout << "copied word to delete to left child data2" << endl;
  leftChild->data3 = new Word;
  leftChild->data3->word = rightChild->data1->word;
  leftChild->data3->count = rightChild->data1->count;
  delete rightChild;
  rightChild = NULL;
  cout << "merged right child data1 into left child data3" << endl;
  
  if (node->data1 == wordToDelete) {
    cout << "word to delete is in data1" << endl;
    delete node->data1;
    node->data1 = node->data2;
    node->data2 = node->data3;
    node->data3 = node->data4;
    node->data4 = NULL;
    node->child2 = node->child3;
    node->child3 = node->child4;
    node->child4 = node->child5;
    //delete node->child5;
    node->child5 = NULL;
  }
  else if (node->data2 == wordToDelete) {
    cout << "word to delete is in data2" << endl;
    delete node->data2;
    node->data2 = node->data3;
    node->data3 = node->data4;
    node->data4 = NULL;
    node->child3 = node->child4;
    node->child4 = node->child5;
    //delete node->child5;
    node->child5 = NULL;
    cout << "finish merge" << endl;
  }
  else if (node->data3 == wordToDelete) {
    cout << "word to delete is in data3" << endl;
    delete node->data3;
    node->data3 = node->data4;
    node->data4 = NULL;
    node->child4 = node->child5;
    // delete node->child5;
    node->child5 = NULL;
  }
  else {
    cout << "word to delete is in data4" << endl;
    delete node->data4;
    node->data4 = NULL;
    node->child5 = NULL;
  }

}

bool Tree25::containsOneKey(Node* node) {
  if (node == NULL)
    return false;
      
  if (node->data1 != NULL && node->data1->count == 1 && node->data2 == NULL && node->data3 == NULL && node->data4 == NULL)
    return true;
  return false;
}

void Tree25::rotateCC(Node*& node, Node*& child, Node*& rightSibling) {
  if (node->child1->data1->word == child->data1->word) {
    child->data1->word = node->data1->word;
    child->data1->count = node->data1->count;
    node->data1->word = rightSibling->data1->word;
    node->data1->count = rightSibling->data1->count;
  }
  else if (node->child2->data1->word == child->data1->word) {
    child->data1->word = node->data2->word;
    child->data1->count = node->data2->count;
    node->data2->word = rightSibling->data1->word;
    node->data2->count = rightSibling->data1->count;
  }
  else if (node->child3->data1->word == child->data1->word) {
    child->data1->word = node->data3->word;
    child->data1->count = node->data3->count;
    node->data3->word = rightSibling->data1->word;
    node->data3->count = rightSibling->data1->count;
  }
  else if (node->child4->data1->word == child->data1->word) {
    child->data1->word = node->data4->word;
    child->data1->count = node->data4->count;
    node->data4->word = rightSibling->data1->word;
    node->data4->count = rightSibling->data1->count;
  }
  delete rightSibling->data1;
  rightSibling->data1 = rightSibling->data2;
  rightSibling->data2 = rightSibling->data3;
  rightSibling->data3 = rightSibling->data4;
  rightSibling->data4 = NULL;
  
}
void Tree25::rotateCW(Node*& node, Node*& child, Node*& leftSibling) {
  string wordFromLeftSibling;
  int countFromLeftSibling;
  if (leftSibling->data4 != NULL) {
    wordFromLeftSibling = leftSibling->data4->word;
    countFromLeftSibling = leftSibling->data4->count;
    delete leftSibling->data4;
    leftSibling->data4 = NULL;
  }
  else if (leftSibling->data3 != NULL) {
    wordFromLeftSibling = leftSibling->data3->word;
    countFromLeftSibling = leftSibling->data3->count;
    delete leftSibling->data3;
    leftSibling->data3 = NULL;
  }
  else {
    wordFromLeftSibling = leftSibling->data2->word;
    countFromLeftSibling = leftSibling->data2->count;
    delete leftSibling->data2;
    leftSibling->data2 = NULL;
  }

  cout << "word from left sibling is " << wordFromLeftSibling << " " << countFromLeftSibling << endl;

  if (node->child2->data1->word == child->data1->word) {
    cout << "word to delete is in child2" << endl;
    child->data1->word = node->data1->word;
    child->data1->count = node->data1->count;
    node->data1->word = wordFromLeftSibling;
    node->data1->count = countFromLeftSibling;
  }
  else if (node->child3->data1->word == child->data1->word) {
    cout << "word to delete is in child3" << endl;
    child->data1->word = node->data2->word;
    child->data1->count = node->data2->count;
    node->data2->word = wordFromLeftSibling;
    node->data2->count = countFromLeftSibling;
  }
  else if (node->child4->data1->word == child->data1->word) {
    cout << "word to delete is in child4" << endl;
    child->data1->word = node->data3->word;
    child->data1->count = node->data3->count;
    node->data3->word = wordFromLeftSibling;
    node->data3->count = countFromLeftSibling;
  }
  else if (node->child5->data1->word == child->data1->word) {
    cout << "word to delete is in child5" << endl;
    child->data1->word = node->data4->word;
    child->data1->count = node->data4->count;
    node->data4->word = wordFromLeftSibling;
    node->data4->count = countFromLeftSibling;
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
  if(node == NULL) return;

  rangeSearch(node->child1, startWord, endWord);
  if(node->data1->word >= startWord && node->data1->word <= endWord)
    cout << node->data1->word << " " << node->data1->count << endl;
  rangeSearch(node->child2, startWord, endWord);
  if (node->data2 != NULL) {
    if(node->data2->word >= startWord && node->data2->word <= endWord)
      cout << node->data2->word << " " << node->data2->count << endl;
  }
  rangeSearch(node->child3, startWord, endWord);
  if (node->data3 != NULL) {
    if(node->data3->word >= startWord && node->data3->word <= endWord)
      cout << node->data3->word << " " << node->data3->count << endl;
  }
  rangeSearch(node->child4, startWord, endWord);
  if (node->data4 != NULL) {
    if(node->data4->word >= startWord && node->data4->word <= endWord)
      cout << node->data4->word << " " << node->data4->count << endl;
  }
  rangeSearch(node->child5, startWord, endWord);
}

void Tree25::printInorder() {
  printInorder(root);
}

void Tree25::printInorder(Node* node) {
  if (node == NULL)
    return;

  printInorder(node->child1);
  cout << "data1: " << node->data1->word << " " << node->data1->count << endl;
  printInorder(node->child2);
  if (node->data2 != NULL)
    cout << "data2: " << node->data2->word << " " << node->data2->count << endl;
  printInorder(node->child3);
  if (node->data3 != NULL)
    cout << "data3: " << node->data3->word << " " <<  node->data3->count << endl;
  printInorder(node->child4);
  if (node->data4 != NULL)
    cout << "data4: " << node->data4->word << " " << node->data4->count << endl;
  printInorder(node->child5);

}

