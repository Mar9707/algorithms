#include <iostream>


/*int partition (int* arr, int first, int end){
    int pivot = arr[end];
    int i = first - 1;
   
   for(int j = first; j <= end - 1; ++j){
    if(arr[j] <= pivot){
        ++i;
        std::swap(arr[i], arr[j]);
    }
   }

   std::swap(arr[i + 1], arr[end]);
   return i + 1;
}*/



int partition (int* arr, int first, int end){
    int pivot = arr[end];
    int i = first;
    int j = end - 1;
    while (i <= j){
        while(i < end && arr[i] <= pivot){
            ++i;
        }

        while (j >= first && arr[j] > pivot){
            --j;
        }

        if(i < j){
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i], arr[end]);
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
    const int size = 7;
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