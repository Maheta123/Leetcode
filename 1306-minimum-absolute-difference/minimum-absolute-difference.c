
int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    i++;
    int temp = arr[high];
    arr[high] = arr[i];
    arr[i] = temp;
    return i;
}

void quicksort(int* arr, int low, int high) {
    if (low < high) {
        int part = partition(arr, low, high);
        quicksort(arr, low, part-1);
        quicksort(arr, part+1, high);
    }
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    quicksort(arr, 0, arrSize-1);
    int mindiff = INT_MAX;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] - arr[i-1] < mindiff) mindiff = arr[i]-arr[i-1];
    }
    int** answer = (int**)malloc(arrSize * sizeof(int*));
    *returnColumnSizes = malloc(arrSize * sizeof(int));
    int pos = 0;
    for (int i = 1; i < arrSize; i++) {
        if (arr[i]-arr[i-1] == mindiff) {
            answer[pos] = malloc(2 * sizeof(int));
            answer[pos][0] = arr[i-1];
            answer[pos][1] = arr[i];
            (*returnColumnSizes)[pos] = 2;
            pos++;
        }
    }
    *returnSize = pos;
    return answer;
}