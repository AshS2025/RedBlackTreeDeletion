#include <iostream>
#include <cstring>
#include "node.h"
#include <vector>
#include <fstream>

using namespace std;

void fixViolations(Node*&, Node*);
void leftGrandRotation(Node* &, Node*);
void rightGrandRotation(Node* &, Node*);
void rightParentRotation(Node*);
void leftParentRotation(Node*);
void addNode(Node*&, Node*, Node*);
void printTree(Node*, int);

void removeNode(Node* current);
void fixDeleteTree (Node* current, bool&);
void deletebyCase(Node* current, bool& deleted);
void swap(Node*, Node*);
Node* findDeleteNode(Node*, Node*, int);
Node* findSuccessor(Node*);


void caseTwoDeletion(Node*, bool&);
void caseThreeDeletion(Node*, bool&);
void caseFourDeletion(Node*, bool&);
void caseFiveDeletion(Node*, bool&);
void caseSixDeletion(Node*, bool&);

void caseOneInsertion(Node* &, Node*);
void caseTwoInsertion(Node* &, Node*);
void caseThreeInsertion(Node*&, Node*);
void caseFourInsertion(Node*&, Node*);
void caseFiveInsertion(Node* &, Node*);

int main(){

  Node* root = NULL;
  cout << "welcome to RedBlackTree!!!" << endl;
  bool running = true;

  while (running == true){
 
  cout << "what do you want to do? type ADD, DELETE, PRINT, or QUIT" << endl;
  char command[10];
  cin >> command;

  if (strcmp(command, "QUIT") == 0){
    running = false;
  }

  if (strcmp(command, "PRINT") == 0){
    printTree(root, 0);
  }

  if (strcmp(command, "DELETE") == 0){
    cout << "what number do you want to delete?" << endl;
    int toDelete;
    cin >> toDelete;
    Node* current = findDeleteNode(root, root, toDelete);
    cout << current->getData() << endl;
    cout << "found the node" << endl;
    bool deleted = false;
    fixDeleteTree(current, deleted);
  }
  
  if (strcmp(command, "ADD") == 0){
    //add node stuff
      cout << "would you like to add manually or by file? type m or f." << endl;
    char inputType;
    cin >> inputType;

    if (inputType == 'f'){
      //did this with help from vikram

       vector<int> input;
       fstream first_stream;
       first_stream.open("numbers.txt");
       int num;
       while(first_stream >> num){
       input.push_back(num);
        }
       vector <int> ::iterator iter = input.begin();
       for(iter = input.begin(); iter < input.end(); iter++){
       Node* newNode = new Node();
       newNode->setData(*iter);
       addNode(root, root, newNode);
       }
   
  }
     else {
      //manual string of numbers
      cout << "how many numbers do you want to enter?" << endl;
      int numOfNums;
      cin >> numOfNums;

      cout << "enter each number as you are prompted" << endl;

      //im too lazy to make a vector or break at spaces so users will have to enter one by one

      for (int i = 0; i < numOfNums; i++) {
        int entry;
        cout << "enter a number" << endl;
        cin >> entry;
        Node* newNode = new Node();
        newNode->setData(entry);
        addNode(root, root, newNode);
      }

      //  cout << "all numbers have been added" << endl;
    }

    //else statement about manual insertion

  }
  
 }
  
}



void printTree(Node* current, int count){
    if(current->getRight() != NULL){
      //count = count + 1;
        printTree(current->getRight(), count+1);
    }
    for(int i = 0; i < count; i++){
        cout << '\t';
    }

    int temp = current->getData();
    char color = current->getColor();
    cout << temp << color << endl;
    
    if(current->getLeft() != NULL){
      //count = count + 1;
        printTree(current->getLeft(), count+1);
    }

}


