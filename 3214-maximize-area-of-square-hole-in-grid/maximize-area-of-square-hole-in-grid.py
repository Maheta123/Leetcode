class Solution(object):
    def maximizeSquareHoleArea(self, n, m, hBars, vBars):
        def longest_consecutive(bars):
            bars.sort()
            longest = curr = 1
            for i in range(1, len(bars)):
                if bars[i] == bars[i - 1] + 1:
                    curr += 1
                else:
                    curr = 1
                longest = max(longest, curr)
            return longest

        max_h = longest_consecutive(hBars) + 1
        max_v = longest_consecutive(vBars) + 1

        side = min(max_h, max_v)
        return side * side
