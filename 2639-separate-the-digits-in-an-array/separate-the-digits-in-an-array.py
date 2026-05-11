class Solution(object):
    def separateDigits(self, nums):
        result = []
        for num in nums:
            # Convert number to string, then split into digits
            digits = [int(ch)  for ch in str(num)]
            result.extend(digits)
        
        return result

        