#include <iostream>
#include <algorithm> 

void countingSort (int* arr, int size){
    int max = *std::max_element(arr, arr + size);
    int min = *std::min_element(arr, arr + size);

    int range = max - min + 1;
    int count[range] = {0};


    for(int i = 0; i < size; ++i){
        count[arr[i] - min]++;
    }

    int ind = 0;
    for(int i = 0; i < range; ++i){
        while(count[i] > 0){
            arr[ind] = i + min;
            ++ind;
            --count[i];
        }
    }
}


int main() {
    const size_t size = 5;
    int arr[size];

    for(int i = 0; i < size; ++i){
        std::cin >> arr[i];
    }

    countingSort(arr, size);

    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

}