class Solution(object):
    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        s = 0
        e = len(nums)-1

        while s < e:
            mid = s + (e-s)//2

            if nums[mid] > nums[e]: 
                s= mid+1
            elif nums[mid] < nums[e]:
                    e =mid
            else:
                    e -=1
        
        return nums[s]