# Binary Tree Level Order Traversal

## 🧩 Problem Statement
Given the `root` of a binary tree, return the **level order traversal** of its nodes' values. (i.e., from left to right, level by level).

### 🔹 Example 1:
#### Input:
```plaintext
root = [3,9,20,null,null,15,7]
```
#### Output:
```plaintext
[[3],[9,20],[15,7]]
```

## 🔍 Approaches

### 1. Breadth-First Search (BFS) ($O(N)$)
- **Concept:** Use a queue to traverse the tree level by level.
- **Algorithm:**
  1. If `root` is null, return empty.
  2. Initialize a queue with `root`.
  3. While queue is not empty:
     - Get the number of nodes at the current level (`size = q.size()`).
     - Iterate `size` times:
       - Pop a node.
       - Add its value to the current level list.
       - Push its valid children (left, then right) to the queue.
     - Add the current level list to the result.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Each node is visited once.
- **Space Complexity:** $O(N)$ or more specifically $O(W)$ where $W$ is the maximum width of the tree (for the queue).

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(currentLevel);
        }
        
        return result;
    }
};
```

### Python
```python
from typing import List, Optional
from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        
        result = []
        queue = deque([root])
        
        while queue:
            level_size = len(queue)
            current_level = []
            
            for _ in range(level_size):
                node = queue.popleft()
                current_level.append(node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.append(current_level)
            
        return result
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
    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            List<Integer> currentLevel = new ArrayList<>();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                currentLevel.add(node.val);
                
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            result.add(currentLevel);
        }
        
        return result;
    }
}
```

## 🌍 Real-World Analogy
### **Organizational Chart:**
Traversing a company hierarchy level by level. First the CEO (Level 1), then all VPs (Level 2), then all Directors (Level 3), and so on.

## 🎯 Summary
✅ **Queue is Key:** BFS strictly relies on a FIFO queue to process nodes level by level.
