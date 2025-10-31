/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getSneakyNumbers(int* nums, int numsSize, int* returnSize) {
    int ind = 0;
    int* freq = (int*)calloc(101 , sizeof(int));
    for(int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }
    for(int i = 0; i < 101; i++) {
        if(freq[i] == 2) {
            nums[ind] = i;
            ind++;
        }
    }
    free(freq);
    *returnSize = 2;
    return nums;
}