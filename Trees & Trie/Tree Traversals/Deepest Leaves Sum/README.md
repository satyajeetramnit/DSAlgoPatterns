# Deepest Leaves Sum

## 🧩 Problem Statement
Given the `root` of a binary tree, return the sum of values of its deepest leaves.

### 🔹 Example 1:
#### Input:
```plaintext
root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
```
#### Output:
```plaintext
15
```
#### Explanation:
Deepest leaves are at the bottom-most level.

## 🔍 Approaches

### 1. BFS (Level Order Traversal) ($O(N)$)
- **Concept:** Traverse level by level. When we reach the last level, summing its nodes gives the answer.
- **Algorithm:**
  - Standard BFS queue.
  - Reset `sum` to 0 at the start of each level.
  - Add node values to `sum`.
  - After loop finishes, `sum` holds the sum of the last processed level.

### 2. DFS (Depth First Search) ($O(N)$)
- **Concept:** Track `maxDepth`.
- **Algorithm:**
  - if `depth > maxDepth`: update `maxDepth`, reset `sum = val`.
  - if `depth == maxDepth`: `sum += val`.

BFS is cleaner for this specific problem as "deepest level" is natural for BFS.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ (Queue width for BFS or Stack height for DFS).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int deepestLeavesSum(TreeNode* root) {
        if (!root) return 0;
        queue<TreeNode*> q;
        q.push(root);
        int sum = 0;
        
        while (!q.empty()) {
            int size = q.size();
            sum = 0; // Reset sum for new level
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        
        return sum; // Returns sum of last level processed
    }
};
```

### Python
```python
from typing import Optional
from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def deepestLeavesSum(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        
        queue = deque([root])
        level_sum = 0
        
        while queue:
            level_sum = 0
            size = len(queue)
            for _ in range(size):
                node = queue.popleft()
                level_sum += node.val
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
                    
        return level_sum
```

### Java
```java
import java.util.*;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

class Solution {
    public int deepestLeavesSum(TreeNode root) {
        if (root == null) return 0;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int sum = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            sum = 0; // Reset for new level
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                sum += node.val;
                
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
        }
        
        return sum;
    }
}
```

## 🌍 Real-World Analogy
### **Harvesting Fruit:**
You want to collect fruits only from the lowest branches of the tree because they are the ripest (deepest). You look at branches level by level, discarding the upper ones, until you reach the very bottom.

## 🎯 Summary
✅ **BFS Natural Fit:** Since we process level-by-level, the sum of the last iteration of the while loop is exactly what we need.
