#include <iostream>

using namespace std;
#define INFINITY 1000000;

/*
*
* Author Stephen Sottosanti
* A Classa for Binomial Heap
*
*/
template<typename keytype, typename valuetype>
struct Tree{
  int degree = 0;
  keytype key;
  valuetype value;
  Tree *parent; //up
  Tree *child; //down
  Tree *sibling; //next or move right

  /*
  * Constructor with parameters
  */
  Tree(Tree<keytype, valuetype>* tree){
    key = tree->key;
    value = tree->value;
    parent = tree->parent;
    child = tree->child;
    sibling = tree->sibling;
  }

  /*
  * Constructor with parameters
  */
  Tree(keytype k, valuetype v,Tree<keytype, valuetype>* p, Tree<keytype, valuetype>* c, Tree<keytype, valuetype>* s){
    key = k;
    value = v;
    parent = p;
    child = c;
    sibling = s;
  }

  /*
  * Constructor with parameters
  */
  Tree& operator=(Tree H2){
    cout << "Copy of assignment of H2" << endl;
    swap(key, H2.key);
    swap(value, H2.value);
    swap(parent, H2.parent);
    swap(child, H2.child);
    swap(sibling, H2.sibling);
    return *this;
  }

};

/*************************************************************/
template<typename keytype, typename valuetype>
class BHeap{
private:
  Tree<keytype, valuetype> *root;

public:

  /*
  * Copy Assignment Operator
  */
  BHeap& operator=(BHeap copy){
    cout << "Copy assignment of H2";
    swap(root, copy.root);
    return *this;
  }

  /*
  * Copy Constructor
  */
  BHeap(const BHeap &H){
    root = H.root;
  }


  /*
  * Default Constructor. The heap should be empy
  * O(1)
  */
  //FINISHED
  BHeap(){
    root = nullptr;
  }

  /*
  * For this constructor the heap should be built using the arrays K and
  * V containing s items of keytype and valuetype. The heap should be
  * constructed using repeated insertion.
  * O(s)
  */

  //FINISHED
  BHeap(keytype k[], valuetype v[], int s){
    root = nullptr;

    for(unsigned int i = 0; i < s; ++i){
      insert(k[i], v[i]);
    }

  }

  /*
  * Insets the key k and value v pair into the heap
  */

