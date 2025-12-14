from typing import Optional
from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        
        # queue stores (node, index)
        queue = deque([(root, 0)])
        max_width = 0
        
        while queue:
            level_length = len(queue)
            _, level_start_index = queue[0]
            
            for i in range(level_length):
                node, index = queue.popleft()
                
                if node.left:
                    queue.append((node.left, 2 * index))
                if node.right:
                    queue.append((node.right, 2 * index + 1))
                    
                if i == level_length - 1:
                    max_width = max(max_width, index - level_start_index + 1)
                    
        return max_width

if __name__ == "__main__":
    sol = Solution()
    # [1,3,2,5,3,null,9]
    root = TreeNode(1)
    root.left = TreeNode(3)
    root.right = TreeNode(2)
    root.left.left = TreeNode(5)
    root.left.right = TreeNode(3)
    root.right.right = TreeNode(9)
    
    print(f"Test Case 1: {sol.widthOfBinaryTree(root)}") # Expect 4
