# Time Needed to Inform All Employees

## 🧩 Problem Statement
A company has `n` employees with a unique ID for each employee from `0` to `n - 1`. The head of the company is the one with `headID`.

Each employee has one direct manager given in the `manager` array where `manager[i]` is the direct manager of the `i-th` employee, `manager[headID] = -1`. Also, it is guaranteed that the subordination relationships have a tree structure.

The head of the company wants to inform all the employees of the company of an urgent piece of news. He will inform his direct subordinates, and they will inform their subordinates, and so on until all employees know about the urgent news.

The `i-th` employee needs `informTime[i]` minutes to inform all of his direct subordinates (i.e., After `informTime[i]` minutes, all his direct subordinates can start spreading the news).

Return the number of minutes needed to inform all the employees about the urgent news.

### 🔹 Example 1:
#### Input:
```plaintext
n = 6, headID = 2
manager = [2,2,-1,2,2,2]
informTime = [0,0,1,0,0,0]
```
#### Output:
```plaintext
1
```
**Explanation:**
- The head of the company with id 2 is the direct manager of all the employees in the company and needs 1 minute to inform them all.
- The tree structure: 2 -> {0, 1, 3, 4, 5}

### 🔹 Example 2:
#### Input:
```plaintext
n = 7, headID = 6
manager = [1,2,3,4,5,6,-1]
informTime = [0,6,5,4,3,2,1]
```
#### Output:
```plaintext
21
```
**Explanation:**
The graph is 6->5->4->3->2->1->0.
Time = 1 + 2 + 3 + 4 + 5 + 6 = 21.

## 🔍 Approaches

### 1. Depth-First Search (DFS)
The company structure is a **Tree** (or Directed Acyclic Graph) rooted at `headID`.
The time taken for a subordinate to receive news is the time taken for their manager to receive news **plus** the manager's `informTime`.
We want to find the **maximum** time required to reach any leaf node (closest to the bottom of the hierarchy).

#### Algorithm Steps:
1. **Build Adjacency List:** Convert the `manager` array into an adjacency list `adj`, where `adj[u]` contains all direct subordinates of `u`.
2. **DFS Traversal:**
   - Start DFS from `headID`.
   - For each subordinate `v` of `u`:
     - `maxTime = max(maxTime, DFS(v))`.
   - Return `informTime[u] + maxTime`.
   
   *Alternative:* Pass `currentTime` down the recursion.
   - `DFS(u, currentTime)`
   - `maxTime = max(maxTime, currentTime)`
   - Recursive call: `DFS(v, currentTime + informTime[u])`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. We build the graph and visit every node exactly once.
- **Space Complexity:** $O(N)$ for adjacency list and recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        vector<vector<int>> adj(n);
        for(int i = 0; i < n; ++i) {
            if(manager[i] != -1) {
                adj[manager[i]].push_back(i);
            }
        }
        
        return dfs(headID, adj, informTime);
    }

private:
    int dfs(int u, vector<vector<int>>& adj, vector<int>& informTime) {
        int maxSubTime = 0;
        for(int v : adj[u]) {
            maxSubTime = max(maxSubTime, dfs(v, adj, informTime));
        }
        return informTime[u] + maxSubTime;
    }
};
```

### Python
```python
from typing import List
from collections import defaultdict

class Solution:
    def numOfMinutes(self, n: int, headID: int, manager: List[int], informTime: List[int]) -> int:
        adj = defaultdict(list)
        for i, mgr in enumerate(manager):
            if mgr != -1:
                adj[mgr].append(i)
                
        def dfs(u):
            max_sub_time = 0
            for v in adj[u]:
                max_sub_time = max(max_sub_time, dfs(v))
            return informTime[u] + max_sub_time
            
        return dfs(headID)
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class Solution {
    public int numOfMinutes(int n, int headID, int[] manager, int[] informTime) {
        List<List<Integer>> adj = new ArrayList<>();
        for(int i = 0; i < n; i++) adj.add(new ArrayList<>());
        
        for(int i = 0; i < n; i++) {
            if(manager[i] != -1) {
                adj.get(manager[i]).add(i);
            }
        }
        
        return dfs(headID, adj, informTime);
    }
    
    private int dfs(int u, List<List<Integer>> adj, int[] informTime) {
        int maxSubTime = 0;
        for(int v : adj.get(u)) {
            maxSubTime = Math.max(maxSubTime, dfs(v, adj, informTime));
        }
        return informTime[u] + maxSubTime;
    }
}
```

## 🌍 Real-World Analogy
### **Phone Chain:**
The CEO calls VPs (takes 5 mins). VPs call Directors (takes 10 mins). Directors call Managers...
The total time until the *last* person knows is the longest path from CEO to any bottom-level employee, summing up the call durations.

## 🎯 Summary
✅ **Tree Traversal:** Problems involving hierarchies are typically tree problems.
✅ **Bottom-Up vs Top-Down:** Can interpret as finding max depth of weighted tree.
