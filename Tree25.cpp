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
  printInorder();
  cout << "finished insert" << endl << endl;
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
    cout << word << " already exists. increment count" << endl;
    insertExistingWord(node, word);
  }
  
  // If the current node is a 5-node:
  if (isFiveNode(node)) {
    // Remove and save the middle value to get a 4-node
    // Split the remaining 4-node up into a 2-node and 3-node
    // The 2-node and 3-node will be the left and right child of the middle value, respectively
    // Insert the word into the corresponding left or right child
    
    // If the node is the root, the saved middle value becomes the new root
    // Ascend into the root and set child1 and child2 to be the left and right child, respectively
    
    // Otherwise, push the middle value up into the parent node
    // Ascend into the root and reorganize the children, adding in the new left and right children
  }
  else {
    // If the node is a leaf, insert the value into the node
    if (isLeaf(node)) {
      cout << "node is a leaf" << endl;
      insertIntoLeaf(node, word);
    }
  }
}

void Tree25::remove(string word) {

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
    cout << node->data1->word << " " << node->data1->count << endl;
  
  rangeSearch(node->child2, startWord, endWord);
  if (node->data2 != NULL && node->data2->word >= startWord && node->data2->word <= endWord)
      cout << node->data2->word << " " << node->data2->count << endl;

  rangeSearch(node->child3, startWord, endWord);
  if (node->data3 != NULL && node->data3->word >= startWord && node->data3->word <= endWord)
    cout << node->data3->word << " " << node->data3->count << endl;

  rangeSearch(node->child4, startWord, endWord);
  if (node->data4 != NULL && node->data4->word >= startWord && node->data4->word <= endWord)
    cout << node->data4->word << " " << node->data4->count << endl;

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
  cout << "insert into leaf" << endl;
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