void addNode(Node* &root, Node* current, Node* newNode){

  if (root == NULL){ //added node is root
    root = newNode; 
    //newNode->setColor('b'); //node must always be black
    fixViolations(root, newNode);
  }

  else if (newNode->getData() < current->getData()){
    /*
      if added node is smaller than current, check if left is null
      if left is null then set the left as the newnode
      else recursion
     */
    if (current->getLeft() == NULL){
      current->setLeft(newNode);
      newNode->setParent(current);
      newNode->setColor('r');
      //cout << "added left" << endl;
      //cout << "going to fix violations. still in addnode" << endl;
      fixViolations(root, newNode);
      

    }
    else{
      current = current->getLeft();
      addNode(root, current, newNode);
    }
  }

  else if (newNode->getData() >= current->getData()){
    if (current->getRight() == NULL){
      current->setRight(newNode);
      newNode->setParent(current);
      newNode->setColor('r');
      //cout << "added right" << endl;
      //cout << "going to fix violations. still in addnode" << endl;
      fixViolations(root, newNode);
    
    }
    else {
      current = current->getRight();
      addNode(root, current, newNode);
    }
  }

}

void caseOneInsertion(Node*&root, Node* newNode){
  //cout << "in case 1 function" << endl;
  newNode->setColor('b');
  //cout << "root color has been set to black" << endl;
    //fixViolations(root, newNode);
}

void caseTwoInsertion(Node*&root, Node* newNode){
  //cout << "we're done nothing to do yay!" << endl;
}

void caseThreeInsertion(Node*&root, Node* newNode){
  Node* tempParent = newNode->getParent();
  Node* tempUncle = newNode->getUncle();
  Node* tempGrandparent = newNode->getGrandparent();

  tempParent->setColor('b');
  tempUncle->setColor('b');
  //tempGrandparent->setColor('r');
  //fixViolations(root, tempGrandparent);
}

void caseFourInsertion(Node*&root, Node* newNode){
  //cout << "getting inside casefour insertion function" << endl;
  if ((newNode->getGrandparent()->getRight() == newNode->getParent()) && (newNode->getParent()->getLeft() == newNode)){
    //right rotation
    rightParentRotation(newNode);
    caseFiveInsertion(root, newNode->getRight());
  }
  if ((newNode->getGrandparent()->getLeft() == newNode->getParent()) && (newNode->getParent()->getRight() == newNode)){
    leftParentRotation(newNode);
    caseFiveInsertion(root, newNode->getLeft());
  }

 
}

void caseFiveInsertion(Node*&root, Node* newNode){
  //cout << "getting inside casefive insertion function" << endl;
  if (newNode->getGrandparent()->getRight() == newNode->getParent() && newNode->getParent()->getRight() == newNode){
    leftGrandRotation(root, newNode);
  }

  if (newNode->getGrandparent()->getLeft() == newNode->getParent() && newNode->getParent()->getLeft() == newNode){
    rightGrandRotation(root, newNode);
  }
  
  //fixViolations(root, newNode->getSibling());
 
}

