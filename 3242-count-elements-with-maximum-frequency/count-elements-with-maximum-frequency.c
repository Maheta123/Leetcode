int maxFrequencyElements(int* nums, int numsSize) {
    int freq[101] = {0}; // assuming nums[i] <= 100
    int i, maxFreq = 0, sum = 0;

    // Count frequencies
    for(i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Find max frequency
    for(i = 0; i < 101; i++) {
        if(freq[i] > maxFreq) {
            maxFreq = freq[i];
        }
    }

    // Sum all occurrences of elements with max frequency
    for(i = 0; i < 101; i++) {
        if(freq[i] == maxFreq) {
            sum += freq[i];
        }
    }

    return sum;
}
