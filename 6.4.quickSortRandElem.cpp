#include <iostream>
#include <random>

int randomPivot(int first, int end) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(first, end);
    return dis(gen);
}


int partition (int* arr, int first, int last){
    int PIndex = randomPivot(first, last);
    int pivot = arr[PIndex];
    std::swap(arr[PIndex], arr[last]);
    int i = first;
    int j = last - 1;
    while (i <= j){
        while(i <= last && arr[i] < pivot){
            ++i;
        }

        while (j >= first && arr[j] >= pivot){
            --j;
        }

        if(i < j){
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i], arr[last]);
    return i;
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