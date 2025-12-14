from typing import List, Optional

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        inorder_map = {val: i for i, val in enumerate(inorder)}
        self.pre_idx = 0
        
        def array_to_tree(left, right):
            if left > right:
                return None
            
            root_val = preorder[self.pre_idx]
            self.pre_idx += 1
            root = TreeNode(root_val)
            
            root.left = array_to_tree(left, inorder_map[root_val] - 1)
            root.right = array_to_tree(inorder_map[root_val] + 1, right)
            
            return root
            
        return array_to_tree(0, len(preorder) - 1)

def get_preorder(root):
    if not root: return []
    return [root.val] + get_preorder(root.left) + get_preorder(root.right)

if __name__ == "__main__":
    sol = Solution()
    preorder = [3,9,20,15,7]
    inorder = [9,3,15,20,7]
    root = sol.buildTree(preorder, inorder)
    print(f"Test Case 1 (Re-Preorder): {get_preorder(root)}") # Expect [3, 9, 20, 15, 7]
