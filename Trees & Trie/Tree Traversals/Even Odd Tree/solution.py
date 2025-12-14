from typing import Optional
from collections import deque
import math

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        if not root:
            return True
        
        queue = deque([root])
        level = 0
        
        while queue:
            size = len(queue)
            prev_val = -math.inf if level % 2 == 0 else math.inf
            
            for _ in range(size):
                node = queue.popleft()
                
                if level % 2 == 0: # Even level
                    if node.val % 2 == 0 or node.val <= prev_val:
                        return False
                else: # Odd level
                    if node.val % 2 != 0 or node.val >= prev_val:
                        return False
                        
                prev_val = node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            level += 1
            
        return True

if __name__ == "__main__":
    sol = Solution()
    # [1,10,4,3,null,7,9,12,8,6,null,null,2]
    root = TreeNode(1)
    root.left = TreeNode(10)
    root.right = TreeNode(4)
    
    root.left.left = TreeNode(3)
    root.right.left = TreeNode(7)
    root.right.right = TreeNode(9)
    
    root.left.left.left = TreeNode(12)
    root.left.left.right = TreeNode(8)
    root.right.left.left = TreeNode(6)
    root.right.right.right = TreeNode(2)
    
    print(f"Test Case 1: {sol.isEvenOddTree(root)}") # Expect True
