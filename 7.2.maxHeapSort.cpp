#include <iostream>

void minHeapify(int* arr, int size, int ind){
    int smallest = ind;
    int left = ind *2 + 1;
    int right = ind * 2 + 2;

    if(left < size && arr[left] < arr[smallest]){
        smallest = left;
    }

    if (right < size && arr[right] < arr[smallest]){
        smallest = right;
    }

    if(smallest != ind){
        std::swap(arr[smallest], arr[ind]);
        minHeapify(arr, size, smallest);
    }
}


void build(int* arr, int size){
    for(int i = size / 2 - 1; i >= 0; --i){
        minHeapify(arr, size, i);
    }
}


void heapSort(int* arr, int size){
    build(arr, size);
    for(int i = size - 1; i > 0; --i){
        std::swap(arr[0], arr[i]);
        minHeapify(arr, i, 0);
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
