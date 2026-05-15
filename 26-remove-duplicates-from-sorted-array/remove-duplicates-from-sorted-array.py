class Solution(object):
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) <= 1:
            return len(nums)

        i = 1 
        k = 0

        while i < len(nums):
            if nums[i] != nums[k]:
                nums[k+1] = nums[i]
                k += 1
            i += 1
        # print(k+1)
        return k+1