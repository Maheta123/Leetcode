class Solution:
    def minimumCost(self, v):
        n = len(v)
        s = v[0]
        v[1:n] = sorted(v[1:n])
        s = s + v[1] + v[2]
        return s