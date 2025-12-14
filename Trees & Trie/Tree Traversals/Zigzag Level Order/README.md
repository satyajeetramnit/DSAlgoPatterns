# Binary Tree Zigzag Level Order Traversal

## 🧩 Problem Statement
Given the `root` of a binary tree, return the **zigzag level order traversal** of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

### 🔹 Example 1:
#### Input:
```plaintext
root = [3,9,20,null,null,15,7]
```
#### Output:
```plaintext
[[3],[20,9],[15,7]]
```

## 🔍 Approaches

### 1. BFS with Toggle Flag ($O(N)$)
- **Concept:** Standard BFS, but control the order of adding elements to the current level list.
- **Algorithm:**
  - Use a queue for BFS.
  - Maintain a boolean `leftToRight = true`.
  - For each level:
    - If `leftToRight` is true, add nodes to the list normally (append).
    - If `false`, add nodes to the front of the list (or reverse the list after collecting).
    - Toggle `leftToRight` after processing the level.
- **Data Structure:** A `Deque` for the current level list makes adding to front $O(1)$. Alternatively, just `reverse()` the vector at the end of the level.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ (queue width).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <algorithm>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        if (!root) return result;
        
        queue<TreeNode*> q;
        q.push(root);
        bool leftToRight = true;
        
        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                int index = leftToRight ? i : (size - 1 - i);
                level[index] = node->val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            leftToRight = !leftToRight;
            result.push_back(level);
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
    def zigzagLevelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if not root:
            return []
        
        result = []
        queue = deque([root])
        left_to_right = True
        
        while queue:
            level_size = len(queue)
            current_level = deque()
            
            for _ in range(level_size):
                node = queue.popleft()
                if left_to_right:
                    current_level.append(node.val)
                else:
                    current_level.appendleft(node.val)
                
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            result.append(list(current_level))
            left_to_right = not left_to_right
            
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
    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> result = new ArrayList<>();
        if (root == null) return result;
        
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        boolean leftToRight = true;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            LinkedList<Integer> level = new LinkedList<>();
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                if (leftToRight) {
                    level.addLast(node.val);
                } else {
                    level.addFirst(node.val);
                }
                
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            leftToRight = !leftToRight;
            result.add(level);
        }
        
        return result;
    }
}
```

## 🌍 Real-World Analogy
### **Snake Printing:**
Like an old dot-matrix printer or a snake game moving across the screen. Left-to-right, drop down, then right-to-left.

## 🎯 Summary
✅ **Direction Flag:** A simple boolean flag toggles the insertion order (append vs prepend) at each level.
