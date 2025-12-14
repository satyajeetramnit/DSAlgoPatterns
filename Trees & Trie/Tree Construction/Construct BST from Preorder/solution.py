from typing import List, Optional
import math

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
        self.idx = 0
        n = len(preorder)
        
        def build(bound):
            if self.idx >= n or preorder[self.idx] > bound:
                return None
            
            val = preorder[self.idx]
            root = TreeNode(val)
            self.idx += 1
            
            root.left = build(val)
            root.right = build(bound)
            
            return root
            
        return build(math.inf)

def get_preorder(root):
    if not root: return []
    return [root.val] + get_preorder(root.left) + get_preorder(root.right)

if __name__ == "__main__":
    sol = Solution()
    preorder = [8,5,1,7,10,12]
    root = sol.bstFromPreorder(preorder)
    print(f"Test Case 1 (Re-Preorder): {get_preorder(root)}") # Expect [8, 5, 1, 7, 10, 12]
