class Solution(object):
    def minPairSum(self, nums):
        return nums.sort() or max(nums[i]+nums[-1-i] for i in range((len(nums)>>1)+1))
        