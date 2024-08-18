#include <iostream>

void merge (int* arr, int first, int mid, int last);


void mergeSort (int* arr, int first, int end){
    if (end > first){
        int mid = first + (end - first) / 2;

        mergeSort(arr, first, mid);
        mergeSort(arr, mid + 1, end);

        merge(arr, first, mid, end);
    }
}


void merge (int* arr, int first, int mid, int last){
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;

    int size = (last - first) + 1;
    int* tmp = new int[size];
    int ind = 0;


    while ((first1 <= last1) && (first2 <= last2)){
        if(arr[first1] <= arr[first2]){
            tmp[ind] = arr[first1];
            ++first1;
        } else {
            tmp[ind] = arr[first2];
            ++first2;
        }

        ++ind;
    }


    while(first1 <= last1){
        tmp[ind] = arr[first1];
        ++first1;
        ++ind;
    }


    while(first2 <= last2) {
        tmp[ind] = arr[first2];
        ++first2;
        ++ind;
    }


    for(int i = 0; i < size; ++i){
        arr[first + i] = tmp[i];
    }

    delete[] tmp;

}


int main() {
    const size_t size = 5;
    int arr[size];

    for(int i = 0; i < size; ++i){
        std::cin >> arr[i];
    }

    mergeSort(arr, 0, size - 1);

    for(int i = 0; i < size; ++i){
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

}