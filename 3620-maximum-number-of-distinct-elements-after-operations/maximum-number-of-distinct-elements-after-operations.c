#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int cmpInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int maxDistinctElements(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), cmpInt);
    int min = nums[0] - k;
    int ans = 1;
    for(int i = 1; i < numsSize; i++) {
        int curr = nums[i];
        if(min < curr + k) {
            ans++;
            if(min < curr - k) {
                min = curr - k;
            } else
                min++;
        }
    }
    return ans;
}