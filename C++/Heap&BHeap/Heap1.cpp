#include <iostream>

using namespace std;

/*************************************************************
*
* Author Stephen Sottosanti
* A Standard Binary Heap
*
*
*
***********************************************************/
template<typename keytype, typename valuetype>
struct Node{
  keytype key;
  valuetype value;
  Node() {

  }
  Node(keytype k, valuetype v){
    key = k;
    value = v;
  }
};

/*************************************************************/
template<typename keytype, typename valuetype>
class Heap{
private:
  int size;
  int space;
  int capacity;
  bool heap;
  Node<keytype, valuetype> *array;

public:

  /*
  * Default Constructor. The heap should be empy
  * O(1)
  */
  Heap(){
    size = 1;
    capacity = 2;
    array = new Node<keytype, valuetype>[2];
  }
/*************************************************************/
  /*
  * For this constructor the heap should be built using the arrays K and
  * V containing s items of keytype and valuetype. The heap should be
  * constructed using the O(n) bottom up heap building method
  * O(s)
  */
  Heap(keytype k[], valuetype v[], int s){
    size = 1;
    capacity = 2;
    array = new Node<keytype, valuetype>[2];

    // array[0].key = k[0];
    // array[0].value = v[0];

    for(unsigned int i = 1; i < s + 1; ++i){
      array[i].key = k[i -1];
      array[i].value = v[i -1];
      size += 1;

      if(size == capacity){ //double the size of the array
        Node<keytype, valuetype> *temp;
        temp = new Node<keytype, valuetype>[size];

        for(unsigned int i = 1; i < size; ++i){
          temp[i] = array[i];
        }

        capacity = capacity*2;

        array = new Node<keytype, valuetype>[capacity];

        for(unsigned i = 1; i < size; i++) {
          array[i] = temp[i];
        }
      }
    }
    //then bottom up heap sort them. min heap
    BottomsUp(array);
  }
/*************************************************************/
  void BottomsUp(Node<keytype, valuetype> *array) {
    unsigned int k = 0;
    unsigned int j = 0;
    int cap = size - 1;
    Node<keytype, valuetype> v;

    for(unsigned int i = cap/2; i > 0; --i){
      k = i;
      v = array[k];
      heap = false;

      while (heap == false && 2*k <= cap) {
        j = 2*k;

        if(j < cap) { // there are two children
          if(array[j].key > array[j+1].key) {
            j = j + 1;
          }
        }

        if(v.key <= array[j].key) {
          heap = true;
        }
        else {
          array[k] = array[j];
          k = j;
        }
      }

      array[k] = v;
    }

  }
/*************************************************************/
/*************************************************************/
  /*
  * Insets the key k and value v pair into the heap
  */
  void insert(keytype k, valuetype v){

    array[size].key = k;
    array[size].value = v;
    BottomsUp(array);

    size += 1;

    if(size == capacity){ //double the size of the array
      Node<keytype, valuetype> *temp;
      temp = new Node<keytype, valuetype>[size];

      for(unsigned int i = 1; i < size; ++i){
        temp[i] = array[i];
      }

      capacity = capacity*2;

      array = new Node<keytype, valuetype>[capacity];

      for(unsigned i = 1; i < size; i++) {
        array[i] = temp[i];
      }
    }

  }
/*************************************************************/
void BubbleUp(Node<keytype, valuetype> *array){
  int k = size;
  int x;
  int j;
  heap = false;

  while (k/2 > 0 && heap == false) {
    j = k/2;
    x = k;

    if(2*j < size) { //node we inserted
      if(array[x].key > array[x-1].key) {
        x = x - 1;
      }
    }

    if(array[x].key >= array[j].key){
      heap = true;
    }
    else{
      swap(array[x], array[j]);
      k = j;
    }
  }

}
/*************************************************************/
/*************************************************************/
  /*
  * Destructor for the class
  */
  ~Heap() {
    delete[] array;
  }

  /*
  * Returns the minimum key in the heap without modifying the heap
  */
  keytype peekKey() {
    return array[1].key;
  }

  /*
  * Returns the value associated with the minimum key in the heap without
  * modifying the heap
  */
  valuetype peekValue() {
    return array[1].value;
  }

  /*
  * Removes the minimum key in the heap and returns the key
  */
  keytype extractMin(){
    Node<keytype, valuetype> v;
    Node<keytype, valuetype> *temp;
    v = array[1];

    for(unsigned int i = 1; i < size; ++i){
      array[0] = array[i];
      array[i] = array[i + 1];
    }

    size -= 1;

    float check = (float)size/(float)capacity; // checks the amount of the array that is being "used"
    //for all the user knows

    if(check <= 0.25){ //reduce the size of the array
      Node<keytype, valuetype> *temp;
      temp = new Node<keytype, valuetype>[size];

      for(unsigned int i = 1; i < size; ++i){
        temp[i] = array[i];
      }

      capacity = capacity/2;

      array = new Node<keytype, valuetype>[capacity];

      for(unsigned i = 0; i < size; i++) {
        array[i] = temp[i];
      }

    }

    BottomsUp(array);

    return v.key;
  }
  //
  // void TrickleDown(Node<keytype, valuetype> *array){
  //   k = 1;
  //
  //   while (k*2 <= size) {
  //     j = 2*k;
  //
  //     if(j < size) { // there are two children
  //       if(array[j].key > array[j+1].key) {
  //         swap(array[j + 1], array[k]);
  //       }
  //       else{
  //         swap(array[j], array[j+1]);
  //         swap(array[k], array[j+1]);
  //       }
  //     }
  //     else{ //one child
  //       swap(array[j], array[k]);
  //     }
  //
  //     k = j;
  //   }
  //
  //
  // }

  /*
  * Writes the keys stored in the array starting at the root
  */
  void printKey(){
    for(unsigned int i = 1; i < size; ++i){
      cout << array[i].key << " ";
    }
    cout << endl;

  }

};