  //FINISHED
  void insert(keytype k, valuetype v){
    Tree<keytype, valuetype> *myTree = root;
    Tree<keytype, valuetype> *myPrevTree = myTree;
    Tree<keytype, valuetype> *newTree = new Tree<keytype, valuetype>(k, v, nullptr, nullptr, nullptr);
    Tree<keytype, valuetype> *addTree = newTree;

    if(root == nullptr){ // at degree 0
      root = newTree;
      return;
    }

    int currentDegree = 0;
    int nextDegree = INFINITY;

    while(myTree != nullptr) {//current degree and next dehree

      int currentDegree = myTree->degree;
      //set next degree to a value
      if(myTree->sibling != nullptr){
        int nextDegree = myTree->sibling->degree;
      }
      else{
        int nextDegree = INFINITY;
      }

      //need to find out if current tree degree already exists or not
      if(addTree->degree == currentDegree){ //merge trees
        if(myTree->key > addTree->key){
          addTree->sibling = myTree->sibling;
          swap(myTree, addTree);
        }

        //Larger tree.key becomes child of smaller tree.key
        addTree->parent =  myTree;
        addTree->sibling = myTree->child;
        myTree->child = addTree;

        myTree->degree+= 1;
        //myTree = addTree;
        if(myPrevTree->key == root->key){//fixing the root
          root = myTree;
        }
        else{//fixing the pointer
          myPrevTree->sibling = myTree;
        }

        addTree = myTree;
      }//End of merge
      else if(addTree->degree < nextDegree){ //add new tree with unused degree

        if(myPrevTree->key == root->key){
          root = addTree;
          root->sibling = myTree;
        }
        else{
          myPrevTree = myTree;
          myTree = myTree->sibling;

          myPrevTree->sibling = addTree;
          addTree->sibling = myTree;
        }

        break;
      }

      myPrevTree = myTree;
      myTree = myTree->sibling;
    }

  }


/***************************************************************************/
  /*
  * Merges the H2 into the current heap
  */
  //FINISHED BUT ERROR WHEN DEALLOCATING MEMORY
  void merge(BHeap<keytype,valuetype> &H2){
    Tree<keytype, valuetype> *newTree = new Tree<keytype, valuetype>(H2.root);
    Tree<keytype, valuetype> *myTree = root;

    while(myTree->sibling != nullptr){
      myTree = myTree->sibling;
    }

    while(newTree != nullptr){
      myTree->sibling = new Tree<keytype, valuetype>(newTree);
      myTree = myTree->sibling;
      newTree = newTree->sibling;
    }
    PutInOrder();
    runMerge();

  }
/***************************************************************************/
  void runMerge() {
    if(root == nullptr){ // at degree 0
      return;
    }

    int currentDegree = 0;
    int nextDegree = INFINITY;

    Tree<keytype, valuetype> *myTree = root;
    Tree<keytype, valuetype> *myPrevTree = myTree;
    Tree<keytype, valuetype> *addTree = myTree->sibling;

    while(addTree != nullptr) {//current degree and next dehree

      //need to find out if current tree degree already exists or not
      if(myTree->degree == addTree->degree){ //merge trees
        if(addTree->key > myTree->key){
          myTree->sibling = addTree->sibling;
          swap(myTree, addTree);
        }

        //Larger tree.key becomes child of smaller tree.key
        addTree->parent =  myTree;
        addTree->sibling = myTree->child;
        myTree->child = addTree;

        myTree->degree+= 1;
        //myTree = addTree;
        if(myPrevTree->key == root->key){//fixing the root
          root = myTree;
        }
        else{//fixing the pointer
          myPrevTree->sibling = myTree;
        }

      }
      else{
        myPrevTree = myTree;
        myTree = myTree->sibling;
      }//End of merge
      // else if(addTree->degree < nextDegree){ //add new tree with unused degree
      //
      //   if(myPrevTree->key == root->key){
      //     root = addTree;
      //     root->sibling = myTree;
      //   }
      //   else{
      //     myPrevTree = myTree;
      //     myTree = myTree->sibling;
      //
      //     myPrevTree->sibling = addTree;
      //     addTree->sibling = myTree;
      //   }
      //
      //   break;
      // }

      //myPrevTree = myTree;
      addTree = myTree->sibling;
    }

    // while(myTreeNext != nullptr) {//current degree and next dehree
    //
    //   int currentDegree = myTreeNext->degree;
    //
    //   //need to find out if current tree degree already exists or not
    //   if(myCurrentTree->degree == currentDegree){ //merge trees
    //     if(myTreeNext->key > myCurrentTree->key){
    //       myCurrentTree->sibling = myTreeNext->sibling;
    //       swap(myCurrentTree, myTreeNext);
    //     }
    //
    //     //Larger tree.key becomes child of smaller tree.key
    //     myCurrentTree->parent =  myTreeNext;
    //     myCurrentTree->sibling = myTreeNext->child;
    //     myTreeNext->child = myCurrentTree;
    //
    //     myCurrentTree->degree+= 1;
    //
    //     if(myPrevTree->key == root->key){//fixing the root
    //       root = myTreeNext;
    //     }
    //     else{//fixing the pointer
    //       myPrevTree->sibling = myTreeNext;
    //     }
    //
    //     myCurrentTree = myTreeNext;
    //   }
    //   else{
    //     myCurrentTree = myCurrentTree->sibling;
    //   }
    //
    //   myPrevTree = myTreeNext;
    //   myTreeNext = myTreeNext->sibling;
    // }
  }
/***************************************************************************/
  /*
  * Destructor for the class
  */
  //FINISHED
//   ~BHeap() {
//     deleteRecursive(root);
//   }
// /***************************************************************************/
//   void deleteRecursive(Tree<keytype, valuetype> *tree) {
//       if (tree != nullptr) {
//         deleteRecursive(tree->child);
//         deleteRecursive(tree->sibling);
//         delete tree;
//       }
//   }

  /*
  * Returns the minimum key in the heap without modifying the heap
  */

  //FINISHED
  keytype peekKey() {
    keytype returnKey = root->key;
    Tree<keytype, valuetype> *myTree = root;

    while(myTree != nullptr){
      if(myTree->key < returnKey){
        returnKey = myTree->key;
      }
      myTree = myTree->sibling;
    }

    return returnKey;
  }

