#include <iostream>
#include "node.h"

Node:: Node(){
  right = NULL;
  left = NULL;
  parent = NULL;
}

Node:: Node(int Data){
  data = Data;
  right = NULL;
  left = NULL;
  parent = NULL;
}

int Node:: getData(){
  return data;
}

void Node:: setData(int Data){
  data = Data;
}

Node* Node:: getRight(){
  return right;
}

void Node:: setRight(Node* Right){
  right = Right;
}

Node* Node:: getLeft(){
  return left;
}

void Node:: setLeft(Node* Left){
  left = Left;
}

Node* Node:: getParent(){
  return parent;
}

void Node:: setParent(Node* Parent){
  parent = Parent;
}

void Node:: setColor(char Color){
  color = Color;
}

char Node:: getColor(){
  return color;
}



//additional calculated getters

Node* Node:: getSibling(){
  if (this->getParent()->getLeft() == this){
    Node* toReturn = this->getParent()->getRight();
    return toReturn;
  }

  else if (this->getParent()->getRight() == this){
    Node* toReturn = this->getParent()->getLeft();
    return toReturn;
  }
  return NULL;
}

Node* Node:: getGrandparent(){
  Node* grandparent = this->getParent()->getParent();
  return grandparent;
}

Node* Node:: getUncle(){
  if (this->getParent()->getParent()->getRight() == this->getParent()){
    Node* uncle = this->getParent()->getParent()->getLeft();
    return uncle;
  }

  else if (this->getParent()->getParent()->getLeft() == this->getParent()){
    Node* uncle = this->getParent()->getParent()->getRight();
    return uncle;
  }
  return NULL;
}
