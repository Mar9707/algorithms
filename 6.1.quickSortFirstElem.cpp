#include <iostream>


int partition (int* arr, int first, int last){
    int pivot = arr[first];
    int i = first + 1;
    int j = last;
    while (i <= j){
        while(i <= last && arr[i] <= pivot){
            ++i;
        }

        while (j > first && arr[j] > pivot){
            --j;
        }

        if(i < j){
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[j], arr[first]);
    return j;
}


void quickSort(int* arr, int first, int end){
    if (first < end){
        int PIndex = partition(arr, first, end);
        quickSort(arr, first, PIndex - 1);
        quickSort(arr, PIndex + 1, end);
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