  /*
  * Returns the value associated with the minimum key in the heap without
  * modifying the heap
  */

  //FINISHED
  valuetype peekValue() {
    keytype returnKey = root->key;
    valuetype returnValue = root->value;
    Tree<keytype, valuetype> *myTree = root;

    while(myTree != nullptr){
      if(myTree->key < returnKey){
        returnKey = myTree->key;
        returnValue = myTree->value;
      }
      myTree = myTree->sibling;
    }

    return returnValue;
  }

  /*
  * Removes the minimum key in the heap and returns the key
  */

  //FINISHED
  keytype extractMin(){
    keytype returnKey = root->key;
    Tree<keytype, valuetype> *myTree = root;
    Tree<keytype, valuetype> *prevNode = myTree;
    Tree<keytype, valuetype> *previousNode = myTree;
    Tree<keytype, valuetype> *nodeToDelete = myTree;

    while(myTree != nullptr){
      if(myTree->key < returnKey){
        returnKey = myTree->key;

        nodeToDelete = myTree;
        previousNode = prevNode;
      }

      prevNode = myTree;
      myTree = myTree->sibling;

    }

    if(nodeToDelete->child == nullptr){//deleting a min key of degree 0. no children
      root = nodeToDelete->sibling;
      delete nodeToDelete;
    }
    else{
      promoteChildren(nodeToDelete, previousNode, nodeToDelete->child);
    }

    // delete nodeToDelete;

    return returnKey;
  }

//WORKS
  void promoteChildren(Tree<keytype, valuetype> *x, Tree<keytype, valuetype> *y, Tree<keytype, valuetype> *z){
    //x is node to be deleted
    //y is previous node
    //z is child of node to be deleted
    Tree<keytype, valuetype> *prevSib = z;
    Tree<keytype, valuetype> *testSib = z;

    if(y == x){//previous node is root
      root = z;

      while(z->sibling != nullptr) {
        z->parent = nullptr;
        z = z->sibling;
      }

      z->parent = nullptr;
      z->sibling = x->sibling;
    }
    else{//there is a previous node
      cout << "no in here: " << endl;
      cout << "x " << x->key << endl;
      cout << "y " << y->key << endl;
      cout << "z " << z->key << endl;
       y->sibling = z;

      while(z->sibling != nullptr) {
        z->parent = nullptr;
        z = z->sibling;
      }

      z->parent = nullptr;
      z->sibling = x->sibling;
    }

    PutInOrder();
    printKey();

    runMerge();

  }
//WORKS
  void PutInOrder(){
    Tree<keytype, valuetype> *x = root;
    Tree<keytype, valuetype> *rootCheck = nullptr;
    Tree<keytype, valuetype> *nextSib = x;

    while(x != nullptr) {
      nextSib = x->sibling;
      if(nextSib != nullptr){
        if(x->degree > nextSib->degree){
          x->sibling = nextSib->sibling;
          nextSib->sibling = x;

          if(rootCheck == nullptr){
            root = nextSib;
          }
          else{
            rootCheck->sibling = nextSib;
            //PutInOrder(root);
          }

          PutInOrder();
        }
      }
      rootCheck = x;
      x = x->sibling;
    }

  }

  /*
  * Writes the keys stored in the heap, printing the
  * smallest binomial tree first. When printing a
  * binomial tree, print the size of tree first and then
  * use a modified preorder traversal of the tree.
  * See the example below.
  */
  //FINISHED
  void printKey(){
    //VLR
    Tree<keytype, valuetype> *myTree = root;

    while(myTree != nullptr){

      cout << "B" << myTree->degree << endl;
      cout << myTree->key << " "; //print current key than all children of it

      if(myTree->child != nullptr){
        printOne(myTree->child);
      }

      myTree = myTree->sibling;
      cout << endl << endl;
    }

  }
/***************************************************************************/
  void printOne(Tree<keytype, valuetype> *x){
    //Tree<keytype, valuetype> *printSiblings;

    cout << x->key << " ";
    if(x->child != nullptr) {
      printOne(x->child);
    }

    if(x->sibling != nullptr) { //while loop to print out siblings in level
      printOne(x->sibling);
    }
  }
/***************************************************************************/
/***************************************************************************/

};
