# Maximum Binary Tree

## 🧩 Problem Statement
You are given an integer array `nums` with no duplicates. A **maximum binary tree** can be built recursively from `nums` using the following algorithm:
1. Create a root node whose value is the maximum value in `nums`.
2. Recursively build the left subtree on the subarray prefix to the left of the maximum value.
3. Recursively build the right subtree on the subarray suffix to the right of the maximum value.

Return the **maximum binary tree** built from `nums`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [3,2,1,6,0,5]
```
#### Output:
```plaintext
[6,3,5,null,2,0,null,null,1]
```
#### Explanation:
- Max is 6. Root is 6. Left: [3,2,1], Right: [0,5].
- Left of 6: Max is 3. Root 3. Left: [], Right: [2,1].
- Right of 3: Max is 2. Root 2. Left: [], Right: [1].
- Right of 6: Max is 5. Root 5. Left: [0], Right: [].

## 🔍 Approaches

### 1. Recursive Construction ($O(N^2)$)
- **Concept:** Find max in current range, make it root, recurse left and right.
- **Time Complexity:** $O(N^2)$ in worst case (sorted array), $O(N \log N)$ average.

### 2. Monotonic Stack ($O(N)$)
- **Concept:** Iterate through numbers. Keep a stack of nodes on the "right path" from root to current leaf.
- **Algorithm:**
  - For each number `num`:
    - Create `curr = TreeNode(num)`.
    - Pop from stack while `stack.top < curr`. The last popped node becomes `curr.left` (it effectively finds its parent which is `curr` for now).
    - If stack is not empty, `stack.top.right = curr` (current is the right child of the closest larger number on left).
    - Push `curr`.
  - The bottom of the stack is the root.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Each node pushed and popped at most once.
- **Space Complexity:** $O(N)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <stack>
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
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> stk;
        for (int num : nums) {
            TreeNode* curr = new TreeNode(num);
            while (!stk.empty() && stk.back()->val < num) {
                curr->left = stk.back();
                stk.pop_back();
            }
            if (!stk.empty()) {
                stk.back()->right = curr;
            }
            stk.push_back(curr);
        }
        return stk.front();
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
    def constructMaximumBinaryTree(self, nums: List[int]) -> Optional[TreeNode]:
        stack = []
        for num in nums:
            curr = TreeNode(num)
            while stack and stack[-1].val < num:
                curr.left = stack.pop()
            
            if stack:
                stack[-1].right = curr
            
            stack.append(curr)
            
        return stack[0] if stack else None
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
    public TreeNode constructMaximumBinaryTree(int[] nums) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        for (int num : nums) {
            TreeNode curr = new TreeNode(num);
            while (!stack.isEmpty() && stack.peek().val < num) {
                curr.left = stack.pop();
            }
            if (!stack.isEmpty()) {
                stack.peek().right = curr;
            }
            stack.push(curr);
        }
        return stack.isEmpty() ? null : stack.peekLast();
    }
}
```

## 🌍 Real-World Analogy
### **Building a Pyramid:**
You place blocks. If a bigger block comes, it crushes everything smaller before it (makes them its left children). If it's smaller, it sits on the right shoulder of the last block.

## 🎯 Summary
✅ **Cartesian Tree:** This is essentially constructing a Cartesian tree from an array.
