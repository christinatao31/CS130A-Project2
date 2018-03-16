#include "AVL.h"
#include <iostream>
#include <string>
#include <algorithm>

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
void AVL::printInorder(Node* node) {
	if(node == NULL) return;
	printInorder(node->left);
	cout << node->word << endl;
	printInorder(node->right);
}

bool AVL::search(string word) {
	search(root, word);
}

bool AVL::search(Node* node, string word) {
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

int AVL::height(Node* node) {
	if(node == NULL)
		return 0;
	return node->height;
}
int AVL::getDiff(Node* node) {
	if(node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}
void AVL::rightRotate(Node*& z) {
	Node* y = z->left;
	Node* T3 = y->right;
	y->right = z;
	z->left = T3;

	y->height = 1 + max(height(y->left), height(y->right));
	z->height = 1 + max(height(z->left), height(z->right));
}
void AVL::leftRotate(Node*& z) {
	Node* y = z->right;
	Node* T3 = y->left;
	y->left = z;
	z->right = T3;

	y->height = 1 + max(height(y->left), height(y->right));
	z->height = 1 + max(height(z->left), height(z->right));
}

void AVL::insert(string word) {
	insert(root, word);
}

void AVL::insert(Node*& node, string word) {
	/* 1.  Perform the normal BST insertion */
	if(node == NULL) {
		Node* newNode = new Node(word);
		node = newNode;
	}
	if(word.compare(node->word) > 0) {
		insert(node->right, word);
	} else if(word.compare(node->word) < 0) {
		insert(node->left, word);
	} else {
		node->wordCount = node->wordCount + 1;
	}

	/* 2. Update height of this ancestor node (called recursively) */
	node->height = 1 + max(height(node->left), height(node->right));

	 /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
	int diff = getDiff(node);
 
    // Left Left Case
	if(diff > 1 && word < node->left->word) {
		rightRotate(node);
	}
	// Right Right Case
	if(diff < -1 && word > node->left->word) {
		leftRotate(node);
	}
	// Left Right Case
	if(diff > 1 && word > node->left->word) {
		leftRotate(node->left);
		rightRotate(node);
	}
    // Right Left Case
	if(diff < -1 && word < node->left->word) {
		rightRotate(node->right);
		leftRotate(node);
	}
}

void AVL::deleteWord(string word) {
	deleteWord(root, word);
}

void AVL::deleteWord(Node*& node, string word) {
	if (node == NULL) return;
	if(word.compare(node->word) < 0) {
		deleteWord(node->left, word);
	else if(word.compare(node->word) > 0) 
		deleteWord(node->right, word);
	else {
		if(node->wordCount > 1)
			node->wordCount = node->wordCount - 1;
		else {
			if(node->left == NULL) {
				Node* temp = node;
				node = node->right;
				delete temp;
			} else if(node->right == NULL) {
				Node* temp = node;
				node = node->left;
				delete temp;
			} else {
				Node* temp = node;
				while(temp->right != NULL)
					temp = temp->right;
				node->word = temp->word;
				delete temp;
			}
		}
	}
	if(root == NULL) return;

	node->height = 1 + max(height(node->left), height(node->right));
	int diff = getDiff(node);

	// Left Left Case
	if(diff > 1 && word < node->left->word) {
		rightRotate(node);
	}
	// Right Right Case
	if(diff < -1 && word > node->left->word) {
		leftRotate(node);
	}
	// Left Right Case
	if(diff > 1 && word > node->left->word) {
		leftRotate(node->left);
		rightRotate(node);
	}
    // Right Left Case
	if(diff < -1 && word < node->left->word) {
		rightRotate(node->right);
		leftRotate(node);
	}
}

void BST::sort() {
  ofstream outFile;
  outFile.open("output.txt");
  sort(root, outFile);
  outFile << endl;
  outFile.close();
}

void AVL::sort(Node* node, ofstream& outFile) {
  if (node == NULL)
    return;
  sort(node->left, outFile);
  outFile << node->word << endl;
  sort(node->right, outFile);
}

void AVL::rangeSearch(string startWord, string endWord) {
  rangeSearch(root, startWord, endWord);
}

void AVL::rangeSearch(Node* node, string startWord, string endWord) {
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

int AVL::countWords(Node* node) {
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


void AVL::destroyTree(Node* node) {
  if(node != NULL) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
  }
}




