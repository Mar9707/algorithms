#include <iostream>


int binarySearch (int* arr, const size_t size, int target){
   int left = 0; 
   int right = size - 1;

   while (right >= left){
      int mid = left + (right - left) / 2;
        
      if (arr[mid] == target){
         return mid;
      } else if (arr[mid] < target){
         left = mid + 1;
      } else {
         right = mid - 1;
      }

   }

   return -1;
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

   std::cout <<"Is the index of your target " << binarySearch(arr, size, target) << std::endl;
   return 0;
}
