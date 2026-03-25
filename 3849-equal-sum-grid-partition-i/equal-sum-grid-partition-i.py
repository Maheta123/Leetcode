class Solution(object):
    def canPartitionGrid(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: bool
        """
        def check(A):
            curr = 0
            for r in A:
                curr += sum(r)
                if 2* curr == total:
                    return True
            return False
        total = sum(sum(r) for r in grid)
        return check(grid) or check(zip(*grid))
