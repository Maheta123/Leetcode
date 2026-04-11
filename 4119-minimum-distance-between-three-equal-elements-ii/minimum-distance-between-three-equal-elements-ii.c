int minimumDistance(int* nums, int numsSize) {
    if (numsSize < 3) return -1;

    int *map = (int *)malloc((numsSize + 1) * sizeof(int));
    int *nxt = (int *)malloc((numsSize) * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        map[i] = -1;
        nxt[i] = -1;
    }
    map[numsSize] = -1;

    for (int i = numsSize - 1; i >= 0; i--) {
        if (map[nums[i]] != -1) nxt[i] = map[nums[i]];
        map[nums[i]] = i;
    }
    free(map);

    int ans = 100001;
    for (int i = 0; i < numsSize; i++) {
        int secondPos = nxt[i];
        if (secondPos != -1) {
            int thirdPos = nxt[secondPos];
            if (thirdPos != -1) {
                int calc = thirdPos - i;
                ans = ans < calc ? ans : calc;
            }
        }
    }
    free(nxt);

    return ans == 100001 ? -1 : (ans << 1);
}