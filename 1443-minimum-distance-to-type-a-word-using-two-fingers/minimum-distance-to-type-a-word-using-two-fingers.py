diff = ord('A')
alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
distance_lookup = {}
for c1 in alphabet:
    for c2 in alphabet:
        x1, x2 = (ord(c1) - ord('A')) % 6, (ord(c2) - ord('A')) % 6
        y1, y2 = (ord(c1) - ord('A')) // 6, (ord(c2) - ord('A')) // 6
        distance_lookup[(c1, c2)] = abs(x1 - x2) + abs(y1 - y2)


class Solution:
    def minimumDistance(self, word: str) -> int:
        n = len(word)
        dp = [0] * 26
        for c1, c2 in pairwise(word):
            c1_to_c2 = distance_lookup[(c1, c2)]
            new_dp = [inf] * 26
            for c in alphabet:
                c_to_c2 = distance_lookup[(c, c2)]
                ci = ord(c) - diff

                leave_on_c = c1_to_c2 + dp[ci]
                if leave_on_c < new_dp[ci]:
                    new_dp[ci] = leave_on_c
                
                leave_on_c1 = c_to_c2 + dp[ci]
                if leave_on_c1 < new_dp[ord(c1) - diff]:
                    new_dp[ord(c1) - diff] = leave_on_c1
            dp, new_dp = new_dp, dp
            new_dp.clear()
        
        return min(dp)