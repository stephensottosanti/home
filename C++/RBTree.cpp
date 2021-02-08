#include <iostream>
#include <cstdlib>

using namespace std;

/***********************************************************/
enum Color{Red, Black};

/***********************************************************/
template<typename keytype, typename valuetype>
struct Node{
  keytype key;
  valuetype value;
  Node *parent; //parent
  Node *leftChild; //left child
  Node *rightChild; //right child
  Color color; //either red or black
  int subTreeSize;
  Node(keytype k, valuetype v, Node *p, Node *l, Node *r, Color c){
    key = k;
    value = v;
    parent = p;
    leftChild = l;
    rightChild = r;
    color = c;
    subTreeSize = 1;
  }
};

/***************************************************************************/
template<typename keytype, typename valuetype>
class RBTree{
private:
  int numNodes;
  Node<keytype, valuetype> *root;
public:
/***************************************************************************/
/***************************************************************************/
  //Default Constructor. Tree should be empty
  //O(1)
  RBTree(){
    numNodes = 0;
    root = nullptr;
  }
/***************************************************************************/
  //O(s lg s)
  RBTree(keytype k[], valuetype v[], int s){
    numNodes = s;
    root = nullptr;
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *y;

    //given the size of the tree so were running through s times
    for(int i = 0; i < s; ++i) {
      Node<keytype, valuetype> *z = new Node<keytype, valuetype>(k[i], v[i], nullptr, nullptr, nullptr, Red);
      x = root;
      y = x;

      //find node to add the new node to
      while(x != nullptr) {
        //if new key is less than current key move left
        y = x;
        if(z->key < x->key) {
          x = x->leftChild;
        }
        //if new key is greater than current key move right
        else {
          x = x->rightChild;
        }
      } //end while loop


      if(y == nullptr){
        //case 0: add the first node to the tree. Change color to black
        root = z;
        root->color = Black;
        root->subTreeSize = 1;
      }
      else if(z->key < y->key){
        z->parent = y;
        y->leftChild = z;
        increaseSubTreeSize(z);
      }
      else{
        z->parent = y;
        y->rightChild = z;
        increaseSubTreeSize(z);
      }

      //run the fix-up
      if(z->parent != nullptr && z->parent->color == Red){
        runFixUp(z);
      }


    }//end of for loop

  }
/***************************************************************************/
/***************************************************************************/
  ~RBTree(){
    deleteRecursive(root);
  }
/***************************************************************************/
  void deleteRecursive(Node<keytype, valuetype> *node) {
      if (node != nullptr) {
        deleteRecursive(node->leftChild);
        deleteRecursive(node->rightChild);
        delete node;
      }
  }
/***************************************************************************/
/***************************************************************************/
  /*Traditional search. Should return a pointer to the
  valutype stored with the key. if the key is not
  stored in the tree then the function should return NULL*/
  //O(lg n)
  valuetype *search(keytype k){
    Node<keytype, valuetype> *x = root;

    //find node with key k
    while(x != nullptr) {
      //valuetype *t;

      if(x->key == k){
        return &x->value;
      }
      else if(k < x->key) { //move left
        x = x->leftChild;
      }
      else { //move right
        x = x->rightChild;
      }
    } //end while loop

  return NULL;
  }
/***************************************************************************/
/***************************************************************************/
  //Inserts the node with key k and value v into the tree
  //O(lg n)
  void insert(keytype k, valuetype v){
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *y;
    Node<keytype, valuetype> *z = new Node<keytype, valuetype>(k, v, nullptr, nullptr, nullptr, Red);
    numNodes += 1;
    x = root;
    y = x;

    //find node to add the new node to
    while(x != nullptr) {
      //if new key is less than current key move left
      y = x;
      if(z->key < x->key) {
        x = x->leftChild;
      }
      //if new key is greater than current key move right
      else {
        x = x->rightChild;
      }
    } //end while loop

    if(y == nullptr){
      //case 0: add the first node to the tree. Change color to black
      root = z;
      root->color = Black;
      root->subTreeSize = 1;
    }
    else if(z->key < y->key){
      z->parent = y;
      y->leftChild = z;
      increaseSubTreeSize(z);
    }
    else{
      z->parent = y;
      y->rightChild = z;
      increaseSubTreeSize(z);
    }
    //run the fix-up
    if(z->parent != nullptr && z->parent->color == Red){
      runFixUp(z);
    }

  } //end of insert
  /***************************************************************************/
  void runFixUp(Node<keytype, valuetype> *z){
    Node<keytype, valuetype> *y;
    Node<keytype, valuetype> *x;

    while(z->parent->color == Red){

      if(z->parent == z->parent->parent->leftChild){
        y = z->parent->parent->rightChild;//y is set to the uncle

        if(y == nullptr || y->color == Black){
          if(z == z->parent->leftChild){ //line is formed. Uncle is null
            rotateRight(z);
            z->parent->color = Black;
            z->parent->rightChild->color = Red;
          }
          else{  //triangle is formed so for a line
            simpleLeft(z);
            z = z->leftChild;
          }
        }
        else if(y->color == Red){
          //case 1. Z.uncle = red
          z->parent->color = Black;
          y->color = Black;
          z->parent->parent->color = Red;
          z = z->parent->parent;
          //if were at the root. change root to black and done
          if(z->key == root->key){
            root = z;
            root->color = Black;
            break;
          }
        }
      }
      else if(z->parent == z->parent->parent->rightChild){
        y = z->parent->parent->leftChild; // y is now the uncle

        if(y == nullptr || y->color == Black){
          if(z == z->parent->rightChild){ //line is formed. Uncle is Black
            rotateLeft(z);
            z->parent->color = Black;
            z->parent->leftChild->color = Red;
          }
          else{//Triangle is formed. Simple Rotate
            //Form a line
            simpleRight(z);
            z = z->rightChild;
          }
        }
        else if(y->color == Red){
          //case 1. Z.uncle = red
          z->parent->color = Black;
          y->color = Black;
          z->parent->parent->color = Red;
          z = z->parent->parent;
          //if were at the root. change root to black and done
          if(z->key == root->key){
            root = z;
            root->color = Black;
            break;
          }
        }//end of else if ^
      }//end of else if ^^
    }//end of while loop
  }
  /***************************************************************************/
  Node<keytype, valuetype> *simpleLeft(Node<keytype, valuetype> *z){
    //for a line then rotate
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *y;

    x = z->parent->parent;
    y = z->parent;

    x->leftChild = z;
    z->parent = x;
    z->leftChild = y;
    y->parent = z;
    y->rightChild = nullptr;

    fixRank(x);
    fixRank(y);
    fixRank(z);

    return z;
  }
  /***************************************************************************/
  Node<keytype, valuetype> *simpleRight(Node<keytype, valuetype> *z){
    //for a line then rotate
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *y;

    x = z->parent->parent;
    y = z->parent;

    x->rightChild = z;
    z->parent = x;
    z->rightChild = y;
    y->parent = z;
    y->leftChild = nullptr;

    fixRank(x);
    fixRank(y);
    fixRank(z);

    return z;
  }
/***************************************************************************/
  Node<keytype, valuetype> *rotateLeft(Node<keytype, valuetype> *z){
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *y;

    x = z->parent->parent;
    y = z->parent;

    y->parent = x->parent;
    if(x->parent != nullptr){ //if were moving around a sub tree
      if(x == x->parent->leftChild){
        x->parent->leftChild = y;
      }
      else{
        x->parent->rightChild = y;
      }
    }
    x->rightChild = y->leftChild;
    if(y->leftChild != nullptr){
      y->leftChild->parent = x;
      //x->subTreeSize += y->leftChild->subTreeSize;
    }
    x->parent = y;
    y->leftChild = x;


    fixRank(x);
    fixRank(y);
    fixRank(z);

    if(y->parent == nullptr){ //y is the new root
      root = y;
    }

    return z;
  }
/***************************************************************************/
  Node<keytype, valuetype> *rotateRight(Node<keytype, valuetype> *z){
    Node<keytype, valuetype> *x;
    Node<keytype, valuetype> *y;

    x = z->parent->parent;
    y = z->parent;

    y->parent = x->parent;
    if(x->parent != nullptr){ //if were moving around a sub tree
      if(x == x->parent->leftChild){
        x->parent->leftChild = y;
      }
      else{
        x->parent->rightChild = y;
      }
    }
    x->leftChild = y->rightChild;
    if(y->rightChild != nullptr){
      y->rightChild->parent = x;
    }
    x->parent = y;
    y->rightChild = x;


    fixRank(x);
    fixRank(y);
    fixRank(z);

    if(y->parent == nullptr){ //y is the new root
      root = y;
    }

    return z;
  }
/***************************************************************************/
  void increaseSubTreeSize(Node<keytype, valuetype> *x){
    //traverse your way up to root ad increase subtree sizes
    if(x->parent == nullptr){ //root
      if(x->leftChild == nullptr) { //no left child. will result in error
        return;
      }
      x->subTreeSize = x->leftChild->subTreeSize + 1; //has a left child
      return;
    }
    else if(x->leftChild == nullptr && x->rightChild == nullptr){
      x = x->parent;
      increaseSubTreeSize(x);
    }
    else{
      x->subTreeSize += 1;
      x = x->parent;
      increaseSubTreeSize(x);
    }
  }
/***************************************************************************/
  void decreaseSubTreeSize(Node<keytype, valuetype> *x){
    //traverse your way up to root ad increase subtree sizes
    if(x->parent == nullptr){ //root
      if(x->leftChild == nullptr) { //no left child. will result in error
        return;
      }
      x->subTreeSize = x->leftChild->subTreeSize + 1; //has a left child
      return;
    }
    else if(x->leftChild == nullptr && x->rightChild == nullptr){
      x = x->parent;
      decreaseSubTreeSize(x);
    }
    else{
      x->subTreeSize -= 1;
      x = x->parent;
      decreaseSubTreeSize(x);
    }
  }
/***************************************************************************/
  void fixRank(Node<keytype, valuetype> *x){
    //fix sub tree sizes
    if(x == nullptr) { //nullptr nothing to change
      return;
    }

    if(x->parent == nullptr) {//root node
      if(x->leftChild != nullptr){
        x->subTreeSize = x->leftChild->subTreeSize + 1;
      }
      else {
        x->subTreeSize = 1;
      }
      return;
    }


    if(x->leftChild == nullptr){
      if(x->rightChild == nullptr){ //subTreeSize has no children so it = 1
        x->subTreeSize = 1;
      }
      else{ // rightChild
        x->subTreeSize = x->rightChild->subTreeSize + 1;
      }
    }
    else { //has a leftChild
      if(x->rightChild == nullptr){ //subTreeSize has 1 new child on rightChild
        x->subTreeSize = x->leftChild->subTreeSize + 1;
      }
      else{ //Has 2 children
        x->subTreeSize = x->leftChild->subTreeSize + x->rightChild->subTreeSize + 1;
      }
    }
  }
/***************************************************************************/
/***************************************************************************/
//O(lg n)
int remove(keytype k){
  Node<keytype, valuetype> *z = root;

  //find node with key k
  while(z != nullptr) {
    if(z->key == k){//check current node
      break;
    }
    else if(k < z->key) { //move left
      z = z->leftChild;
    }
    else { //move right
      z = z->rightChild;
    }
  } //end while loop

  //If the Key wasn't found
  if(z == nullptr){
    return 0;
  }

  numNodes -= 1;
  decreaseSubTreeSize(z);
  cout << "removing " << z->key << endl;

  //Find its replacement

  //INITIAL STEPS PART 1
  // - If the node we deleted has 2 NIL children, it's replacement x is NIL
  // - If the node we deleted has 1 NIL child and 1 non NIL Child, its
  // replacement x is the non NIL child
  // - If the node we deleted has 2 non NIL children, set x to the replacements
  // right child before the replacement is spliced out

  //INITIAL STEPS PART 2
  // - If the node we deleted is red and its replacement is red or NIL, we
  // are done
  // - If the node we deleted is red and its replacement is black, color the
  // replacement red and porceed to the appropriate case
  // - If the node we deleted is black and its replacement is red, color the
  // replacement black and we are done
  // - If the node we deleted is black and its replacement is either black or
  // nil then proceed to the appropriate case

  Node<keytype, valuetype> *x;
  Node<keytype, valuetype> *y;
  Node<keytype, valuetype> *v;

  //2 NILL children
  if (z->leftChild == nullptr && z->rightChild == nullptr) {
    x = nullptr; // 2 nil children so the replacement is a nullptr

    if(z->parent == nullptr) { //empty tree
      delete z;
      root = nullptr;
    }

    if(z == z->parent->leftChild){
      z->parent->leftChild = x;
    }
    else {
      z->parent->rightChild = x;
    }

    if(z->color == Red) {
      //the node were deleting is red and its replacement is nil
      delete z;
      //we are done
    }
    //the node we deleted is black and its replacement is nil meaning black
    else{
      y = z->parent;
      runCases(y, x);
      delete z;
    }

    return 1;
  }
  //2 NON-NIL children
  else if (z->leftChild != nullptr && z->rightChild != nullptr) {

    x = z->rightChild;
    x = runSuccesor(x);

    y = x->rightChild;
    v = x;

    if(x == x->parent->leftChild){
      x->parent->leftChild = y;
    }
    else {
      x->parent->rightChild = y;
    }

    if(x->parent->key != z->key){
      v = x->parent;
    }

    if(z->color == Red) {
      //z is red and x is nil or red
      if(x == nullptr || x->color == Red){
        x = runReplace(z,x);
        //we are done
      }
      //The node we deleted is red and the replacement is black
      else {
        x = runReplace(z,x);
        x->color = Red;
        x = y; //x is now the replacements new right child
        runCases(v, x);
      }
    }
    else{ //the node we deleted is black
      //the node we deleted is black and the replacement is nil
      if(x == nullptr){
        x = runReplace(z,x);
        x = y; //x is now the replacements new right child
        runCases(v, x);
      }
      //z is black and x is red. Color x black and we are done
      else if(x->color == Red) {
        x = runReplace(z,x);
        x->color = Black;
      }
      //the node we deleted is black and the replacement is black
      else {
        x = runReplace(z,x);
        x = y; //x is now the replacements new right child
        runCases(v, x);
      }

    }

    delete z;
    return 1;
  }
  //1 NIL child
  else{
    //set replacement
    if (z->leftChild == nullptr && z->rightChild != nullptr) {
      x = z->rightChild;
    }
    else {
      x = z->leftChild;
    }

    v = x;

    if(z->color == Red) {
      ///z is red and x is nil or red
      if(x == nullptr || x->color == Red){
        x = runReplace(z,x);
        //we are done
      }
      //The node we deleted is red and the replacement is black
      else {
        x = runReplace(z,x);
        x->color = Red;
        x = y; //x is now the replacements new right child
        runCases(v, x);
      }
    }
    else{ //the node we deleted is black
      //z is black and x is red. Color x black and we are done
      if(x->color == Red){
        if(z->parent == nullptr){//deleting root so only 2 things left
          root = x;
          x->parent = z->parent;
          delete z;
        }
        else if(z == z->parent->leftChild){
          z->parent->leftChild = x;
          x->parent = z->parent;
          x->color = Black;
          delete z;
        }
        else {
          z->parent->rightChild = x;
          x->parent = z->parent;
          x->color = Black;
          delete z;
        }
        //we are done
      }
      //the replacement is black so we are done
      else{
        //Black cant have 1 black child
      }
    }
    return 1;
  }


  return 0;
}
/***************************************************************************/
Node<keytype, valuetype> *runReplace(Node<keytype, valuetype> *z, Node<keytype, valuetype> *x) {

  if(z->parent != nullptr) {//checking if we are at root
    if(z == z->parent->leftChild){
      z->parent->leftChild = x;
    }
    else {
      z->parent->rightChild = x;
    }
  }

  if(x != z->rightChild) {// had to find a successor
    x->parent = z->parent;
    x->leftChild = z->leftChild;
    x->rightChild = z->rightChild;

    if(z->leftChild != nullptr){
      z->leftChild->parent = x;
    }

    if(z->rightChild != nullptr){
      z->rightChild->parent = x;
    }

  }
  else{
    if(x != nullptr){
      x->parent = z->parent;
      x->leftChild = z->leftChild;
    }

    if(z->leftChild != nullptr){
      z->leftChild->parent = x;
    }

  }

  fixRank(x);

  return x;

}
/***************************************************************************/
void runCases(Node<keytype, valuetype> *v, Node<keytype, valuetype> *x) {
  Node<keytype, valuetype> *w;
  Node<keytype, valuetype> *z;

  //CASES
  // 0 - Node x is Red
  // 1 - Node x is black and its sibling is red
  // 2 - Node x is black and its sibling w is black and both of w's children
  // are black or NILL
  // 3 - Node x is black and its siblings w is black and
    // 3 - If x is the leftChild, w's left child is red and w's right child is
    // black
    // 3 - If x is the rightChild, w's right child is red and w's left child is
    // black
  // 4 - Node x is black and its sibling w is black and
    // 4 - If x is the left child, w's right child is red
    // 4 - If x is the right child, w's left child is red

  //Set up sibling w
  if(x == nullptr){
    if(v->rightChild == nullptr){
      w = v->leftChild;
    }
    else{
      w = v->rightChild;
    }
  }
  else if(x == x->parent->rightChild){
    w = x->parent->leftChild;
  }
  else {
    w = x->parent->rightChild;
  }

  //CASE 0
  // - Color x black and we are done
  // if(x != nullptr) {
  //   if(x->color == Red) {
  //     cout << "when" << endl;
  //     x->color = Black; // and we are done
  //     return;
  //   }
  // }

  //CASE 1
  // - Color w Black
  // - Color x->parent Red
  // - Rotate x Parent
    //if x is the left child do a left rotation
    //if x is the right child do a right rotation
  // - Now we have to change w
    //if x is the left child set w = x.p.right
    //if x is the right child set w = x.p.left
  // - With x and our new w decide on case 2,3,or 4 from here
  if(w != nullptr) {
    if((x == nullptr || x->color == Black) && (w->color == Red)) {

      w->color = Black;
      w->parent->color = Red;

      if(v->parent != nullptr){ //if were moving around a sub tree
        if(v == v->parent->leftChild){
          v->parent->leftChild = w;
        }
        else{
          v->parent->rightChild = w;
        }
      }

      if(w == w->parent->rightChild) {
        //do a left rotation

        w->parent = v->parent;
        v->parent = w;
        v->rightChild = w->leftChild;

        if(w->leftChild != nullptr){
          w->leftChild->parent = v;
        }

        w->leftChild = v;

        if(w->parent == nullptr){ //y is the new root
          root = w;
          if(w->leftChild == nullptr) { //no left child. will result in error
            w->subTreeSize = 1;
          }
        }

        w = v->rightChild;
        fixRank(v);
        fixRank(w);
      }
      else{
        //do a right rotation

        w->parent = v->parent;
        v->parent = w;
        v->leftChild = w->rightChild;

        if(w->rightChild != nullptr){
          w->rightChild->parent = v;
        }

        w->rightChild = v;

        if(w->parent == nullptr){ //y is the new root
          root = w;
          if(w->rightChild == nullptr) { //no left child. will result in error
            w->subTreeSize = 1;
          }
        }

        w = v->leftChild;
        x = v->rightChild;
        fixRank(v);
        fixRank(w);
      }
    }
  }

  //CASE 2
  // - Color w red
  // - Set x = x.p
    // - If our new x is red, color x black. we are done.
    // - If our new x is black, decide on cases 1, 2, 3, or 4 from here.
    // Note that we have a new w now
    if((w->leftChild == nullptr || w->leftChild->color == Black) && (w->rightChild == nullptr || w->rightChild->color == Black)){
      x = v;
      w->color = Red;

      if(x->color == Red) {
        x->color = Black;
        return;
      }
      else {
        v = v->parent;

        if(v == nullptr){
          return;
        }

        runCases(v,x);
        return;
      }
    }

    //CASE 3
    // - Color w's child black
      // - If x is the left child, color w.left black
      // - If x is the right child, color w.right black
    // - Color w red
    // - Rotate w
      // - If x is the left child do a right rotation
      // - If x is the right child do a left rotation
    // - Now we have to change w
      // If x is the left child set w = x.p.right
      // If x is the left child set w = x.p.left
    // - Proceed to case 4

    if(w->leftChild != nullptr){
      if(x != nullptr && w->color == Black){
        if((x->color == Black && x == x->parent->leftChild) && (w->leftChild->color == Red && (w->rightChild == nullptr || w->rightChild->color == Black))){
          w->leftChild->color = Black;
          w->color = Red;
          w = w->leftChild;
          //do a right rotation
          w = simpleRight(w);

          w->color = Red;
          w->rightChild->color = Black;
          //do a right rotation
          w = w->rightChild;
          rotateLeft(w);
          return;
          //proceed to case 4
        }
      }
      else if(x == nullptr && w->color == Black){
        if((w = w->parent->rightChild) && (w->leftChild->color == Red && (w->rightChild == nullptr || w->rightChild->color == Black))){
          w->leftChild->color = Black;
          w->color = Red;
          w = w->leftChild;
          //do a right rotation
          w = simpleRight(w);

          w->color = Red;
          w->rightChild->color = Black;
          //do a right rotation
          w = w->rightChild;
          rotateLeft(w);
          return;
          //proceed to case 4
        }
      }
    }
    else if(w->rightChild != nullptr){
      if(x != nullptr && w->color == Black){
        if((x->color == Black && x == x->parent->rightChild) && (w->rightChild->color == Red && (w->leftChild == nullptr || w->leftChild->color == Black))){
          w->rightChild->color = Black;
          w->color = Black;
          //do a left rotation
          w = w->rightChild;
          w = simpleLeft(w);

          w->color = Red;
          w->leftChild->color = Black;
          //do a right rotation
          w = w->leftChild;
          rotateRight(w);
          return;
          //proceed to case 4
        }
      }
      else if(x == nullptr && w->color == Black){
        if((w = w->parent->leftChild) && (w->rightChild->color == Red && (w->leftChild == nullptr || w->leftChild->color == Black))){
          w->rightChild->color = Black;
          w->color = Black;
          //do a simple left rotation
          w = w->rightChild;
          w = simpleLeft(w);

          w->color = Red;
          w->leftChild->color = Black;
          //do a right rotation
          w = w->leftChild;
          rotateRight(w);
          return;
          //proceed to case 4
        }
      }
    }

    //CASE 4
    // - Color w the same color as x.p
    // - Color x.p black
    // - Color w's child black
      // - If x is the left child, color w.right black
      // - If x is the right child, color w.left black
    // - Rotate x.p
      // - If x is the left child do a left rotation
      // - If x is the right child do a right rotation
    //We are done.
    if(w->rightChild != nullptr){
      if((x == nullptr ||x == x->parent->leftChild) && w->rightChild->color == Red) {
        w->color = w->parent->color;
        w->parent->color = Black;
        w->rightChild->color = Black;
        //do a left rotation
        w = w->rightChild;
        rotateLeft(w);
        return;
      }
    }
    if(w->leftChild != nullptr){
      if((x == nullptr || x == x->parent->rightChild) && w->leftChild->color == Red) {
        w->color = w->parent->color;
        w->parent->color = Black;
        w->leftChild->color = Black;
        //do a right rotation
        w = w->leftChild;
        rotateRight(w);
        return;
      }
    }


}
/***************************************************************************/
  //Prints the keys of the tree in a preorder traversal
  //O(n)
  void preorder(){
    //VLR
    Node<keytype, valuetype> *x = root;

    if(x == nullptr){ //empty tree
      return;
    }

    cout << x->key; //print current key

    if(x->leftChild != nullptr){
      goLeft(x, 0);
    }

    if(x->rightChild != nullptr){
      goRight(x, 0);
    }
  }
/***************************************************************************/
  //Prints the keys of the tree in an inorder traversal
  //O(n)
  void inorder(){
    //LVR
    Node<keytype, valuetype> *x = root;

    if(x == nullptr){ //empty tree
      return;
    }

    if(x->leftChild != nullptr){
      goLeft(x, 1);
    }

    cout << x->key;

    if(x->rightChild != nullptr){
      goRight(x, 1);
    }
  }
/***************************************************************************/
  //Prints the keys of the tree in an postorder traversal
  //O(n)
  void postorder(){
    //LRV
    Node<keytype, valuetype> *x = root;

    if(x == nullptr){ //empty tree
      return;
    }

    if(x->leftChild != nullptr){
      goLeft(x, 2);
    }

    if(x->rightChild != nullptr){
      goRight(x, 2);
    }

    cout << x->key;

  }
/***************************************************************************/
  void goLeft(Node<keytype, valuetype> *x, int a){
    x = x->leftChild;

    if(a == 0){//VLR
      cout << x->key;
    }

    if(x->leftChild != nullptr){
      goLeft(x, a);
    }

    if(a == 1){//LVR
      cout << x->key;
    }

    if(x->rightChild != nullptr){
      goRight(x, a);
    }
    if(a == 2){//LRV
      cout << x->key;
    }

  }
/***************************************************************************/
  void goRight(Node<keytype, valuetype> *x, int a){
    x = x->rightChild;

    if(a == 0){//VLR
      cout << x->key;
    }

    if(x->leftChild != nullptr){
      goLeft(x, a);
    }

    if(a == 1){//LVR
      cout << x->key;
    }

    if(x->rightChild != nullptr){
      goRight(x, a);
    }

    if(a == 2){//LRV
      cout << x->key;
    }
  }
/***************************************************************************/
/***************************************************************************/
/*Returns a pointer to the key after k in the tree. Should
return Null if no successor exits*/
//O(lg n)
keytype *successor(keytype k){
  Node<keytype, valuetype> *x = root;
  //x = runFindKey(k);
  x = runFindKey(k);

  if(x->rightChild == nullptr) {
    return NULL;
  }
  else {
    x = x->rightChild;
    x = runSuccesor(x);
    return &x->key;
  }

}
/***************************************************************************/
Node<keytype, valuetype> *runSuccesor(Node<keytype, valuetype> *node) {
    if (node->leftChild != nullptr) {
        node = node->leftChild;
        node = runSuccesor(node);
    }

    return node;
}
/*Returns a pointer to the key before k in the tree. Should
return NULL if no predecessor exists*/
//O(lg n)
keytype *predecessor(keytype k){
  Node<keytype, valuetype> *x = root;
  x = runFindKey(k);

  if(x->leftChild == nullptr) {
    return NULL;
  }
  else {
    x = x->leftChild;
    x = runPredeccesor(x);
    return &x->key;
  }

}
/***************************************************************************/
Node<keytype, valuetype> *runPredeccesor(Node<keytype, valuetype> *node) {
    if (node->rightChild != nullptr) {
        node = node->rightChild;
        node = runPredeccesor(node);
    }

  return node;
}
/***************************************************************************/
/***************************************************************************/
  /*Returns the rank of the key in the tree. Returns 0 if
  the key k is not found. The smallest item in the tree
  rank is 1.*/
  //O(lg n)
  int rank(keytype k){
    Node<keytype, valuetype> *x = root;
    int findRank = 0;
    //find node with key k
    while(x != nullptr) {
      if(x->key == k){
        if(x->leftChild != nullptr){
          findRank += x->leftChild->subTreeSize;
        }
        findRank += 1;
        return findRank;
      }
      if(k < x->key) { //move left
        x = x->leftChild;
      }
      else { //move right
        if(x->leftChild == nullptr){
          findRank += 1;
        }
        else {
          findRank += x->leftChild->subTreeSize + 1;
        }

        x = x->rightChild;
      }
    } //end while loop

    return 0;
  }
/***************************************************************************/
/***************************************************************************/
  /*Order statistics. Returns the key of the node at position
  "pos" in the tree. Calling with pos = 1 should return
  the smallest key in the tree, pos = n should return the
  largest*/
  //O(lg n)
  keytype select(int pos){
    Node<keytype, valuetype> *x = root;
    int findPos = x->subTreeSize;

    while(x != nullptr) {

      if(findPos == pos){
        return x->key;
      }

      if(pos < findPos){ //somewhere on the left
        x = x->leftChild;
        findPos -= x->subTreeSize;

        if(x->leftChild != nullptr){
          findPos += x->leftChild->subTreeSize;
        }
      }
      else{ //moving to the right
        x = x->rightChild;

        if(x->leftChild != nullptr){
          findPos += x->leftChild->subTreeSize + 1;
        }
        else{
          findPos += 1;
        }
      }
    }

    return x->key;
  }
/***************************************************************************/
/***************************************************************************/
Node<keytype, valuetype> *runFindKey(keytype k){
  Node<keytype, valuetype> *x = root;

  while(x != nullptr) { //find node with key k
    if(x->key == k){//check current node
      return x;
    }
    else if(k < x->key) { //move left
      x = x->leftChild;
    }
    else { //move right
      x = x->rightChild;
    }
  } //end while loop

  return nullptr;
}
/***************************************************************************/
/***************************************************************************/
int size(){
  return numNodes;
}
/***************************************************************************/
/***************************************************************************/
};
