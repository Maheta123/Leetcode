class Solution(object):
    def minMoves(self, nums, limit):
        # Difference array for target sums from 2 to 2 * limit
        # Size is 2 * limit + 2 to handle indices comfortably
        diff = [0] * (2 * limit + 2)
        n = len(nums)
        
        for i in range(n // 2):
            a, b = nums[i], nums[n - 1 - i]
            
            # Default: 2 moves for all possible target sums [2, 2 * limit]
            # We represent this by adding 2 at the start index
            diff[2] += 2
            diff[2 * limit + 1] -= 2
            
            # Transition to 1 move:
            # Range: [min(a, b) + 1, max(a, b) + limit]
            low = min(a, b) + 1
            high = max(a, b) + limit
            diff[low] -= 1  # 2 moves becomes 1 move
            diff[high + 1] += 1 # 1 move becomes 2 moves again
            
            # Transition to 0 moves:
            # Target: exactly a + b
            target = a + b
            diff[target] -= 1     # 1 move becomes 0 moves
            diff[target + 1] += 1 # 0 moves becomes 1 move again
            
        # Calculate prefix sums to find the minimum moves
        ans = n  # Maximum possible moves is n
        current_moves = 0
        for i in range(2, 2 * limit + 1):
            current_moves += diff[i]
            if current_moves < ans:
                ans = current_moves
                
        return ans