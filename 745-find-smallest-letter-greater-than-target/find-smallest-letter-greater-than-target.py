class Solution:
    def nextGreatestLetter(self, letters: List[str], target: str) -> str:
        re = letters[0]
        flag =False

        for ch in letters:
                if not flag:
                        if ch > target:
                                re = ch
                                flag = not flag
                        else:
                            if ch>target and ch<re:
                                    re=ch 
        
        return re
