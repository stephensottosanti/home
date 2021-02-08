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
    array = new elmtype[1];
    front = 0; // no values in the array front is at element 0
    end = 0; // no values in the array end is at element 0
  }

  //Constructor with capacity and size s with ordered = false
  CDA(int s){
    size = s;
    capacity = s;

    array = new elmtype[s];
    // for(unsigned i = 0; i < s; i++){
    //   array[i] = nullptr;
    // }

    front = 0;
    end = 0;

    ordered = false;
  }

  //Destructor for the class
  ~CDA() {
    delete[] array;
  }

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
    size += 1; //capacity never changes unless array doubles or reduced by half
    if(size == capacity){ // array is about to be full
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
      end += 1; // new end because element was added
    }
    else { // adding another value to the array and there is room to put it
      array[end] = v;
      end += 1;
    }


    ordered = Ordered(); // check to see if array is still in order

    return;
  }

  /* increases the size of the array by 1 and stores v at the beginning of the
  array. Should double the capacity when the new element doesn't fit. The new
  element should be the item returned at index 0. if ordered is true, check
  to be sure that the array is is still in order. */
  void AddFront(elmtype v){
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

   size += 1; //capacity never changes unless array doubles or reduced by half

   // if(front == 0){ //front element was "deleted" before so front was sitting
   // //at array [0]
   //   array[0] = v;
   //   //cout << array[front];
   //   front = capacity -1;
   //   return;
   // }

   //if size is not zero then there are elements in the array so lets
   //increase the size by one since we are adding a new element and
   //check to see if the array is about to be full

   if(size == capacity){ // array is about to be full
     array[front] = v; //add new elemnt then double size
     elmtype *temp;
     temp = new elmtype[size];
     temp = setArray();
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
     front -= 1;
   }

   ordered = Ordered(); // check to see if array is still in order

   return;
 }

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

    float check = size/capacity; // checks the amount of the array that is being "used"
    //for all the user knows

    if(check <= 0.25){ //reduce the size of the array
      elmtype *temp;
      temp = new elmtype[capacity];

      for(unsigned i = 0; i < capacity; i++) {
        temp[i] = array[i];
      }

      capacity = capacity/2;

      array = new elmtype[capacity];

      for(unsigned i = 0; i < size; i++) {
        array[i] = temp[i];
      }

      front = capacity -1;
    }
  }

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
    if((front) == capacity){
      front = 0;
    }

    float check = size/capacity; // checks the amount of the array that is being "used"
    //for all the user knows

    if(check <= 0.25){ //reduce the size of the array
      elmtype *temp;
      temp = new elmtype[capacity];
      setArray(&temp);
      //temp = array;
      capacity = capacity/2;

      array = new elmtype[capacity];

      for(unsigned i = 0; i < size; i++) {
        array[i] = temp[i];
      }

      front = capacity -1;
    }
  }


  // returns the size of the array
  int Length(){
    return size; // returns the number of elements that have been added to array
  }

  //returns the capacity pf the array
  int Capacity() {
    return capacity;
  }

  //Frees any space currently used and starts over with an array of Capacity 1 and size 0
  void Clear(){
    delete[] array; //deletes array and frees up space
    CDA(); //creates new array with size 0 and capacity 1
  }

//   //returns the status of the ordered
  bool Ordered(){
    int i = SetOrdered();

    if(i == 1) {
      return true;
    }

    //else return false
    return false;
  }

