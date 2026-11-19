

void insertion_sort(int arr[], int n){
    if(n < 2) return;

    for(int i = 1; i < n; i++){
        int key = arr[i];
        int j = i;

        while(j > 0 && arr[j - 1] > key){
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;   
    }
}


static int partition(int arr[], int left, int right){
    int pivot = arr[right -1];
    int i = left;

    for(int j = left; j < (right - 1); j++){
        if(arr[j] <= pivot){
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }

    int temp = arr[i];
    arr[i] = arr[right -1];
    arr[right -1] = temp;

    return i;
}

static void quick_sort_recursive(int arr[], int left, int right, int random_pivot){
    if (right - left <= 1) {
        return;
    }

    int pivot_index;

    if (random_pivot) {
        pivot_index = left + (int)rand() % (right - left);
    } else {
        pivot_index = left;
    }

    int temp = arr[pivot_index];
    arr[pivot_index] = arr[right -1];
    arr[right -1] = temp;

    int p = partition(arr, left, right);

    quick_sort_recursive(arr, left, p, random_pivot);
    quick_sort_recursive(arr, p + 1, right, random_pivot);
}

void quick_sort_first_pivot(int arr[], int n) {
    quick_sort_recursive(arr, 0, n, 0);
}

void quick_sort_random_pivot(int arr[], int n) {
    quick_sort_recursive(arr, 0, n, 1);
}