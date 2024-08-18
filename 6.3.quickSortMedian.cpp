#include <iostream>
#include <vector>
#include <algorithm>

int medianOfThree(int* arr, int first, int last) {
    int mid = first + (last - first) / 2;
    int a = arr[first];
    int b = arr[mid];
    int c = arr[last];
    
    if ((a > b) != (a > c)) {
        return first;
    } else if ((b > a) != (b > c)) {
        return mid;
    } else {
        return last;
    }
}


int partition (int* arr, int first, int last){
    int pivotIndex = medianOfThree(arr, first, last);
    std::swap(arr[pivotIndex], arr[last]); 
    int pivot = arr[last];


    int i = first;
    int j = last - 1;

    while (i <= j){
        while(i < last && arr[i] <= pivot){
            ++i;
        }

        while(j >= first && arr[j] > pivot){
            --j;
        }

        if(i < j) {
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i], arr[last]);
    return i;
}


void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


int main () {
    const int size = 5;
    int arr[size] = {0};

    for (int i = 0; i < size; ++i){
        std::cin >> arr[i];
    }

    quickSort(arr, 0, size - 1);

    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << ' ';
    }

    std::cout << std::endl;
}
