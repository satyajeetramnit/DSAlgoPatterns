from typing import List, Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        stack = []
        for num in nums:
            curr = TreeNode(num)
            while stack and stack[-1].val < num:
                curr.left = stack.pop()
            
            if stack:
                stack[-1].right = curr
            
            stack.append(curr)
            
        return stack[0] if stack else None

if __name__ == "__main__":
    sol = Solution()
    nums = [3,2,1,6,0,5]
    root = sol.constructMaximumBinaryTree(nums)
    print(f"Test Case 1: Root={root.val}, Left={root.left.val}, Right={root.right.val}") # Expect Root=6, Left=3, Right=5
