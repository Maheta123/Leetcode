#include <stdio.h>
#include <stdlib.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        int tmp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

int extractMax(int arr[], int *n) {
    if (*n <= 0) return -1;
    int root = arr[0];
    arr[0] = arr[*n - 1];
    (*n)--;
    heapify(arr, *n, 0);
    return root;
}

void heapInsert(int arr[], int *n, int val) {
    int i = (*n)++;
    arr[i] = val;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (arr[p] < arr[i]) {
            int tmp = arr[p];
            arr[p] = arr[i];
            arr[i] = tmp;
            i = p;
        } else break;
    }
}

int largestPerimeter(int* nums, int numsSize) {
    if (numsSize < 3) return 0;
    buildHeap(nums, numsSize);

    while (numsSize >= 3) {
        int a = extractMax(nums, &numsSize);
        int b = extractMax(nums, &numsSize);
        int c = extractMax(nums, &numsSize);

        if (b + c > a) {
            return a + b + c; 
        }

        heapInsert(nums, &numsSize, b);
        heapInsert(nums, &numsSize, c);
    }

    return 0;
}