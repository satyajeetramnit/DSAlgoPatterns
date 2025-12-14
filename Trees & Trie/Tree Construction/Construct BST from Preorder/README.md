# Construct Binary Search Tree from Preorder Traversal

## 🧩 Problem Statement
Given an array of integers `preorder`, which represents the **preorder traversal** of a BST (Binary Search Tree), construct the tree and return its root.

It is guaranteed that there is always possible to find a binary search tree with the given preorder traversal.

### 🔹 Example 1:
#### Input:
```plaintext
preorder = [8,5,1,7,10,12]
```
#### Output:
```plaintext
[8,5,10,1,7,null,12]
```

## 🔍 Approaches

### 1. Recursion with Bounds ($O(N)$)
- **Concept:** The first element is the root. Elements smaller than root go left, larger go right.
- **Optimization:** Instead of scanning for the split point every time (like in general BT construction), we can pass a `bound` (or `min, max` range) down the recursion.
- **Algorithm:**
  - Maintain a global index `idx` (or pass it).
  - Recursively call `build(bound)`:
    - If `preorder[idx]` > `bound`, return null.
    - Create `root` with `preorder[idx]`. Increment `idx`.
    - `root.left = build(root.val)` (upper bound for left child is current root's value).
    - `root.right = build(bound)` (upper bound for right child is the parent's upper bound).
    - Return `root`.

### 2. Monotonic Stack ($O(N)$)
- **Concept:** Iterative simulation of recursion.

We will use the **Recursion with Bounds** approach as it is cleanest and $O(N)$.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Each element is processed once.
- **Space Complexity:** $O(N)$ for recursion stack (worst case skewed tree) or $O(\log N)$ (balanced).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <climits>
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
    int idx = 0;
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        idx = 0;
        return build(preorder, INT_MAX);
    }
    
    TreeNode* build(vector<int>& preorder, int bound) {
        if (idx >= preorder.size() || preorder[idx] > bound) {
            return nullptr;
        }
        
        TreeNode* root = new TreeNode(preorder[idx++]);
        root->left = build(preorder, root->val);
        root->right = build(preorder, bound);
        
        return root;
    }
};
```

### Python
```python
from typing import List, Optional
import math

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
        self.idx = 0
        n = len(preorder)
        
        def build(bound):
            if self.idx >= n or preorder[self.idx] > bound:
                return None
            
            val = preorder[self.idx]
            root = TreeNode(val)
            self.idx += 1
            
            root.left = build(val)
            root.right = build(bound)
            
            return root
            
        return build(math.inf)
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
    int idx = 0;
    
    public TreeNode bstFromPreorder(int[] preorder) {
        idx = 0;
        return build(preorder, Integer.MAX_VALUE);
    }
    
    private TreeNode build(int[] preorder, int bound) {
        if (idx >= preorder.length || preorder[idx] > bound) {
            return null;
        }
        
        TreeNode root = new TreeNode(preorder[idx++]);
        root.left = build(preorder, root.val);
        root.right = build(preorder, bound);
        
        return root;
    }
}
```

## 🌍 Real-World Analogy
### **Sorting Mail:**
You have a pile of numbered envelopes (Preorder). You take the first one (8). You know anything smaller (1-7) belongs in the left bin, anything larger (9+) belongs in the right bin. You repeat this recursively for each bin's pile.

## 🎯 Summary
✅ **Bound Optimization:** Using the BST property allows us to avoid $O(N^2)$ searching for the split point.
