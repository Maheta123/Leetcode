int compare(const void* a, const void* b) {
    int* elem1 = (int*)a;
    int* elem2 = (int*)b;
    if (elem1[1] != elem2[1]) {
        
        return elem2[1] - elem1[1];
    }
    return elem2[0] - elem1[0];
}
int* findXSum(int* nums, int numsSize, int k, int x, int* returnSize) {
    *returnSize = numsSize - k + 1;  
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    int freq[101] = {0};  
    int freqPairs[101][2]; 
    for (int i = 0; i < k; ++i) {
        freq[nums[i]]++;
    }
    for (int i = 0; i < *returnSize; ++i) {
        int count = 0;
        for (int j = 0; j <= 100; ++j) {
            if (freq[j] > 0) {
                freqPairs[count][0] = j;     
                freqPairs[count][1] = freq[j]; 
                count++;
            }
        }
        qsort(freqPairs, count, sizeof(freqPairs[0]), compare);
        int sum = 0;
        for (int j = 0; j < x && j < count; ++j) {
            sum += freqPairs[j][0] * freqPairs[j][1];
        }
        result[i] = sum;
        if (i + k < numsSize) {
            freq[nums[i]]--;    
            freq[nums[i + k]]++; 
        }
    }
    return result;
}