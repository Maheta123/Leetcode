# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

def get_subtree_sum(node: TreeNode, subtree_sums: list):
    if node is None:
        return 0

    total_sum = node.val

    total_sum += get_subtree_sum(node.left, subtree_sums)

    total_sum += get_subtree_sum(node.right, subtree_sums)

    subtree_sums.append(total_sum)

    return total_sum


def get_max_product(node: TreeNode):
    subtree_sums = list()

    total_sum = get_subtree_sum(node, subtree_sums)

    max_product = 0

    for s in subtree_sums:
        product = s * (total_sum - s)

        if product > max_product:
            max_product = product

    return max_product % (10**9 + 7)


class Solution:
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        return get_max_product(root)