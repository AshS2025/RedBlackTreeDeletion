#include <iostream>

class Node {
public:

  Node();
  Node(int Data);
  
  void setLeft(Node* Left);
  Node* getLeft();

  void setRight(Node* Right);
  Node* getRight();

  void setParent(Node* Parent);
  Node* getParent();

  void setData(int Data);
  int getData();

  void setColor(char Color);
  char getColor();

  Node* getSibling();
  Node* getGrandparent();
  Node* getUncle();
  
 private:
  Node* left;
  Node* right;
  Node* parent;
  int data;
  char color;
};
