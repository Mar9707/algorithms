#include <iostream>
#include <algorithm>


void countingSort (int* arr, int size, int exp){
    const int base = 10;

    int output[size];
    int count[base] = {0};

    for (int i = 0; i < size; ++i){
        ++count[(arr[i] / exp) % base];
    }

    for (int i = 1; i < base; ++i){
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % base] - 1] = arr[i];
        --count[(arr[i] / exp) % base];
    }

    for (int i = 0; i < size; ++i){
        arr[i] = output[i];
    }
}


void radixSort(int arr[], int n) {
    int max = *std::max_element(arr, arr + n);

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}


int main() {
    const size_t size = 5;
    int arr[size];

    for(int i = 0; i < size; ++i){
        std::cin >> arr[i];
    }

    radixSort(arr, size);

    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

}