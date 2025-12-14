# Add One Row to Tree

## 🧩 Problem Statement
Given the `root` of a binary tree and two integers `val` and `depth`:
- Add a row of nodes with value `val` at the given `depth`.
- The root node is at depth 1.

**Rules:**
- If `depth == 1`, create a new root with value `val`, and the original tree becomes the new root's left subtree.
- If `depth > 1`, for each non-null node at `depth - 1` (let's call it `cur`):
  - Create two nodes with value `val`.
  - `cur.left` becomes the left child of the new left node.
  - `cur.right` becomes the right child of the new right node.
  - The new left node becomes `cur.left`.
  - The new right node becomes `cur.right`.

### 🔹 Example 1:
#### Input:
```plaintext
root = [4,2,6,3,1,5], val = 1, depth = 2
```
#### Output:
```plaintext
[4,1,1,2,null,null,6,3,1,5]
```

## 🔍 Approaches

### 1. BFS / Level Order Traversal ($O(N)$)
- **Concept:** Traverse to `depth - 1`. Perform the pointer rewiring.
- **Algorithm:**
  - If `depth == 1`: New root.
  - Queue `q`. Push `root`.
  - Traverse `depth - 2` levels (to arrive at level `depth - 1`).
  - For all nodes at this level:
    - `tempLeft = node.left`
    - `tempRight = node.right`
    - `node.left = new Node(val)`
    - `node.right = new Node(val)`
    - `node.left.left = tempLeft`
    - `node.right.right = tempRight`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Worst case we traverse the whole tree.
- **Space Complexity:** $O(N)$ (Queue width).

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
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (depth == 1) {
            TreeNode* newRoot = new TreeNode(val);
            newRoot->left = root;
            return newRoot;
        }
        
        queue<TreeNode*> q;
        q.push(root);
        int currentDepth = 1;
        
        while (!q.empty()) {
            int size = q.size();
            
            // If we are at the parent level (depth - 1)
            if (currentDepth == depth - 1) {
                for (int i = 0; i < size; i++) {
                    TreeNode* node = q.front(); q.pop();
                    
                    TreeNode* oldLeft = node->left;
                    TreeNode* oldRight = node->right;
                    
                    node->left = new TreeNode(val);
                    node->right = new TreeNode(val);
                    
                    node->left->left = oldLeft;
                    node->right->right = oldRight;
                }
                break; // Done
            }
            
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front(); q.pop();
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            currentDepth++;
        }
        
        return root;
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
    public TreeNode addOneRow(TreeNode root, int val, int depth) {
        if (depth == 1) {
            TreeNode newRoot = new TreeNode(val);
            newRoot.left = root;
            return newRoot;
        }
        
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int currentDepth = 1;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            
            if (currentDepth == depth - 1) {
                for (int i = 0; i < size; i++) {
                    TreeNode node = queue.poll();
                    TreeNode oldLeft = node.left;
                    TreeNode oldRight = node.right;
                    
                    node.left = new TreeNode(val);
                    node.left.left = oldLeft;
                    
                    node.right = new TreeNode(val);
                    node.right.right = oldRight;
                }
                break;
            }
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            currentDepth++;
        } 
        return root;
    }
}
```

## 🌍 Real-World Analogy
### **Renovating a Building:**
You want to add a new floor between the 1st and 2nd floor. You jack up the 2nd floor and everything above it, insert the new floor, and connect the stairs.

## 🎯 Summary
✅ **Pointer Rewiring:** The core logic handles preserving the existing subtrees by attaching them to the newly created nodes.
