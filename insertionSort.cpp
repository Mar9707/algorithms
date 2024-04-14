#include <iostream>

void insertionSort (int* arr, const int size){
   for (int i = 1; i < size; ++i){
      int key = arr[i];
      int j = i - 1;
      while (j >= 0 && arr[j] > key){
         arr[j + 1] =  arr[j];
         --j;
      }

      arr[j + 1] = key;
   }
}


int main () {
   const int size = 5;
   int arr[size] = {2, 5, 3, 4, 1};
   insertionSort(arr, size);
   for (int i = 0; i < size; ++i){
      std::cout << arr[i];
   }

   std::cout << std::endl;
   return 0;
}
