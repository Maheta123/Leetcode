static int cmp(const void*a, const void*b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}
int minRemoval(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), cmp);
    int i = 0;
    for (int j = 0; j < numsSize; j++){
        if (i <= j && (long long)nums[j] > (long long)nums[i] * k){
            i++;
        }
    }
    return i;
}