void fixViolations(Node* &root, Node* newNode){

  //cout << "getting into fixViolations" << endl;

  //case 1: root
  if (root == newNode){ 
    caseOneInsertion(root, newNode);
    return;
  }

  //case 2: black parent
  if (newNode->getParent()->getColor() == 'b'){
    caseTwoInsertion(root, newNode);
  }
  
  //case 3: parent and uncle are red
  /*  cout << "parent:" << newNode->getParent()->getData() << endl;
  if (newNode->getUncle() != NULL){
  cout << "uncle; " << newNode->getUncle()->getData() << endl;
  }
  else {
    cout << "uncle is null (which means its black!)" << endl;
  }
  */
  if ((newNode->getParent()->getColor() == 'r') && (newNode->getUncle() != NULL) && (newNode->getUncle()->getColor() == 'r')){
    caseThreeInsertion(root, newNode);
  }


  //case 4: uncle is black and triangle
  if ((newNode->getParent()->getColor() == 'r') && ((newNode->getUncle() == NULL)||(newNode->getUncle()->getColor() == 'b'))){
    //cout << "getting into black uncle cases" << endl;
    
    if (((newNode->getGrandparent()->getRight() == newNode->getParent()) && (newNode->getParent()->getLeft() == newNode))
      || ((newNode->getGrandparent()->getLeft() == newNode->getParent()) && (newNode->getParent()->getRight() == newNode)))
      {
	//	cout << "in fixbioaltions right before case Four cfunction call" << endl;
	caseFourInsertion(root, newNode);
      } 
  

  //case 5:
    /*    cout << "newNode: " << newNode->getData() << endl;
    cout << "parent: " << newNode->getParent()->getData() << endl;
    cout << "parent right: " << newNode->getParent()->getRight()->getData() << endl;
    cout << "parent's parent: " << newNode->getParent()->getParent()->getData() << endl;
    cout << "newNode's grandparent: " << newNode->getGrandparent()->getData() << endl;
    cout << "grandparent right: " << newNode->getGrandparent()->getRight()->getRight()->getData() << endl;
    */
  if (((newNode->getGrandparent()->getRight() == newNode->getParent()) && (newNode->getParent()->getRight() == newNode)) || (newNode->getGrandparent()->getLeft() == newNode->getParent()) && (newNode->getParent()->getLeft() == newNode)){
    //cout << "in fix violations right before case five function call" << endl;
    caseFiveInsertion(root, newNode);
    return;
  }

  } //end of color conditions loop
    

  //only check if two reds in a row -- 
  

}

void rightParentRotation(Node* newNode){ //parent is a right child, newNode is a left child
  /*
    newNode becomes right child of grandparent
    parent becomes right child of newNode
    old sibling (right child of parent) becomes left child of newNode
   */
  //cout << "in right parent rotation" << endl;
  Node* temp = newNode->getParent(); //parent
  Node* tempTwo = newNode; //itself
  Node* tempThree = newNode->getSibling(); //sibling
  Node* tempFour = newNode->getGrandparent(); //grandparent
  Node* tempFive = newNode->getRight();
  
  if (tempFour->getLeft() == temp){
    tempFour->setLeft(tempTwo);
  }

  else if (tempFour->getRight() == temp){
    tempFour->setRight(tempTwo);
  }

  tempTwo->setParent(tempFour);
    temp->setParent(newNode);
  newNode->setRight(temp);
  temp->setParent(newNode);
  
  newNode->setParent(tempFour);
  if (tempThree != NULL){
    tempThree->setParent(temp);
  }
  temp->setRight(tempThree);


  if (tempFive != NULL){
    tempFive->setParent(temp);
  }
  temp->setLeft(tempFive);
  //temp->setParent(newNode);
  
}

void leftParentRotation(Node* newNode){
  /*
    newNode becomes left child of grandparent
    parent becomes left child of newnode
    sibling becomes right child of newnode 
  */
  //cout << "in left parent rotation" << endl;
  Node* temp = newNode->getParent(); //parent
  Node* tempTwo = newNode; //itself
  Node* tempThree = newNode->getSibling(); // sibling
  Node* tempFour = newNode->getGrandparent(); //grandparent
  Node* tempFive = newNode->getLeft();
  
  if (tempFour->getLeft() == temp){
    tempFour->setLeft(tempTwo);
  }

  else if (tempFour->getRight() == temp){
    tempFour->setRight(tempTwo);
  }
  tempTwo->setParent(tempFour);
  temp->setParent(newNode);
  newNode->setLeft(temp); //set parent as left child of newnode
  //newNode->setRight(tempThree); //set right child of newnode to the old sibling
  newNode->setParent(tempFour); //set parent of newnode to grandparent

  
  if (tempThree != NULL){
    tempThree->setParent(temp); //parent of old sibling is new node
    //temp->setRight(tempThree);
  }
  temp->setLeft(tempThree);

  if (tempFive != NULL){
  tempFive->setParent(temp);
  }
  temp->setRight(tempFive);
  
} 

