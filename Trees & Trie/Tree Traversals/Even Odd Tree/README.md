# Even Odd Tree

## 🧩 Problem Statement
A binary tree is named **Even-Odd** if it meets the following conditions:
1. The root of the binary tree is at level index `0`, its children are at level index `1`, their children are at level index `2`, etc.
2. For every **even-indexed** level, all nodes at the level have **odd** integer values in **strictly increasing** order (from left to right).
3. For every **odd-indexed** level, all nodes at the level have **even** integer values in **strictly decreasing** order (from left to right).

Given the `root` of a binary tree, return `true` if the binary tree is **Even-Odd**, otherwise return `false`.

### 🔹 Example 1:
#### Input:
```plaintext
root = [1,10,4,3,null,7,9,12,8,6,null,null,2]
```
#### Output:
```plaintext
true
```

## 🔍 Approaches

### 1. BFS with Level Tracking ($O(N)$)
- **Concept:** Use Breadth-First Search (BFS) to traverse level by level.
- **Constraints Check:**
  - For each level index `level`:
    - **Even Level:** vals must be **odd** and **increasing**.
    - **Odd Level:** vals must be **even** and **decreasing**.
- **Algorithm:**
  - BFS Queue. Track `level_index`.
  - For each level, keep track of `prev_val`.
  - Check parity: `val % 2` must match expected (odd for even level, even for odd level).
  - Check order: Compare `val` with `prev_val` (increasing/decreasing).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

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
    bool isEvenOddTree(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q;
        q.push(root);
        int level = 0;
        
        while (!q.empty()) {
            int size = q.size();
            int prev_val = (level % 2 == 0) ? INT_MIN : INT_MAX;
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                // Check parity
                if (level % 2 == 0) { // Even level: odd vals, increasing
                    if (node->val % 2 == 0 || node->val <= prev_val) return false;
                } else { // Odd level: even vals, decreasing
                    if (node->val % 2 != 0 || node->val >= prev_val) return false;
                }
                
                prev_val = node->val;
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            level++;
        }
        return true;
    }
};
```

### Python
```python
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
    public boolean isEvenOddTree(TreeNode root) {
        if (root == null) return true;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int level = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            int prevVal = (level % 2 == 0) ? Integer.MIN_VALUE : Integer.MAX_VALUE;
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                
                if (level % 2 == 0) { // Even level: odd vals, increasing
                    if (node.val % 2 == 0 || node.val <= prevVal) return false;
                } else { // Odd level: even vals, decreasing
                    if (node.val % 2 != 0 || node.val >= prevVal) return false;
                }
                
                prevVal = node.val;
                
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            level++;
        }
        return true;
    }
}
```

## 🌍 Real-World Analogy
### **Strict Dress Code Party:**
A party with multiple floors. Floor 0 (Ground) requires people to wear Odd colors and line up by height (Short -> Tall). Floor 1 requires Even colors and line up Tall -> Short. Security checks every floor strictly.

## 🎯 Summary
✅ **Level-wise check:** Validating both parity and sorting order at each step.