//   /* Check to see if the array is in order. Set the order flag appropiately.
//   Return 1 if the array was ordered and -1 otherwise */
  int SetOrdered(){
    elmtype *temp;
    temp = new elmtype[capacity];
    int h = 0;
    int head = front;
    int tail = end;

    temp = setArray();
    //head += 1;
    if(capacity == 2){ // means theres only 1 element. has to be True
      return 1;
    }
    else{
      //if(head == capacity){ // meaning nothing was added to the back so start at array[0]
        for(unsigned i = 1; i < size; ++i){
          if(temp[i] < temp[h]) {
            return -1;
          }
          ++h;
        }
      }
  //otherwise it passes the test and the array is in order!!
  return 1;
  }

  /* returns the k^th smallest element in the array. If ordered is true then
  return the item at index k-1. Otherwise use the quickselect algorithm. Quickselect
  should choose a random partition element. */
  elmtype Select(int k){
    elmtype *temp;
    temp = new elmtype[capacity];
    setArray(&temp);
    elmtype value;
    ordered = Ordered();


    if(ordered == true){
      value = temp[k-1];
      return value;
    }
    // else {
    //   int rand = rand() % (size - capacity);
    //
    //   int pivot = temp[rand];
    //   int j = l;
    //   for (int i = 0; i <= (size - capacity) - 1; i++) {
    //       if (arr[i] <= x) {
    //           swap(arr[j], arr[i]);
    //           j++;
    //       }
    //   }
    //   swap(arr[i], arr[r]);
    //   return i;
    //
    // }

    return value;
  }

//   //Performs insertion sort on the array. Sets ordered to be true.
//   void InsertionSort(){
//     elmtype *temp;
//     elmtype hold;
//     elmtype value;
//     temp = setArray();
//     ordered = true;
//     array = new elmtype[size];
//     array[0] = 0;
//     int i;
//
//     for(unsigned i = 0; i < temp.size(); ++i){
//       if(i == 0){
//         array[i] = temp[0];
//       }
//       else if(temp[i] >= array[i-1]){
//         array[i] = temp[i];
//       }
//       else if(temp[i] < array[i-1]){
//         hold = array[i-1];
//         array[i-1] = temp[i];
//         array[i] = hold;
//       }
//     }
//
//     return;
//   }
//
//   /* Sorts the values in the array using the quicksort algorithm. This should
//   pick the partition value using the median of three technique. Set ordered to
//   true. Should also make us of insertion sort to improve perfromance. */
//   void QuickSort(){
//     elmtype pivot;
//     elmtype *temp;
//     elmtype *quick;
//     elmtype *left[size/2];
//     elmtype *right[size/2];
//     int left = 0;
//     int right = 0;
//     elmtype value;
//     temp = setArray();
//     quick = temp;
//     ordered = true;
//     array = new elmtype[size];
//     int i;
//     int val = size - capacity;
//
//     val = temp[(val+1)/2]; //pivot spot
//
//     for(i = 0; i < size; ++i) {
//
//     }
//
//
//     return;
//   }
//
//   /* sorts the values in the array using counting sort, where the values
//   in the array are in the range 0....m Set ordered to be true. You may assume that
//   all values in the array are integers in the range 0...m */
//   void CountingSort(int m){
//     elmtype *temp;
//     elmtype hold;
//     elmtype value;
//     temp = setArray();
//     int tempSize = size - capacity;
//     ordered = true;
//     array = new elmtype[size];
//     int i, h;
//     int add = 0;
//     elmtype *countSort[m] = {0};
//     int index = 0;
//     int loop;
//
//     for(i = 0; i < tempSize; ++i) {//set up count array
//       index = temp[i];
//       countSort[index] += 1;
//     }
//
//     for(i = 0; i < m; ++i) { //using count array to sort array
//       if(countSort[i] != 0){
//         loop = countSort[i];
//         for(h = 0; h < loop; ++h){ //insert number loop amount of time
//           array[add] = i;
//           ++add; // adding sorted elements to original array
//         }
//       }
//     }
//     end = size - capacity;
//     front = size - 1;
//
//     return;
//   }
//
  /* if ordered is true, perform a binary search of the array looking for the
  item e. Otherwise perform linear search. Returns the index of the item if found
  or -1 otherwise. */
  int Search(elmtype e){
    ordered = Ordered();
    elmtype *temp;
    temp = new elmtype[size];
    int mid = size / 2;

    temp = setArray();

    if(ordered == true){// run binary search
      temp = setArray();
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

  elmtype* setArray(){ //done
    elmtype *temp;
    temp = new elmtype[size];
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
