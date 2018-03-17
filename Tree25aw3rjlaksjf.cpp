#include "Tree25.h"

#include <string>
#include <iostream>

using namespace std;

// constructor
Tree25::Tree25() {
  root = NULL;
  height = 0;
}

// destructor
Tree25::~Tree25() {

}

bool Tree25::search(string word) {
  return false;
}

void Tree25::insert(string word) {
  cout << word << endl;
  insert(root, word);
  //  cout << "done" << endl;
}

void Tree25::insert(Node*& node, string word) {
  if (node == NULL) {
    node = new Node();
    node->data1->word = word;
    root = node;
    return;
  }

  if (nodeContains(node, word)) {
    nodeInsert(node,word);
    return;
  }
  
  if (isLeaf(node) && !isFiveNode(node)) {
    nodeInsert(node, word);
    return;
  }

  if (isFiveNode(node)) {
    Word* tempData = node->data2;
    Node* newLeft = new Node();
    newLeft->data1 = node->data1;
    newLeft->child1 = node->child1;
    newLeft->child2 = node->child2;
    Node* newRight = new Node();
    newRight->data1 = node->data3;
    newRight->data2 = node->data4;
    newRight->child1 = node->child3;
    newRight->child2 = node->child4;
    newRight->child3 = node->child5;

    if (node == root) {
      Node* newRoot = new Node();
      newRoot->data1 = tempData;
      newRoot->child1 = newLeft;
      newRoot->child2 = newRight;
      newRoot->child1->parent = newRoot;
      newRoot->child2->parent = newRoot;
      newRoot->child3->parent = newRoot;
      newRoot->child4->parent = newRoot;
      newRoot->child5->parent = newRoot;
      root = newRoot;
    }
    else {
      insert(node->parent, tempData->word);
      if (tempData < node->parent->data1) {
	node->parent->child1 = newLeft;
	node->parent->child2 = newRight;
      }
      else {
	if (node->parent->data4 == "") {
	  node->parent->child3 = newLeft;
	  node->parent->child4 = newRight;
	}
	else {
	  node->parent->child4 = newLeft;
	  node->parent->child5 = newRight;
	}
      }
    }

  }
  else {
    if (word.compare(node->data1->word) < 0)
      insert(node->child1, word);
    else if (word.compare(node->data1->word) > 0 && word.compare(node->data2->word) < 0)
      insert(node->child2, word);
    else if (word.compare(node->data2->word) > 0 && word.compare(node->data3->word) < 0)
      insert(node->child3, word);
    else if (word.compare(node->data3->word) > 0 && word.compare(node->data4->word) < 0)
      insert(node->child4, word);
    else if (word.compare(node->data4->word) > 0)
      insert(node->child4, word);
  } 

}

void Tree25::remove(string word) {

}

void Tree25::sort() {

}

void Tree25::rangeSearch(string startWord, string endWord) {

}

void Tree25::initNode(Node*& node) {
  node->data1 = node->data2 = node->data3 = node->data4 = "";
  node->child1 = node->child2 = node->child3 = node->child4 = node->child5 = NULL;
}

bool Tree25::isFiveNode(Node* node) {
  if (node->data1 != "" && node->data2 != "" &&
      node->data3 != "" && node->data4 != "")
    return true;

  return false;
}
 
bool Tree25::nodeIsEmpty(Node* node) {
  if (node->data1 == "" && node->data2 == "" &&
      node->data3 == "" && node->data4 == "")
    return true;

  return false;
}

bool Tree25::isLeaf(Node* node) {
  if (node->child1 == NULL && node->child2 == NULL && node->child3 == NULL &&
      node->child4 == NULL && node->child5 == NULL)
    return true;

  return false;
}

void Tree25::nodeInsert(Node* node, string word) {
  if (node->data1 == NULL)
    node->data1->word = word;
  else if(word == node->data1->word)
    incrementWordCount(node->data1);
  else if(word.compare(node->data1) < 0) {
    node->data4 = node->data3;
    node->data3 = node->data2;
    node->data2 = node->data1;
    node->data1->word = word;
  }
  else if (node->data2 == NULL)
    node->data2->word = word;
  else if (word == node->data2->word)
    incrementWordCount(node->data2);
  else if(word.compare(node->data1) > 0 && word.compare(node->data2) < 0) {
    node->data4 = node->data3;
    node->data3 = node->data2;
    node->data2->word = word;
  }
  else if (node->data3 == NULL)
    node->data3->word = word;
  else if (word == node->data3->word)
    incrementWordCount(node->data3);
  else if(word.compare(node->data2) > 0 && word.compare(node->data3) < 0) {
    node->data4 = node->data3;
    node->data3->word = word;
  }
  else if (node->data4->word == NULL) {
    node->data4->word = new Word();
    node->data4->word = word;
  }
  else if (word == node->data4->word)
    incrementWordCount(node->data4);
  else {
    node->data4->word = word;
  }
}

void Tree25::incrementWordCount(Word*& word) {
  word->count++;
}

bool Tree25::nodeContains(Node* node, string word) {
  if (node->data1->word == word || node->data2->word == word || node->data3->word == word || node->data4->word == word)
    return true;
  
  return false;
}
