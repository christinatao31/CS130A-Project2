#include "Node.h"
#include <string>

using namespace std;

// constructor
Node::Node(string word) {
  word = word;
  count = 1;
  next = NULL;
  left = NULL;
  right = NULL;
}

// destructor
Node::~Node() {

}

Node* Node::getNext() {
  return next;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

string Node::getWord() {
  return word;
}

int Node::getWordCount() {
  return count;
}

int Node::getIndex() {
  return index;
}

void Node::incrementCount() {
  count++;
}
