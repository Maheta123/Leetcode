long long maxSumTrionic(int* nums, int numsSize) {
    long long n = numsSize;
    long long res = -(1LL << 50);
    long long pSum = nums[0];

    int l = 0, p = 0, q = 0;

    for (int r = 1; r < (int)n; r++) {
        pSum += nums[r];

        if (nums[r - 1] == nums[r]) {
            l = r;
            pSum = nums[r];
        } 
        else if (nums[r - 1] > nums[r]) {
            if (r > 1 && nums[r - 2] < nums[r - 1]) {
                p = r - 1;

                while (l < q) {
                    pSum -= nums[l++];
                }
                while (l + 1 < p && nums[l] < 0) {
                    pSum -= nums[l++];
                }
            }
        } 
        else {
            if (r > 1 && nums[r - 2] > nums[r - 1]) {
                q = r - 1;
            }
            if (l < p && p < q) {
                if (pSum > res) res = pSum;
            }
        }
    }
    return res;
}