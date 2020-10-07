#include <iostream>
#include <time.h>
#include <chrono>
// Node for Linked List
class Node{
public:
  int val;

  Node* next = nullptr;
  Node(int num):val(num){}
};
// Linked List class
class LinkedList{
public:
  Node* head = nullptr;
  Node* tail = nullptr;

  // Add to linked list from the front of the list
  void addFront(int val){
    Node* temp = new Node(val);
    if(head == nullptr){
      head = temp;
      tail = temp;
    }else{
      temp->next = head;
      head = temp;
    }
  }
  // Add to linked list from the back of the list
  void addBack(int val){
    if(head == nullptr){
      addFront(val);
    }else{
      Node* temp = new Node(val);
      tail->next = temp;
      tail = temp;
    }
  }
  // Function to get middle Node
  Node* getMid(Node* top, Node* bottom){
    if(top == nullptr){
      return nullptr;
    }

    Node* rapido = top->next; // Fast moving pointer
    Node* lento = top; // Slow moving pointer

    while(rapido != bottom){
      rapido = rapido->next; // Fast always moves 1 more than slow
      if(rapido != bottom){
        rapido = rapido->next; // Move fast and slow down the list
        lento = lento->next;
      }
    }
    return lento; // Return slow pointer which is in the middle of the list
  }
  //Binary search Linked list
  int binaryLinked(int element){
    Node* top = head;
    Node* bottom = nullptr;

    while(bottom != nullptr || bottom != top){
      Node* mid = getMid(top,bottom); // Get middle object in the linked list
      if(mid == nullptr){
        return -1;
      }
      if(mid->val == element){ // If middle object value = element then return the value
        return mid->val;
      }
      else if(mid->val < element){ // If middle object's value is less than element then run again with start of list equaling the middle object
        top = mid->next;
      }
      else{ // If middle object is greater than element then run again with end of the list equaling the middle object
        bottom = mid;
      }
    }
    return -1; // If element not found then return -1
  }
  // Print linked list to console
  void printLL(){
    Node* current = head;
    while(current != nullptr){
      std::cout << current->val << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }
};
// Binary search an array Recursively
int binaryRecursive(int* array, int start, int finish, int element){
  if(start <= finish){
    if(finish < start){
      return -1;
    }
    int mid = (start + finish) / 2; // Get middle index
    if(array[mid] == element){ // Return index if element found
      return mid;
    }else if(element < array[mid]){ // If element is smaller than mid object recurse with the end of the array as the mid-1
      return binaryRecursive(array, start, mid-1, element);
    }else if(element > array[mid]){ // If element is greater than the mid object recurse with the start of the array as the mid+1
      return binaryRecursive(array, mid+1, finish, element);
    }
  }
  return -1; // Element not found return -1
}
// Binary search an array Irratively
int binaryIrative(int* array,int element, int size){
  int start = 0; // Variables to keep track of the ends of the array
  int finish = size;

  while(start <= finish){
    int mid = (start + finish) / 2; // Get mid index
    if(array[mid] == element){ // If element found return the index
      return mid;
    }
    if(element < array[mid]){ // If element is less than mid object then make end of the array the mid-1
      finish = mid - 1;
    }else{ // If element is grater than mid object then make start of the array mid+1
      start = mid + 1;
    }
  }
  return -1; // If element not found then return -1
}
// Swap values in an array
void swapValues(int* arr, int index1, int index2){
  int temp = *(arr+index1);
  *(arr+index1) = *(arr+index2);
  *(arr+index2) = temp;
}
// Divide array to quick sort
int divideToConquer(int* arr, int is, int der, int pivot){
  while(is <= der){
    while(arr[is] < pivot){ // While left value is smaller than pivot point move right
      ++is;
    }
    while(arr[der] > pivot){ // While right value is greater than pivot more left
      --der;
    }
    if(is <= der){ // After movement stops, if left value is greater than right then swap them.
      swapValues(arr,is,der);
      ++is; // Continue to move after swap
      --der;
    }
  }
  return is;
}
// Recursive Quick sort
void quickSortArray(int* arr, int is, int der){
  if(is >= der){ // If left is greater than the right return
    return;
  }
  int pivot = arr[(is+der) /2]; // Pivot point is the middle index of the array
  int index = divideToConquer(arr, is, der, pivot); // Get index to divide the array in half
  quickSortArray(arr,is,index-1); // Quick sort then two new halfs created
  quickSortArray(arr,index,der);
}
int main(){
  srand(time(NULL));
  // Array size
  int size = 100000000;
  // Element to search
  int element = 9999;
  // Create array
  int* list = new int[size];
  // Create Linked List
  LinkedList linked;
  // Fill array
  for(int i=0;i<size;i++){
    list[i] = rand()%(i+1);
  }
  // Slide element we are searching for into random spot in the array
  *(list+(rand()%size)) = element;
  // Sort Array
  quickSortArray(list,0,size-1);
  // Fill linked list with sorted array
  for(int i=0;i<size;i++){
    linked.addBack(*(list+i));
  }
  // Time recursive search
  auto begin = std::chrono::steady_clock::now();
  std::cout << "What index is " << element << " in?  " << binaryRecursive(list,0,size,element) << std::endl;
  auto end = std::chrono::steady_clock::now();
  auto length = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
  std::cout << "Recursive function toke: " << length << " ms" << std::endl;

  std::cout << std::endl;

  // Time irative search
  begin = std::chrono::steady_clock::now();
  std::cout << "What index is " << element << " in? " << binaryIrative(list,element,size) << std::endl;
  end = std::chrono::steady_clock::now();
  length = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
  std::cout << "Irative function toke: " << length << " ms" << std::endl;

  std::cout << std::endl;

  // Time linked search
  begin = std::chrono::steady_clock::now();
  int foundElement = linked.binaryLinked(element);
  end = std::chrono::steady_clock::now();
  length = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
  std::cout << "Linked function toke: " << length << " ms  " << "Element found was: "<< foundElement <<  std::endl;
  std::cout << std::endl;

  return 0;
}