void leftGrandRotation(Node* &root, Node* newNode){
  //cout << "got into left grand" << endl;
  Node* temp = newNode->getParent(); //parent
  Node* tempTwo = newNode; //itself
  Node* tempThree = newNode->getSibling(); //sibling
  Node* tempFour = newNode->getGrandparent(); //grandparent
  Node* tempFive = newNode->getUncle(); //uncle
  Node* tempSix = newNode->getGrandparent()->getParent();
  
  //cout << "nodes are being set" << endl;
  temp->setLeft(tempFour); //old grandparent becomes child of old parent
  tempFour->setParent(temp); //setting parent for above line
  tempFour->setRight(tempThree); //old sibling becomes right of old grandparent
  if (tempThree != NULL){
    tempThree->setParent(tempFour); //setting parent for above line
  }

    if (tempSix != NULL){
    tempSix->setRight(temp);
    temp->setParent(tempSix);
  }


  temp->getRight()->setLeft(NULL);
  
  temp->setColor('b');
  tempFour->setColor('r');
  //cout << "nodes have been recolored" << endl;
  //cout << "current root: " << root->getData() << endl;
  if (root == tempFour){
    root = newNode->getParent();
    //cout << "new root: " << root->getData() << endl;
  }
}


  
void rightGrandRotation(Node* &root, Node* newNode){
  //cout << "got into left grand" << endl;
  Node* temp = newNode->getParent(); //parent
  Node* tempTwo = newNode; //itself
  Node* tempThree = newNode->getSibling(); //sibling
  Node* tempFour = newNode->getGrandparent(); //grandparent
  Node* tempFive = newNode->getUncle(); //uncle
  Node* tempSix = newNode->getGrandparent()->getParent();

  //cout << "nodes are being set" << endl;
  temp->setRight(tempFour); //old grandparent becomes child of old parent
  tempFour->setParent(temp); //setting parent for above line
  tempFour->setLeft(tempThree); //old sibling becomes right of old grandparent
  if (tempThree != NULL){
    tempThree->setParent(tempFour); //setting parent for above line
  }

  if (tempSix != NULL){
    if (tempSix->getRight() == tempFour){
      tempSix->setRight(temp);
      temp->setParent(tempSix);
    }
    else {
    tempSix->setLeft(temp);
    temp->setParent(tempSix);
    }
  }

  temp->getLeft()->setRight(NULL);

  temp->setColor('b');
  tempFour->setColor('r');
  //cout << "nodes have been recolored" << endl;
  //cout << "current root: " << root->getData() << endl;
  if (root == tempFour){
    root = newNode->getParent();
    //cout << "new root: " << root->getData() << endl;
  }
}


//vikram helped me rewrite my removeNode function
void removeNode(Node* current){
    if (current->getRight() == NULL && current->getLeft() == NULL){
      cout << "in this if statement" << endl;
      if (current->getParent() != NULL){
	if (current->getParent()->getLeft() == current){
	current->getParent()->setLeft(NULL);
      }
	else if (current->getParent()->getRight() == current){
	current->getParent()->setRight(NULL);
      }
    }
    
    delete current;
    //if there are no children just set the parent's child to null and delete
  }

  else if (current->getLeft() == NULL){
    if(current->getParent()->getLeft() == current){
      current->getParent()->setRight(current->getRight());
    }

    else if (current->getParent()->getRight() == current){
	current->getParent()->setLeft(current->getRight());
    }
    
    current->getRight()->setParent(current->getParent());
    delete current;

    //if there is a right child, set the right child as the child of the parent
  }

  else if (current->getRight() == NULL){
    if (current->getParent()->getLeft() == current){
      current->getParent()->setLeft(current->getLeft());
    }
    else if (current->getParent()->getRight() == current){
      current->getParent()->setRight(current->getLeft());
    }

    current->getLeft()->setParent(current->getParent());
    delete current;

    //if there's a left child, set the left child as the child of the parent
  }

  else {
    Node* temp = current->getRight();
    int count = 0;
    while (temp->getLeft() != NULL){
      temp = temp->getLeft();
      count++;
    }

    current->setData(temp->getData());

    if (count == 0){
      current->setRight(temp->getRight());
      temp->getParent()->setRight(temp->getRight());
      temp->getRight()->setParent(temp->getParent());
    }

    else {
      temp->getParent()->setLeft(temp->getRight());
      temp->getRight()->setParent(temp->getParent());
    }

    delete temp;

    //if there are two children, find the smallest on the right side of the tree and set it 
  }

  }



