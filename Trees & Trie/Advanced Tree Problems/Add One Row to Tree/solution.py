from typing import Optional
from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def addOneRow(self, root: Optional[TreeNode], val: int, depth: int) -> Optional[TreeNode]:
        if depth == 1:
            return TreeNode(val, left=root)
        
        queue = deque([root])
        current_depth = 1
        
        while queue:
            if current_depth == depth - 1:
                for _ in range(len(queue)):
                    node = queue.popleft()
                    old_left = node.left
                    old_right = node.right
                    
                    node.left = TreeNode(val, left=old_left)
                    node.right = TreeNode(val, right=old_right)
                break
            
            for _ in range(len(queue)):
                node = queue.popleft()
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            current_depth += 1
            
        return root

if __name__ == "__main__":
    sol = Solution()
    # [4,2,6,3,1,5], val = 1, depth = 2
    root = TreeNode(4)
    root.left = TreeNode(2)
    root.right = TreeNode(6)
    root.left.left = TreeNode(3)
    root.left.right = TreeNode(1)
    root.right.left = TreeNode(5)
    
    res = sol.addOneRow(root, 1, 2)
    print(f"Test Case 1: Root={res.val}, Left={res.left.val}, Right={res.right.val}, LeftLeft={res.left.left.val}") # Expect 4, 1, 1, 2
