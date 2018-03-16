#include "AVL.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

AVL::AVL() {
	root = NULL;
}

AVL::~AVL() {
	destroyTree();
}

void AVL::printInorder() {
	printInorder(root);
}
void AVL::printInorder(AvlNode* node) {
	if(node == NULL) return;
	printInorder(node->left);
	cout << node->word << endl;
	printInorder(node->right);
}

bool AVL::search(string word) {
	search(root, word);
}

bool AVL::search(AvlNode* node, string word) {
	if(node == NULL) {
		return false;
	} 
	if(word.compare(node->word) > 0) {
		return search(node->right, word);
	} else if(word.compare(node->word) < 0) {
		return search(node->left, word);
	} else {
		return true;
	}
}



/**
* Return the height of a node t or -1 if nullptr
*/
int AVL::height(AvlNode *t) const {
	return t == nullptr ? -1 : t->height;
}
/**
* Internal method to insert into a subtree
* x is the item to insert
* t is the node that roots the subtree
* Set the new root of the subtree
*/
void AVL::insert(const string & x, AvlNode * & t) {
	if (t == nullptr)
		t = new AvlNode(x, nullptr, nullptr);
	else if (x < t->element)
		insert(x, t->left);
	else if (t->element < x)
		insert(x, t->right);
	balance(t);
}
static const int ALLOWED_IMBALANCE = 1;
// Assume t is balanced or within one of being balanced
void AVL::balance(AvlNode * & t) {
	if (t == nullptr)
		return;
	if (height(t->left) – height(t->right) > ALLOWED_IMBALANCE)
		if (height(t->left->left) >= height(t->left->right))
			rotateWithLeftChild(t);
		else
			doubleWithLeftChild(t)
	else if (height(t->right) – height(t->left) > ALLOWED_IMBALANCE)
		if (height(t->right->right) >= height(t->right->left))
			rotateWithRightChild(t);
		else
			doubleWithRightChild(t);

	t->height = max(height(t->left), height(t->right)) + 1;
}
/**
* Rotate binary tree node with left child
* For AVL trees, this is a single rotation for case 1
* Update heights, then set new root
*/
void AVL::rotateWithLeftChild(AvlNode * & k2) {
	AvlNode *k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left, k2->height)) + 1;
	k2 = k1;
}
/**
* Double rotate binary tree node: fist left child with its right child;
* then node k3 with new left child
* For AVL trees, this is a double rotation for case 2
* Update heights, then set new root
*/
void AVL::doubleWithLeftChild(AvlNode * & k3) {
	rotateWithRightChild(k3->left);
	rotateWithLeftChild(k3);
}
/**
* Rotate binary tree node with left child
* For AVL trees, this is a single rotation for case 1
* Update heights, then set new root
*/
void AVL::rotateWithRightChild(AvlNode * & k2) {
	AvlNode *k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;
	k2->height = max(height(k2->left), height(k2->right)) + 1;
	k1->height = max(height(k1->left, k2->height)) + 1;
	k2 = k1;
}
/**
* Double rotate binary tree node: fist left child with its right child;
* then node k3 with new left child
* For AVL trees, this is a double rotation for case 2
* Update heights, then set new root
*/
void AVL::doubleWithRightChild(AvlNode * & k3) {
	rotateWithLeftChild(k3->right);
	rotateWithRightChild(k3);
}

/**
* Internal method to remove from a subtree
* x is the item to remove
* t is the node that roots the subtree
* Set the new root of the subtree
*/
void AVL::remove(const string & x, AvlNode *& t) {
	if (t == nullptr)
		return; // item not found; do nothing
	if (x < t->element)
		remove(x, t->left);
	else if (t->element < x)
		remove(x, t->right);
	else if (t->left != nullptr && t->right != nullptr) { // two children
		t->element = findMin(t->right)->element;
		remove(t->element, t->right);
	}
	else {
		AvlNode *oldNode = t;
		t = (t->left != nullptr) ? t->left : t->right;
		delete oldNode;
	}
	balance(t);
}



void AVL::sort() {
  ofstream outFile;
  outFile.open("output.txt");
  sort(root, outFile);
  outFile << endl;
  outFile.close();
}

void AVL::sort(AvlNode* node, ofstream& outFile) {
  if (node == NULL)
    return;
  sort(node->left, outFile);
  outFile << node->word << endl;
  sort(node->right, outFile);
}

void AVL::rangeSearch(string startWord, string endWord) {
  rangeSearch(root, startWord, endWord);
}

void AVL::rangeSearch(AvlNode* node, string startWord, string endWord) {
  if (node == NULL)
    return;
  if (startWord < node->word)
    rangeSearch(node->left, startWord, endWord);
  if (startWord <= node->word && endWord >= node->word)
    cout << node->word << endl;
  if (endWord > node->word)
    rangeSearch(node->right, startWord, endWord);
}

int AVL::countWords() {
  return countWords(root);
}

int AVL::countWords(AvlNode* node) {
  int count = 0;
  if (node == NULL)
    return 0;
  count += countWords(node->left);
  count += 1;
  count += countWords(node->right);
  return count;
}

void AVL::destroyTree() {
  destroyTree(root);
}


void AVL::destroyTree(AvlNode* node) {
  if(node != NULL) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}




