#include "search.h"

int linear_search(const int arr[], int n, int target){
    for(int i = 0; i <n; i++){
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}

int binary_search(const int arr[], int n, int target){
    int left = 0;
    int right = n-1; 

    while(left <= right && target >= arr[left] && target <= arr[right]){   
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return (int)mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            if (mid == 0) break;
            right = mid - 1;
        }
    }

    return -1;
}


int interpolation_search(const int arr[], int n, int target){
    int left = 0;
    int right = n-1; 

    while(left <= right && target >= arr[left] && target <= arr[right]){   
        if (arr[left] == arr[right]) {
            if (arr[left] == target) return (int)left;
            break;
        }

        int pos = left + (int)(((double)(target - arr[left]) / (arr[right] - arr[left])) * (right - left));

        if (arr[pos] == target) {
            return (int)pos;
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            if (pos == 0) break;
            right = pos - 1;
        }
        
    }

    return -1;
}