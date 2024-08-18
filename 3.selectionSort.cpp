#include <iostream>

void selectionSort(int* arr, const size_t size){
   for (int i = 0; i < size - 1; ++i){
      int min = i;
      for (int j = i + 1; j < size; ++j){
         if (arr[j] < arr[min]){
            min = j;
         }
      }

      std::swap(arr[i], arr[min]);
   }
}


int main() {
	const size_t size = 5;
	int arr[size];
   std::cout << "Enter the array elements" << std::endl;
	for(int i = 0; i < size; ++i){
		std::cin >> arr[i];
	}

	selectionSort(arr, size);
	for(int i = 0; i < size; ++i){
		std::cout << arr[i] << ' ';
	}

	std::cout << std::endl;
	return 0;
}

