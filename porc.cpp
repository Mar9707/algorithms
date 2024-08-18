    #include <iostream>
    #include <vector>
    #include <limits>
    
    
    int findKthPositive(std::vector<int>& arr, int k) {
        int size = arr.size();
        int last = arr.back();
        int missed = last - size;

        if(missed == 0){
            return last + k;
        } else if(missed > 0){
            int start = 0;
            int end = size - 1;
            while(start <= end){
                int mid = start + (end - start) / 2;
                int diff = arr[mid] - mid;

                if (diff == 1){
                    start = mid + 1;
                } else if (diff > 1){
                    if(k - diff + 1 == 1){
                        int num = 1;
                        for(int i = 0; i < mid; ){
                            if(arr[i] != num){
                                --k;
                                ++num;
                            } else {
                                ++i;
                                ++num;
                            }

                        }
                        return num;
                    } else if (k - diff + 1 > 1){
                        start = mid + 1;
                    }
                }
            }
        }
        return -1;
    }


int main () {
    std::vector<int> arr;
    int k = 0;
    int size = 0;
    std::cout << "enter size" << std::endl;
    std::cin >> size;

    std::cout << "enter " << size << " number" << std::endl;
    for (int i = 0; i < size; ++i){
        int num = 0;
        std::cin >> num;
        arr.push_back(num);
    }
 
    std::cout << "enter k" << std::endl;
    std::cin >> k;
    std::cout << findKthPositive(arr, k) << std::endl;
}