void fixDeleteTree(Node* current, bool &deleted){
  cout << "inside fixDeleteTree" << endl;
  cout << current->getData() << endl;
  
  //if current is black and right child is red (and one child)
  if (current->getColor() == 'b' && current->getRight() != NULL && current->getRight()->getColor() == 'r' && current->getLeft() == NULL){
    cout << "inside the if statement" << endl;
    current->getRight()->setColor('b');
    removeNode(current); //add parameters
  }

  //if current is black and left child is red (and one child)
  if (current->getColor() == 'b' && current->getLeft() != NULL && current->getLeft()->getColor() == 'r' && current->getRight() == NULL){
    current->getLeft()->setColor('b');
    removeNode(current); // add parameters
  }

  //if current red and one child
  if (current->getColor() == 'r' && current->getLeft() != NULL && current->getRight() == NULL){
    removeNode(current); //add parametes
  }

  if (current->getColor() == 'r' && current->getRight() != NULL && current->getLeft() == NULL){
    removeNode(current); //add parameters
  }

  //if two children
  if (current->getRight() != NULL && current->getLeft() != NULL){
    Node* successor = findSuccessor(current); 
    swap(current, successor); //add parameters
    fixDeleteTree(successor, deleted); //call on successor
  }

  if (current->getColor() == 'b' && current->getLeft() == NULL && (current->getRight() == NULL || current->getRight()->getColor() == 'b')){
    cout << "getting inside bb if statement" << endl;
    deletebyCase(current, deleted);

  }

}

void deletebyCase(Node* current, bool &deleted){   

//case 2
  if (current->getParent()->getColor() == 'b' && current->getSibling()->getColor() == 'r' && (current->getSibling()->getRight() == NULL || current->getSibling()->getRight()->getColor() == 'b') && (current->getSibling()->getLeft() == NULL || current->getSibling()->getLeft()->getColor() == 'b')){
  caseTwoDeletion(current, deleted);
 }

//case 3
  if (current->getParent()->getColor() == 'b' && current->getSibling()->getColor() == 'b' && (current->getSibling()->getRight() == NULL || current->getSibling()->getRight()->getColor() == 'b') && (current->getSibling()->getLeft() == NULL || current->getSibling()->getLeft()->getColor() == 'b')){
      caseThreeDeletion(current, deleted); //add parameters
    }
    
    //case 4
    if (current->getParent()->getColor() == 'r' && current->getSibling()->getColor() == 'b' && (current->getSibling()->getRight() == NULL || current->getSibling()->getRight()->getColor() == 'b') && (current->getSibling()->getLeft() == NULL || current->getSibling()->getLeft()->getColor() == 'b')) {
      caseFourDeletion(current, deleted); //add parameters
    }

//case 5

    if (((current->getSibling()->getData() > current->getData()) && (current->getParent()->getColor() == 'b' && current->getSibling()->getColor() == 'b' && current->getSibling()->getLeft()->getColor() == 'r' && (current->getSibling()->getRight() == NULL || current->getSibling()->getRight()->getColor() == 'b'))) || ((current->getSibling()->getData() < current->getData()) && (current->getParent()->getColor() == 'b' && current->getSibling()->getColor() == 'b' && current->getSibling()->getRight()->getColor() == 'r' && (current->getSibling()->getLeft() == NULL || current->getSibling()->getLeft()->getColor() == 'b')))) {
      cout << "inside case 5 if statement" << endl;
  caseFiveDeletion(current, deleted);
 }


  //case 6

if (((current->getSibling()->getData() > current->getData()) && (current->getSibling()->getColor() == 'b' && current->getSibling()->getRight()->getColor() == 'r')) || ((current->getSibling()->getData() < current->getData()) && (current->getSibling()->getColor() == 'b' && current->getSibling()->getLeft()->getColor() == 'r'))){
  caseSixDeletion(current, deleted);
 }

}



