# All Nodes Distance K in Binary Tree

## 🧩 Problem Statement
Given the `root` of a binary tree, the value of a `target` node target, and an integer `k`, return an array of the values of all nodes that have a distance `k` from the `target` node.

### 🔹 Example 1:
#### Input:
```plaintext
root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
```
#### Output:
```plaintext
[7,4,1]
```
#### Explanation:
Nodes 7 and 4 are distance 2 down from 5. Node 1 is distance 2 up-then-down from 5 (5->3->1).

## 🔍 Approaches

### 1. Convert to Graph (Parent Pointers) + BFS ($O(N)$)
- **Concept:** Trees are directed graphs (Parent -> Child). To move "up" towards the parent, we need to treat edges as undirected.
- **Algorithm:**
  1. **DFS:** Traverse the tree to build a `parent_map` (`node -> parent`) so we can move upwards.
  2. **BFS:** Start BFS from the `target` node.
     - Use a `visited` set to avoid cycling back.
     - Level 0: `target`.
     - Level 1: `target`'s left, right, and parent.
     - Repeat `k` times.
     - The nodes in the queue at level `k` are the answer.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. We verify each node twice (once for parent map, once for BFS).
- **Space Complexity:** $O(N)$ for parent map and recursion/queue.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    unordered_map<TreeNode*, TreeNode*> parent;
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        buildParents(root, nullptr);
        
        queue<TreeNode*> q;
        unordered_set<TreeNode*> visited;
        
        q.push(target);
        visited.insert(target);
        
        int current_dist = 0;
        
        while (!q.empty()) {
            if (current_dist == k) {
                vector<int> result;
                while (!q.empty()) {
                    result.push_back(q.front()->val);
                    q.pop();
                }
                return result;
            }
            
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* curr = q.front(); q.pop();
                
                if (curr->left && !visited.count(curr->left)) {
                    q.push(curr->left);
                    visited.insert(curr->left);
                }
                if (curr->right && !visited.count(curr->right)) {
                    q.push(curr->right);
                    visited.insert(curr->right);
                }
                if (parent[curr] && !visited.count(parent[curr])) {
                    q.push(parent[curr]);
                    visited.insert(parent[curr]);
                }
            }
            current_dist++;
        }
        
        return {};
    }
    
    void buildParents(TreeNode* node, TreeNode* par) {
        if (!node) return;
        parent[node] = par;
        buildParents(node->left, node);
        buildParents(node->right, node);
    }
};
```

### Python
```python
from typing import List
from collections import deque

class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        parents = {}
        
        def dfs(node, parent):
            if not node:
                return
            parents[node] = parent
            dfs(node.left, node)
            dfs(node.right, node)
            
        dfs(root, None)
        
        queue = deque([target])
        visited = set([target])
        dist = 0
        
        while queue:
            if dist == k:
                return [node.val for node in queue]
            
            size = len(queue)
            for _ in range(size):
                curr = queue.popleft()
                
                for neighbor in [curr.left, curr.right, parents[curr]]:
                    if neighbor and neighbor not in visited:
                        visited.add(neighbor)
                        queue.append(neighbor)
                        
            dist += 1
            
        return []
```

### Java
```java
import java.util.*;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

class Solution {
    Map<TreeNode, TreeNode> parents = new HashMap<>();
    
    public List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        buildParents(root, null);
        
        Queue<TreeNode> queue = new LinkedList<>();
        Set<TreeNode> visited = new HashSet<>();
        
        queue.offer(target);
        visited.add(target);
        
        int dist = 0;
        
        while (!queue.isEmpty()) {
            if (dist == k) {
                List<Integer> result = new ArrayList<>();
                for (TreeNode node : queue) {
                    result.add(node.val);
                }
                return result;
            }
            
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode curr = queue.poll();
                
                if (curr.left != null && !visited.contains(curr.left)) {
                    visited.add(curr.left);
                    queue.offer(curr.left);
                }
                if (curr.right != null && !visited.contains(curr.right)) {
                    visited.add(curr.right);
                    queue.offer(curr.right);
                }
                if (parents.containsKey(curr) && !visited.contains(parents.get(curr))) {
                    TreeNode parent = parents.get(curr);
                    if (parent != null) { // parent map might have null for root
                        visited.add(parent);
                        queue.offer(parent);
                    }
                }
            }
            dist++;
        }
        
        return new ArrayList<>();
    }
    
    private void buildParents(TreeNode node, TreeNode parent) {
        if (node == null) return;
        parents.put(node, parent);
        buildParents(node.left, node);
        buildParents(node.right, node);
    }
}
```

## 🌍 Real-World Analogy
### **Fire Spreading:**
Imagine a forest fire starts at a specific tree (Target Node).
- In 1 minute (Distance 1), the fire spreads to all directly connected trees (Left child, Right child, and Parent).
- In 2 minutes, it spreads to their neighbors.
- We want to find which trees catch fire exactly at minute `K`. Converting the tree to a graph (adding parent pointers) allows the fire to spread in all directions.

## 🎯 Summary
✅ **Tree to Graph:** The trick is unlocking upward movement by storing parents.
