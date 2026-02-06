static int cmpInt(const void *a, const void *b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

int minRemoval(int* nums, int numsSize, int k) {
    // 1) 排序：这样窗口内最小/最大就是两端
    qsort(nums, numsSize, sizeof(int), cmpInt);

    int left = 0;
    int ans = 1; // ans = 当前找到的“最长平衡窗口长度”，至少为1（单元素必平衡）

    // 2) right 从左到右扫描，每次把 nums[right] 加进窗口
    for (int right = 0; right < numsSize; right++) {

        // 3) while(窗口不满足条件) 就一直移动 left 缩小窗口
        // 注意乘法用 long long 防止溢出
        while (left <= right && (long long)nums[right] > (long long)nums[left] * (long long)k) {
            left++;
        }

        // 4) 跳出 while 后，窗口 [left..right] 是“以 right 结尾”的最大平衡窗口
        int len = right - left + 1;
        if (len > ans) ans = len;
    }

    // 5) 最少移除 = 总长度 - 最长可保留的平衡窗口长度
    return numsSize - ans;
}