# Validate Binary Search Tree

## 🧩 Problem Statement
Given the `root` of a binary tree, determine if it is a valid binary search tree (BST).

A **valid BST** is defined as follows:
- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree of a node contains only nodes with keys **greater than** the node's key.
- Both the left and right subtrees must also be binary search trees.

### 🔹 Example 1:
#### Input:
```plaintext
root = [2,1,3]
```
#### Output:
```plaintext
true
```

## 🔍 Approaches

### 1. Recursion with Range (DFS) ($O(N)$)
- **Concept:** Every node value must fall within a specific valid range `(min, max)`.
  - Root: `(-inf, +inf)`
  - Left child: `(min, root.val)`
  - Right child: `(root.val, max)`
- **Algorithm:**
  - `validate(node, min, max)`
  - Base case: if `node` is `null`, return `true`.
  - Check: `if node.val <= min` or `node.val >= max`, return `false`.
  - Recurse: `validate(node.left, min, node.val) && validate(node.right, node.val, max)`.

### 2. Inorder Traversal ($O(N)$)
- **Concept:** An inorder traversal of a BST yields sorted values.
- **Algorithm:**
  - Traverse inorder.
  - Keep track of `prev_val`.
  - If `curr_val <= prev_val`, return `false`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ (recursion stack).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
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
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
    
    bool validate(TreeNode* node, long minVal, long maxVal) {
        if (!node) return true;
        
        if (node->val <= minVal || node->val >= maxVal) return false;
        
        return validate(node->left, minVal, node->val) && 
               validate(node->right, node->val, maxVal);
    }
};
```

### Python
```python
from typing import Optional
import math

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def validate(node, min_val, max_val):
            if not node:
                return True
            
            if not (min_val < node.val < max_val):
                return False
            
            return validate(node.left, min_val, node.val) and \
                   validate(node.right, node.val, max_val)
                   
        return validate(root, -math.inf, math.inf)
```

### Java
```java
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
    public boolean isValidBST(TreeNode root) {
        return validate(root, null, null);
    }
    
    // Using Integer objects allows passing null for infinity
    private boolean validate(TreeNode node, Integer min, Integer max) {
        if (node == null) return true;
        
        if ((min != null && node.val <= min) || (max != null && node.val >= max)) {
            return false;
        }
        
        return validate(node.left, min, node.val) && validate(node.right, node.val, max);
    }
}
```

## 🌍 Real-World Analogy
### **Organizational Salary Caps:**
A Boss earns X. Everyone reporting to them on the "Low Budget" team (Left) must earn strictly less than X (but more than their own subordinates' limits). Everyone on the "High Budget" team (Right) must earn strictly more than X (but less than the Boss's Boss).

## 🎯 Summary
✅ **Range Propagation:** The key is to narrow the valid range `(min, max)` as we traverse down.
