
class Solution(object):
    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        min = 999999

        for i in range(len(nums)):
                if nums[i] < min:
                        min = nums[i]
        
        return min