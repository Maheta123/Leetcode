class Solution:
    def numOfWays(self, n: int) -> int:
        MOD = 10**9 + 7
        
        # Base case for n = 1
        A = 6  # ABC type
        B = 6  # ABA type
        
        for _ in range(n - 1):
            newA = (2 * A + 2 * B) % MOD
            newB = (2 * A + 3 * B) % MOD
            A, B = newA, newB
        
        return (A + B) % MOD
