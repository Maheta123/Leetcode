class Solution(object):
    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        j=1
        for i in range(1,len(nums)):
                if j==1 or nums[i] != nums[j-2]:
                        nums[j]=nums[i]
                        j +=1
                        
        return j
         