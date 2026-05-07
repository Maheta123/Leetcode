class Solution:
    def maxValue(self, nums: List[int]) -> List[int]:
        n = len(nums)
        if n == 0: return []

        suffix_min = [0] * n
        suffix_min[n - 1] = nums[n - 1]
        for i in range(n - 2, -1, -1):
            suffix_min[i] = min(suffix_min[i + 1], nums[i])

        res = [0] * n
        prefix_max = float('-inf')
        chunk_start = 0

        for i in range(n):
            prefix_max = max(prefix_max, nums[i])

            if i == n - 1 or prefix_max <= suffix_min[i + 1]:
                for j in range(chunk_start, i + 1):
                    res[j] = prefix_max
                chunk_start = i + 1
                prefix_max = float('-inf')

        return res