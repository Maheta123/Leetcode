class Solution:
    def maxProductPath(self, grid):
        MOD = 10**9 + 7

        m = len(grid)
        n = len(grid[0])

        # DP table storing (maxProduct, minProduct)
        dp = [[(0, 0) for _ in range(n)] for _ in range(m)]

        dp[0][0] = (grid[0][0], grid[0][0])

        # Fill first row
        for j in range(1, n):
            max_val = dp[0][j-1][0] * grid[0][j]
            min_val = dp[0][j-1][1] * grid[0][j]
            dp[0][j] = (max_val, min_val)

        # Fill first column
        for i in range(1, m):
            max_val = dp[i-1][0][0] * grid[i][0]
            min_val = dp[i-1][0][1] * grid[i][0]
            dp[i][0] = (max_val, min_val)

        # Fill rest of grid
        for i in range(1, m):
            for j in range(1, n):

                up_max, up_min = dp[i-1][j]
                left_max, left_min = dp[i][j-1]

                values = [
                    up_max * grid[i][j],
                    up_min * grid[i][j],
                    left_max * grid[i][j],
                    left_min * grid[i][j]
                ]

                dp[i][j] = (max(values), min(values))

        max_prod, min_prod = dp[m-1][n-1]

        return -1 if max_prod < 0 else max_prod % MOD