void caseTwoDeletion(Node* current, bool &deleted){
  if (current->getSibling()->getData() > current->getData()){
    //if double black is the left child
    Node* tempS = current->getSibling();
    Node* tempP = current->getParent();
    leftParentRotation(current);
    tempS->setColor('b');
    tempP->setColor('r');
  }

  else if (current->getSibling()->getData() < current->getData()){
      //if double black is the right child
    Node* tempS = current->getSibling();
    Node* tempP = current->getParent();
    rightParentRotation(current);
    tempS->setColor('b');
    tempP->setColor('r');
    }

  deletebyCase(current, deleted);
}



void caseThreeDeletion(Node* current, bool &deleted){
  current->getSibling()->setColor('r');
  Node* temp = current->getParent();
  if (deleted == false){
    removeNode(current); //add parameters
    deleted = true;
  }
  deletebyCase(temp, deleted);
}

void caseFourDeletion(Node* current, bool &deleted){ //add parameters
  current->getParent()->setColor('b');
  current->getSibling()->setColor('r');
  if (deleted == false){
  removeNode(current); //add parameters --> deleting sucesssor (which should be current)
  deleted = true;
  }
}

void caseFiveDeletion(Node* current, bool &deleted){
  cout << "inside case 5 function" << endl;
  if (current->getSibling()->getData() > current->getData()){
    //double black = left child
    cout << "double black is left child" << endl;
    Node* tempS = current->getSibling();
    Node* tempX = current->getSibling()->getLeft();
    rightParentRotation(current->getSibling()->getLeft());
    tempS->setColor('r');
    tempX->setColor('b');
  }

  else if (current->getSibling()->getData() < current->getData()){
    //double black = right child
    Node* tempS = current->getSibling();
    Node* tempX = current->getSibling()->getRight();
    leftParentRotation(current->getSibling()->getRight());
    tempS->setColor('r');
    tempX->setColor('b');
  }
}

void caseSixDeletion(Node* current, bool &deleted){
  cout << "current in case 6 " << current->getData() << endl;
  cout << "inside case 6 function" << endl;
  if (current->getSibling()->getData() > current->getData()){
    //if double black is the left child
    Node* tempRY = current->getSibling()->getRight();
    Node* tempP = current->getParent();
    leftParentRotation(current->getSibling());
    tempRY->setColor('b');
    tempP->setColor('b');
  }

  else if (current->getSibling()->getData() < current->getData()){
    //if double black is the right child
    Node* tempRY = current->getSibling()->getLeft();
    Node* tempP = current->getParent();
    rightParentRotation(current->getSibling());
    tempRY->setColor('b');
    tempP->setColor('b');
  }

  if (deleted == false){
    cout << "getting before remove node" << endl;
    removeNode(current); //add parameters
    cout << "node has been removed" << endl;
  deleted = true;
  }
}
  

Node* findSuccessor(Node* current){

  if (current->getRight()!= NULL){
  
  Node* temp = current->getRight();
  while (temp->getLeft() != NULL){
    temp = temp->getLeft();
  }

  return temp;
}
  else if (current->getLeft() != NULL && current->getRight() == NULL){
    return current->getLeft();
  }

  else if (current->getLeft() == NULL && current->getRight() == NULL){
    return NULL;
  }

  else{
    return NULL;
  }
}


Node* findDeleteNode(Node* root, Node* current, int toDelete){
  if (current->getData() == toDelete){
    return current;
  }

  else if (current->getData() > toDelete){
    findDeleteNode (root, current->getLeft(), toDelete);
  }

  else if (current->getData() < toDelete){
    findDeleteNode(root, current->getRight(), toDelete);
  }

  else {
    return NULL;
  }

}

void swap(Node* current, Node* successor){
  //puts the data value of the successor into the current
  int replacement = successor->getData();
  current->setData(replacement);
}
