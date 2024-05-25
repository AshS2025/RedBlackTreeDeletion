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
void removeNode(int direction, Node* current, int value);

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
    removeNode(0, root, toDelete);
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
  tempFour->setRight(tempTwo); //set itself to child of grandparent
  newNode->setRight(temp); //set parent as right child of newnode
  newNode->setLeft(tempThree); //set left child to the old sibling
  newNode->setParent(tempFour);
  if (tempThree != NULL){
  tempThree->setParent(newNode);
  }
  temp->setParent(newNode);
  
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
  tempFour->setLeft(tempTwo); //set itself to left child to grandparent
  newNode->setLeft(temp); //set parent as left child of newnode
  newNode->setRight(tempThree); //set right child of newnode to the old sibling
  newNode->setParent(tempFour); //set parent of newnode to grandparent
  if (tempThree != NULL){
  tempThree->setParent(newNode); //parent of old sibling is new node
  }
  temp->setParent(newNode); //set parent of old parent to new node
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

//void removeNode(int direction, Node* current sdf


/*
void removeNode(Node* &root, Node* current, int value){
  //root
  if (root->getData() == value){
    //root has no children
    if(root->getRight() == NULL && root->getLeft() == NULL){
      delete root;
    }

    //one child - right child
    else if (root->getRight() != NULL && root->getLeft() == NULL){
      Node* temp = root->getRight();
      delete root;
      root = temp;
    }

    //one child - left child
    else if (root->getLeft() != NULL && root->getRight() == NULL){
      Node* temp = root->getLeft();
      delete root;
      root = tempNode;
    }


    //two children
    else if (root->getRight() != NULL && root->getLeft() != NULL){
      //fidn smallest value on right side
      Node* temp = root->getRight();
      while(tempNode->getLeft() != NULL){
	temp = temp->getLeft();
      }
      Node* tempTwo = new Node();
      tempTwo->setData(temp->getData());
      remove(root, root, temp->getData());
      tempTwo->setLeft(root->getLeft());
      tempTwo->setRight(root->getRight());
      root = tempTwo;
    }


   }

  else if (current->getData() > value){
    
    if(current->getLeft()->getData() != value){
      removeNode (root, current->getLeft(), value);
      
    }

    else{

      if(current->getLeft()->getLeft() == NULL && current->getLeft()->getRight() == NULL){
	delete current->getLeft();
	current->setLeft(NULL);
      }

      else if (current->getLeft()->getLeft() != NULL && current->getLeft()->getRight() == NULL){
	Node* temp = current->getLeft()->getLeft();
	delete current->getLeft();
	current->setLeft(temp);
      }

      else if (current->getLeft()->getLeft() == NULL && current->getLeft()->getRight() != NULL){
	Node* temp = current->getLeft()->getLeft();
	delete current->getLeft();
	current->setLeft(temp);
	
      }

      else if (current->getLeft()->getLeft() != NULL && current->getLeft()->getRight() != NULL){
	Node* temp = current->getLeft()->getLeft();
	while (temp->getRight() != NULL){
	  temp = temp->getRight();
	}

	Node* tempTwo = new Node();
	tempTwo->setData(temp->getData());
	removeNode(root, current, temp->getData());
	tempTwo->setLeft(current->getLeft()->getLeft());
	tempTwo->setRight(current->getLeft()->getRight());
	current->setLeft(tempTwo);
      }
    }


   }

  //same as above but different direction

  else if (current->getData() < value){
    if(current->getRight()->getData() ! = value){
      removeNode(root, current->getRight(), value);
    }

    else {
      if (current->getRight()->getLeft() == NULL && current->getRight()->getRight() == NULL){
	delete current->getRight();
	current->setRight(NULL);
      }

      else if (current->getRight()->getLeft() != NULL && current->getRight()->getRight() == NULL){
	Node* temp = current->getRight()->getLeft();
	delete current->getRight();
	current->setRight(temp);
      }

      else if (current->getRight()->getLeft() == NULL && current->getRight()->getRight() != NULL){
	Node* temp = current->getRight()->getRight();
	wdelete current->getRight();
	current->setRight(temp);
      }

      else if (current->getRight()->getLeft() != NULL && current->getRight()->getRight() != NULL){
	Node* temp = current->getRight()->getRight();
	while(temp->getLeft() != NULL){
	  temp = temp->getLeft();
	}

	Node* tempTwo = new Node();
	tempTwo->setData(temp->getData());
	removeNode(root, current, temp->getData());
	tempTwo->setLeft(current->getRight()->getLeft());
	tempTwo->setRight(current->getRight()->getRight());
	current->setRight(tempTwo);
      }
    }
  }

  }

*/
//vikram helped me rewrite my removeNode function
void removeNode(int direction, Node* current, int toDelete){
  if (current->getData() == toDelete){
    if (current->getRight() == NULL && current->getLeft() == NULL){
      if (current->getParent() != NULL){
      if (direction == 0){
	current->getParent()->setLeft(NULL);
      }
      else if (direction == 1){
	current->getParent()->setRight(NULL);
      }
    }
    
    delete current;
  }

  else if (current->getLeft() == NULL){
    if(direction == 0){
      current->getParent()->setRight(current->getRight());
    }

    else if (direction == 1){
      current->getParent()->setLeft(current->getRight());
    }
    current->getRight()->setParent(current->getParent());
    delete current;
  }

  else if (current->getRight() == NULL){
    if (direction == 0){
      current->getParent()->setLeft(current->getLeft());
    }
    else if (direction == 1){
      current->getParent()->setRight(current->getLeft());
    }

    current->getLeft()->setParent(current->getParent());
    delete current;
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
    }

    else {
      temp->getParent()->setLeft(temp->getLeft());
    }

    delete temp;
  }

  }
  else if (current->getData() > toDelete){
    removeNode (0, current->getLeft(), toDelete);
  }

  else if (current->getData() < toDelete){
    removeNode(1, current->getRight(),toDelete);
  }
}
