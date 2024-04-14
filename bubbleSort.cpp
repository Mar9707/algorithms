#include <iostream>

void bubbleSort(int* arr, const size_t size){
   for (int i = 0; i < size; ++i){
      for (int j = 0; j < size - 1; ++j){
         if (arr[j] >= arr[j + 1]){
            std::swap(arr[j], arr[j + 1]);
         }
      }
   }
}


int main() {
	const size_t size = 5;
	int arr[size];
   std::cout << "Enter the array elements" << std::endl;
	for(int i = 0; i < size; ++i){
		std::cin >> arr[i];
	}

	bubbleSort(arr, size);
	for(int i = 0; i < size; ++i){
		std::cout << arr[i] << ' ';
	}

	std::cout << std::endl;
	return 0;
}

