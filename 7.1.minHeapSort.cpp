#include <iostream>


void maxHeapify (int* arr, int size, int ind){
   int largest = ind;
   int left = ind * 2 + 1;
   int right = ind * 2 + 2;

   if(left < size && arr[left] > arr[largest]){
      largest = left;
   } 

   if(right < size && arr[right] > arr[largest]) {
      largest = right;
   }

   if(largest != ind){
      std::swap(arr[ind], arr[largest]);
      maxHeapify(arr, size, largest);
   }
}


void build (int* arr, int size){
   for(int i = size / 2 - 1; i >= 0; --i){
      maxHeapify(arr, size, i);
   }
}

void heapSort(int* arr, int size){
   build(arr, size);
   for(int i = size - 1; i > 0; --i){
      std::swap(arr[0], arr[i]);
      maxHeapify(arr, i, 0);
   }
}


int main () {
   const size_t size = 7;
   int arr[size] = {0};

   for(int i = 0; i < size; ++i){
      std::cin >> arr[i];
   }

   heapSort(arr, size);

   for(int num : arr){
      std::cout << num << ' ';
   }

   std::cout << std::endl;
   return 0;
}
