/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* constructTransformedArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    
    int* result = (int*)malloc(numsSize * sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            result[i] = 0;
        } else {
            int newIndex = (i + nums[i]) % numsSize;

            if (newIndex < 0) {
                newIndex += numsSize;
            }

            result[i] = nums[newIndex];
        }
    }

    return result;
}