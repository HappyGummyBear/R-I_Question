#include <iostream>
#include <time.h>
#include <chrono>
// Binary search an array Recursively
int binaryRecursive(int* array, int start, int finish, int element){
  if(start <= finish){
    if(finish < start){
      return -1;
    }
    int mid = (start + finish)/2;
    if(array[mid] == element){
      return mid;
    }else if(element < array[mid]){
      return binaryRecursive(array, start, mid-1, element);
    }else if(element > array[mid]){
      return binaryRecursive(array, mid+1, finish, element);
    }
  }
  return -1;
}
// Binary search an array Irratively
int binaryIrative(int* array,int element, int size){
  int start = 0;
  int finish = size-1;

  while(start <= finish){
    int mid = (finish + start) / 2;
    if(array[mid] == element){
      return mid;
    }
    if(element < array[mid]){
      finish = mid - 1;
    }else{
      start = mid + 1;
    }
  }
  return -1;
}

int main(){
  srand(time(NULL));
  // Array size
  int size = 100000;
  // Element to search
  int element = 77;
  // Create array
  int* list = new int[size];
  // Fill array
  for(int i=0;i<size;i++){
    *(list+i) = i+1;
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

  return 0;
}
