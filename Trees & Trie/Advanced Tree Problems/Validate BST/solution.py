from typing import Optional
import math

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def validate(node, min_val, max_val):
            if not node:
                return True
            
            if not (min_val < node.val < max_val):
                return False
            
            return validate(node.left, min_val, node.val) and \
                   validate(node.right, node.val, max_val)
                   
        return validate(root, -math.inf, math.inf)

if __name__ == "__main__":
    sol = Solution()
    root = TreeNode(2)
    root.left = TreeNode(1)
    root.right = TreeNode(3)
    
    print(f"Test Case 1: {sol.isValidBST(root)}") # Expect True
