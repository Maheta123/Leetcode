# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from typing import Optional
import sys

class Solution:
    def maxProduct(self, root: Optional['TreeNode']) -> int:
        sys.setrecursionlimit(10**6)
        MOD = 10**9 + 7

        # First pass: compute total sum of all nodes
        def total_sum(node: Optional['TreeNode']) -> int:
            if not node:
                return 0
            return node.val + total_sum(node.left) + total_sum(node.right)

        total = total_sum(root)

        # Second pass: compute subtree sums and track max product
        max_prod = 0
        def dfs(node: Optional['TreeNode']) -> int:
            nonlocal max_prod
            if not node:
                return 0
            s = node.val + dfs(node.left) + dfs(node.right)
            # consider splitting the edge above this subtree
            max_prod = max(max_prod, s * (total - s))
            return s

        dfs(root)
        return max_prod % MOD