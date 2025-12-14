# Construct Binary Tree from Preorder and Inorder Traversal

## 🧩 Problem Statement
Given two integer arrays `preorder` and `inorder` where `preorder` is the preorder traversal of a binary tree and `inorder` is the inorder traversal of the same tree, construct and return the binary tree.

### 🔹 Example 1:
#### Input:
```plaintext
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
```
#### Output:
```plaintext
[3,9,20,null,null,15,7]
```

## 🔍 Approaches

### 1. Hash Map + Recursion ($O(N)$)
- **Observations:**
  - **Preorder** (Root, Left, Right): The first element `preorder[0]` is always the **Root**.
  - **Inorder** (Left, Root, Right): If we find the Root in `inorder` array, everything to its left belongs to the **Left Subtree**, and everything to its right belongs to the **Right Subtree**.
- **Algorithm:**
  1. Build a Hash Map `inorder_map` for $O(1)$ lookups of values in `inorder` array.
  2. Recursive function `build(pre_start, pre_end, in_start, in_end)`:
     - Base Case: if `pre_start > pre_end` or `in_start > in_end`, return `null`.
     - `root_val = preorder[pre_start]`.
     - Create `root = TreeNode(root_val)`.
     - Find `root_index` in `inorder` using map.
     - Calculate `left_subtree_size = root_index - in_start`.
     - **Recursive Left:** `build(pre_start + 1, pre_start + left_subtree_size, in_start, root_index - 1)`.
     - **Recursive Right:** `build(pre_start + 1 + left_subtree_size, pre_end, root_index + 1, in_end)`.
     - Return `root`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Building the map takes $O(N)$, and each node is processed once.
- **Space Complexity:** $O(N)$ for the recursion stack and hash map.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <unordered_map>
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
    unordered_map<int, int> inorder_map;
    int pre_idx = 0;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        pre_idx = 0;
        inorder_map.clear();
        for (int i = 0; i < inorder.size(); i++) {
            inorder_map[inorder[i]] = i;
        }
        return build(preorder, 0, inorder.size() - 1);
    }
    
    TreeNode* build(vector<int>& preorder, int in_left, int in_right) {
        if (in_left > in_right) return nullptr;
        
        int root_val = preorder[pre_idx++];
        TreeNode* root = new TreeNode(root_val);
        
        int index = inorder_map[root_val];
        
        root->left = build(preorder, in_left, index - 1);
        root->right = build(preorder, index + 1, in_right);
        
        return root;
    }
};
```

### Python
```python
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
    int pre_idx = 0;
    Map<Integer, Integer> map = new HashMap<>();
    
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        pre_idx = 0;
        map.clear();
        for (int i = 0; i < inorder.length; i++) {
            map.put(inorder[i], i);
        }
        return build(preorder, 0, inorder.length - 1);
    }
    
    private TreeNode build(int[] preorder, int left, int right) {
        if (left > right) return null;
        
        int root_val = preorder[pre_idx++];
        TreeNode root = new TreeNode(root_val);
        
        int index = map.get(root_val);
        
        root.left = build(preorder, left, index - 1);
        root.right = build(preorder, index + 1, right);
        
        return root;
    }
}
```

## 🌍 Real-World Analogy
### **Reconstructing a Family Tree:**
Imagine you have a list of all family members.
- **Preorder (Roll Call):** The Great-Grandfather is listed first, then his eldest child's branch, then the next child's branch... This tells you *who is the root*.
- **Inorder (Photo Lineup):** Everyone is standing in a line from Left (youngest branch) to Right (oldest branch).
- By picking the "Root" from Preorder, you can find them in the Inorder lineup. Everyone to their left is in the Left Subtree, and everyone to their right is in the Right Subtree.
  - **Preorder:** "I am the ancestor, then my first child's entire clan, then my second child's entire clan".
  - **Inorder:** "My first child's clan is on my left, ME, then my second child's clan is on my right".
  - Knowing "ME" (Preorder) tells you where to split the crowd (Inorder) into Left and Right clans.

## 🎯 Summary
✅ **Root Identification:** Preorder gives the root. Inorder gives the structure (left vs right subtree).
