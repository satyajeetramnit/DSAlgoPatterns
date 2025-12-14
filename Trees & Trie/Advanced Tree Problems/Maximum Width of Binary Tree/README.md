# Maximum Width of Binary Tree

## 🧩 Problem Statement
Given the `root` of a binary tree, return the **maximum width** of the given tree.

The **maximum width** of a tree is the maximum **width** among all levels.

The **width** of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

### 🔹 Example 1:
#### Input:
```plaintext
root = [1,3,2,5,3,null,9]
```
#### Output:
```plaintext
4
```
#### Explanation:
The maximum width is at level 3: 5, 3, null, 9. The width is `4`.

## 🔍 Approaches

### 1. BFS with Indexing ($O(N)$)
- **Concept:** Heap-style indexing for binary trees:
  - If a parent is at index `i`, its left child is at `2 * i`, and right child is at `2 * i + 1`.
- **Handling Overflow:** The indices can grow very large (2^depth). Since we only care about the *difference* between max and min index at each level, we can normalize the indices.
  - At the start of each level, `min_index = queue.front().index`.
  - For every node in the level, `current_index = node.index - min_index`.
  - Next level children indices: `2 * current_index` and `2 * current_index + 1`.
- **Algorithm:**
  - BFS Queue stores pairs `(node, index)`.
  - For each level:
    - Get `size`.
    - `start = queue.front().index`, `end = queue.back().index`.
    - `width = end - start + 1`.
    - Update `max_width`.
    - Process children with normalized indices.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$.

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
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        
        // Use unsigned long long to prevent overflow without manual normalization
        // (though normalization is safer generally, ULL is sufficient for standard test cases)
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});
        unsigned long long maxWidth = 0;
        
        while (!q.empty()) {
            int size = q.size();
            unsigned long long minIndex = q.front().second;
            unsigned long long firstIndex = 0, lastIndex = 0;
            
            for (int i = 0; i < size; i++) {
                // Normalize to prevent overflow in extremely deep trees (conceptually)
                // In C++, unsigned arithmetic wraps around correctly for difference, 
                // but direct index calculation requires care.
                // Normalization: index - minIndex
                unsigned long long curIndex = q.front().second - minIndex;
                TreeNode* node = q.front().first;
                q.pop();
                
                if (i == 0) firstIndex = curIndex;
                if (i == size - 1) lastIndex = curIndex;
                
                if (node->left) q.push({node->left, 2 * curIndex});
                if (node->right) q.push({node->right, 2 * curIndex + 1});
            }
            maxWidth = max(maxWidth, lastIndex - firstIndex + 1);
        }
        return (int)maxWidth;
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
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        
        # queue stores (node, index)
        queue = deque([(root, 0)])
        max_width = 0
        
        while queue:
            level_length = len(queue)
            _, level_start_index = queue[0]
            
            for i in range(level_length):
                node, index = queue.popleft()
                
                if node.left:
                    queue.append((node.left, 2 * index))
                if node.right:
                    queue.append((node.right, 2 * index + 1))
                    
                if i == level_length - 1:
                    max_width = max(max_width, index - level_start_index + 1)
                    
        return max_width
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
    public int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;
        
        Queue<Pair<TreeNode, Integer>> queue = new LinkedList<>();
        queue.offer(new Pair<>(root, 0));
        int maxWidth = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            int minIndex = queue.peek().getValue(); // Normalize indices
            int firstIndex = 0, lastIndex = 0;
            
            for (int i = 0; i < size; i++) {
                Pair<TreeNode, Integer> pair = queue.poll();
                TreeNode node = pair.getKey();
                int curIndex = pair.getValue() - minIndex;
                
                if (i == 0) firstIndex = curIndex;
                if (i == size - 1) lastIndex = curIndex;
                
                if (node.left != null) queue.offer(new Pair<>(node.left, 2 * curIndex));
                if (node.right != null) queue.offer(new Pair<>(node.right, 2 * curIndex + 1));
            }
            maxWidth = Math.max(maxWidth, lastIndex - firstIndex + 1);
        }
        return maxWidth;
    }
    
    // Simple Pair class
    static class Pair<K, V> {
        K key; V value;
        public Pair(K key, V value) { this.key = key; this.value = value; }
        public K getKey() { return key; }
        public V getValue() { return value; }
    }
}
```

## 🌍 Real-World Analogy
### **Panoramic Photo:**
You're taking a panoramic photo of a mountain range (tree). The width of the photo depends on the leftmost peak and the rightmost peak at any given elevation, including the empty air (nulls) between them.

## 🎯 Summary
✅ **Indexing Strategy:** Assigning indices like `2*i` and `2*i+1` maps a binary tree to an array structure, allowing easy width calculation.
