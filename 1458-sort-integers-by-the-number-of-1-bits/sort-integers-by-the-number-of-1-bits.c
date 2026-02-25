static int cmp(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    int bitsX = __builtin_popcount(x);
    int bitsY = __builtin_popcount(y);

    if (bitsX == bitsY)
        return x - y; 

    return bitsX - bitsY;  
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortByBits(int* arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;
    int* result = (int*)malloc(arrSize * sizeof(int));
    if (!result) 
        return NULL;
    for (int i = 0; i < arrSize; i++)
        result[i] = arr[i];
    qsort(result, arrSize, sizeof(int), cmp);

    return result;
}