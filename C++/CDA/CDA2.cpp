#include <iostream> // cin and cout
#include <cstdlib> // ifstream, ofstream
#include <cmath>

using namespace std;

/*************************************************************/
template<typename elmtype>
class CDA{
private:
  int size; // length of the current array
  int capacity; //size of the array uncluding elements not used
  bool ordered; // is it in order?
  elmtype* array; //main array for inserting front and end
  int front; //front of the array. sit at the back. makes insert O(1)
  int end; //end of the array. makes addend O(1)

public:
  //Default Constructor
  CDA() {
    size = 0;
    capacity = 1;
    ordered = false;
    array = new elmtype[0];
    front = 0; // no values in the array front is at element 0
    end = 0; // no values in the array end is at element 0
  }
/************************************************************************/
  //Constructor with capacity and size s with ordered = false
  CDA(int s){
    size = s;
    capacity = s;

    array = new elmtype[s];

    front = s-1;
    end = s-1;

    ordered = false;
  }
/************************************************************************/
  //Destructor for the class
  ~CDA() {
    delete[] array;
  }
/************************************************************************/
  // Frees any space currently used and starts over with an
  // array of capacity 1 and size 0.
  void Clear(){
    delete[] array;

    size = 0;
    capacity = 1;
    ordered = false;
    array = new elmtype[0];
    front = 0; // no values in the array front is at element 0
    end = 0; // no values in the array end is at element 0
  }
/************************************************************************/
  /* Traditional [] operator. Should print a message if is
  out of bounds and return a reference to value of type
  elmtype stored in the class for this purpose */
  elmtype& operator[](int i){
    if (i >= size)
    {
        cout << "Array index out of bound, exiting";
        exit(0);
    }
    return array[i];
  }
/************************************************************************/
/************************************************************************/
  /* increases the size of the array by 1 and stores v at the
  end of the array. Should double the capacity when the new element
  doesn't fit. If ordered is true, chek to be sure that the array
  is still in order */
  void AddEnd(elmtype v){
     // if size == capacity must double the array

    if(size == 0){ //empty array
      array = new elmtype[2]; //inserting first element so it needs to be doubled
      array[0] = v;
      size += 1; //size of the array is one
      capacity += 1; //capacity is now 2. never goes below zero
      front = 1; //array only has one open spot at [1]
      end = 1; //array only has one open spot at [1]

      return;
    }

    //if size is not zero then there are elements in the array so lets
    //increase the size by one since we are adding a new element and
    //check to see if the array is about to be full
    size += 1;

    if(size >= capacity){ // array is about to be full
      array[end] = v; //add new elemnt then double size
      elmtype *temp;
      temp = new elmtype[size];
      temp = array;
      array = new elmtype[(capacity * 2)];


      for(unsigned i = 0; i < size; i++) {
        array[i] = temp[i];
      }

      capacity *= 2; // new capacity because array was doubled
      front = capacity -1; //new front because array was doubled
      end = size; // new end because element was added
    }
    else { // adding another value to the array and there is room to put it
      array[end] = v;
      end += 1;
    }


    ordered = Ordered(); // check to see if array is still in order

    return;
  }
/************************************************************************/
/************************************************************************/
  /* increases the size of the array by 1 and stores v at the beginning of the
  array. Should double the capacity when the new element doesn't fit. The new
  element should be the item returned at index 0. if ordered is true, check
  to be sure that the array is is still in order. */
  void AddFront(elmtype v){

   if(size == 0){ //empty array
     array = new elmtype[2]; //inserting first element so it needs to be doubled
     array[0] = v;
     size += 1; //size of the array is one
     capacity += 1; //capacity is now 2. never goes below zero

     front = 1; //array only has one open spot at [1]
     end = 1; //array only has one open spot at [1]

     return;
   }

   size += 1; //capacity never changes unless array doubles or reduced by half

   //if size is not zero then there are elements in the array so lets
   //increase the size by one since we are adding a new element and
   //check to see if the array is about to be full
   if(size >= capacity){ // array is about to be full
     array[front] = v; //add new elemnt then double size
     elmtype *temp;
     temp = new elmtype[size];
     temp = setArray(temp);
     array = new elmtype[(capacity * 2)];

     for(unsigned i = 0; i < size; i++) {
       array[i] = temp[i];
     }

     capacity *= 2; // new capacity because array was doubled
     front = capacity -1; //new front because array was doubled
     end = size; // new end because element was added to full array so adding to
     //the front is also like adding to the end. They share the same spot
   }
   else { // adding another value to the array and there is room to put it
     array[front] = v;

     if(front == 0){
       front = capacity - 1;
     }
     else{
       front -= 1;
     }

   }

   ordered = Ordered(); // check to see if array is still in order

   return;
 }
/************************************************************************/
/************************************************************************/
  /* reduces the size of the array by 1 at the end. Should shrink the capacity when
  only 25% of the array is in use after the delete. The capacity should never go
  below 1 */
  void DelEnd(){
    if(size == 0){ // size == 0 then there is nothing to delete
      return;
    }

    end -= 1; //bring end to spot where element not wanted is
    size -= 1; //size of the array "changes". the value is still there but will
    //be overwritten if new element is to be added

    float check = (float)size/(float)capacity; // checks the amount of the array that is being "used"
    //for all the user knows

    if(check <= 0.25){ //reduce the size of the array
      elmtype *temp;
      temp = new elmtype[capacity];

      temp = setArray(temp);

      capacity = capacity/2;

      array = new elmtype[capacity];

      for(unsigned i = 0; i < size; i++) {
        array[i] = temp[i];
        end = size;
      }

      front = capacity -1;
    }
  }
/************************************************************************/
/************************************************************************/
  /* reduces the size of the array by 1 at the beggining of the array. Should shrink
  the capacity when only 25% of the array is in use after the delete. the capacity
  should never go below 1 */
  void DelFront(){
    if(size == 0){ // size == 0 then there is nothing to delete
      return;
    }

    front += 1; //bring front to spot where element not wanted is "deleted"
    size -= 1; //size of the array "changes". the value is still there but will
    //be overwritten if new element is to be added
    if(front == capacity){
      front = 0;
    }

    float check = (float)size/(float)capacity; // checks the amount of the array that is being "used"
    //for all the user knows

    if(check <= 0.25){ //reduce the size of the array
      elmtype *temp;
      temp = new elmtype[capacity];

      temp = setArray(temp);

      capacity = capacity/2;

      array = new elmtype[capacity];

      for(unsigned i = 0; i < size; i++) {
        array[i] = temp[i];
        end = size;
      }

      front = capacity -1;
    }

  }
/************************************************************************/
/************************************************************************/
  // returns the size of the array
  int Length(){
    return size; // returns the number of elements that have been added to array
  }
/************************************************************************/
/************************************************************************/
  //returns the capacity of the array
  int Capacity() {
    return capacity;
  }
/************************************************************************/
/************************************************************************/
  //returns the status of the ordered
  bool Ordered(){
    return ordered;
  }
/************************************************************************/
//   /* Check to see if the array is in order. Set the order flag appropiately.
//   Return 1 if the array was ordered and -1 otherwise */
  int SetOrdered(){
    int h = 0;
    int head = front;
    int tail = end;
    elmtype check;


    head += 1;


    //starting at an element cause head is at empty space
    if(head == capacity){ // if array starts at array[0]
      head = 0;

      for(unsigned i = head + 1; i < tail; ++i) {
        if(array[i] < array[h]) {
          return -1;
        }
      }

      return 1;
    }
    else {
      //if there are elements at the "front" which is in the back of the array
      check = array[head];
      head += 1;
      for(unsigned i = head; i < capacity; ++i) { //adding "front elements"
        if(array[i] < check){
          return -1;
        }
        check = array[i];
      }

      for(unsigned i = 0; i < end; ++i) { //adding elements that were added to "end"
        if(array[i] < check){
          return -1;
        }
        check = array[i];
      }

    }

  //otherwise it passes the test and the array is in order!!
  return 1;
  }
/************************************************************************/
/************************************************************************/
  /* returns the k^th smallest element in the array. If ordered is true then
  return the item at index k-1. Otherwise use the quickselect algorithm. Quickselect
  should choose a random partition element. */
  elmtype Select(int k){
    elmtype *temp;
    temp = new elmtype[size-1];
    temp = setArray(temp);
    elmtype value;
    ordered = Ordered();

    if(ordered == true){
      value = temp[k-1];
      return value;
    }
    else {
      int l = 0;
      int r = size - 1;
      int pivot = rand() % size;
      swap(temp[pivot], temp[r]);

      value = runQuickSelect(temp, l, r, k);

    }

    return value;
  }
/************************************************************************/
  elmtype runQuickSelect(elmtype* temp, int l, int r, int k){

    int index = Partition(temp, l, r);

    if(index - 1 == k - 1){
      index -= 1;
      return temp[index];
    }

    if(index - 1 > k -1){
      return runQuickSelect(temp, l, index - 1, k);
    }
    else{
      return runQuickSelect(temp, index + 1, r, k - index + l - 1);
    }
  }
/************************************************************************/
  int Partition(elmtype* arr, int l, int r){
    int i = l;
    int p = arr[r];

    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= p) {
          swap(arr[j], arr[i]);
          i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
  }
/************************************************************************/
/************************************************************************/
  //Performs insertion sort on the array. Sets ordered to be true.
  void InsertionSort(){
    elmtype *temp;
    temp = new elmtype[size];
    temp = setArray(temp);
    ordered = true;
    array = new elmtype[capacity];

    for(unsigned int i = 0; i < size; ++i){
      array[i] = temp[i];
      end = size;
      front = capacity - 1;
    }

    for(unsigned int i = 0; i < size; ++i){
      for(unsigned int j = i; j > 0; --j){
        if(array[j] < array[j-1]){
          swap(array[j], array[j-1]);
        }
      }
    }

    return;
  }
  /************************************************************************/
  /************************************************************************/
  /* Sorts the values in the array using the quicksort algorithm. This should
  pick the partition value using the median of three technique. Set ordered to
  true. Should also make us of insertion sort to improve perfromance. */
  void QuickSort(){
    elmtype *temp;
    temp = new elmtype[size-1];
    temp = setArray(temp);
    ordered = true;
    array = new elmtype[capacity];

    for(unsigned int i = 0; i < size; ++i){
      array[i] = temp[i];
      end = size;
      front = capacity - 1;
    }

    int l = 0;
    int r = size - 1;

    runQuickSort(array, l, r);

  }
/************************************************************************/
  void runQuickSort(elmtype* array, int l, int r){
    int mid = (l + r) / 2;

    if(l < r) {

      if(array[mid] < array[l]){
        swap(array[mid], array[l]);
      }

      if(array[r] < array[l]){
        swap(array[r], array[l]);
      }

      if(array[r] < array[mid]){
        swap(array[r], array[mid]);
      }

      //place pivot at high - 1
      swap(array[mid], array[r]);

      int index = 0;
      index = Partition(array, l, r);

      runQuickSort(array, l, index - 1);
      runQuickSort(array, index + 1, r);
    }

  }
/************************************************************************/
/************************************************************************/
  /* sorts the values in the array using counting sort, where the values
  in the array are in the range 0....m Set ordered to be true. You may assume that
  all values in the array are integers in the range 0...m */
  void CountingSort(int m){
    elmtype *temp;
    temp = new elmtype[size-1];
    temp = setArray(temp);

    ordered = true;
    unsigned int i, h;
    int add = 0;

    elmtype *countSort;
    countSort = new elmtype[m + 1];
    elmtype index;
    int loop;

    array = new elmtype[capacity];

    for(i = 0; i < m + 1; ++i) {
      countSort[i] = 0;;
    }

    for(i = 0; i < size; ++i) {//set up count array
      index = temp[i];
      countSort[index] += 1;
    }

    for(i = 0; i < m + 1; ++i) { //using count array to sort array
      if(countSort[i] != 0){
        loop = countSort[i];
        for(h = 0; h < loop; ++h){ //insert number loop amount of time
          array[add] = i;
          ++add; // adding sorted elements to original array
        }
      }
    }

    end = size;
    front = capacity - 1;
  }

/************************************************************************/
/************************************************************************/
  /* if ordered is true, perform a binary search of the array looking for the
  item e. Otherwise perform linear search. Returns the index of the item if found
  or -1 otherwise. */
  int Search(elmtype e){
    ordered = Ordered();
    elmtype *temp;
    temp = new elmtype[size];
    int mid = size / 2;

    temp = setArray(temp);

    if(ordered == true){// run binary search
      for(unsigned int i = 0; i < log2 (size); ++i) {
        if(e == temp[mid]){
          return mid;
        }
        else if(e > temp[mid]){
          mid += (mid/2);
        }
        else if(e < temp[mid]){
          mid -= (mid/2);
        }
      }
    }
    else{
      for(unsigned int i = 0; i < size; ++i){
        if(e == temp[i]){
          return i;
        }
      }
    }

  return -1;
  }
/************************************************************************/
/************************************************************************/
  elmtype* setArray(elmtype* temp){ //done
    // elmtype *temp;
    // temp = new elmtype[size];
    int h = 0;
    int i;
    int head = front;
    int tail = end;

    head += 1;
    //starting at an element cause head is at empty space
    if(head == capacity){ // if array starts at array[0]
      head = 0;
      for(unsigned i = head; i < tail; ++i) {
        temp[i] = array[i];
      }

      return temp;
    }

    //if there are elements at the "front" which is in the back of the array
    for(unsigned i = head; i < capacity; ++i) { //adding "front elements"
      temp[h] = array[i];
      ++h;
    }

    for(unsigned i = 0; i < end; ++i) { //adding elements that were added to "end"
      temp[h] = array[i];
      ++h;
    }

    return temp;
  }


};
