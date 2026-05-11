class Solution(object):
    def separateDigits(self, nums):
        result=[]
        for n in nums:
            lst=[]
            while n!=0:
                lst.append(n%10)
                n//=10
            lst.reverse()
            result.extend(lst)
        return result