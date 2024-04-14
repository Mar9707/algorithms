#include <iostream>

int binarySearch(int* arr, int target, int left, int right){
   if (right < left){
      return -1;
   }

   int mid = left + (right - left) / 2;

   if (arr[mid] == target){
      return mid;
   } else if (arr[mid] > target){
      return binarySearch(arr, target, left, mid - 1);
   } else {
      return binarySearch(arr,target,  mid + 1, right);
   } 

}


int main () {
   const size_t size = 5;
   int arr[size] {};
   int target = 0;

   std::cout << "Please enter the array elements in sorted order." << std::endl;

   for (int i = 0; i < size; ++i){
      std::cin >> arr[i];
   }


   std::cout << "Enter Your target" << std::endl;
   std::cin >> target;

   std::cout <<"Is the index of your target " << binarySearch(arr, target, 0, size - 1) << std::endl;
   return 0;
}


