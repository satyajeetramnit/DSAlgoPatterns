from typing import List
from collections import deque

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        parents = {}
        
        def dfs(node, parent):
            if not node:
                return
            parents[node] = parent
            dfs(node.left, node)
            dfs(node.right, node)
            
        dfs(root, None)
        
        queue = deque([target])
        visited = set([target])
        dist = 0
        
        while queue:
            if dist == k:
                return [node.val for node in queue]
            
            size = len(queue)
            for _ in range(size):
                curr = queue.popleft()
                
                for neighbor in [curr.left, curr.right, parents[curr]]:
                    if neighbor and neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
                        
            dist += 1
            
        return []

if __name__ == "__main__":
    sol = Solution()
    # [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
    root = TreeNode(3)
    root.left = TreeNode(5)
    root.right = TreeNode(1)
    root.left.left = TreeNode(6)
    root.left.right = TreeNode(2)
    root.right.left = TreeNode(0)
    root.right.right = TreeNode(8)
    root.left.right.left = TreeNode(7)
    root.left.right.right = TreeNode(4)
    
    target = root.left # 5
    
    result = sol.distanceK(root, target, 2)
    result.sort()
    print(f"Test Case 1: {result}") # Expect [1, 4, 7]
