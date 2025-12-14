# Topological Sort (Course Schedule)

## 🧩 Problem Statement
There are a total of `numCourses` courses you have to take, labeled from `0` to `numCourses - 1`. You are given an array `prerequisites` where `prerequisites[i] = [a, b]` indicates that you **must** take course `b` first if you want to take course `a`.

Return the ordering of courses you should take to finish all courses. If there are multiple valid answers, return **any** of them. If it is impossible to finish all courses (due to a cycle), return an **empty array**.

### 🔹 Example 1:
#### Input:
```plaintext
numCourses = 2, prerequisites = [[1,0]]
```
#### Output:
```plaintext
[0,1]
```
**Explanation:** There are a total of 2 courses. To take course 1 you should have finished course 0. So the correct course order is [0,1].

### 🔹 Example 2:
#### Input:
```plaintext
numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
```
#### Output:
```plaintext
[0,2,1,3]
```
**Explanation:** Total 4 courses. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0.
So one correct course order is [0,1,2,3]. Another correct ordering is [0,2,1,3].

## 🔍 Approaches

### 1. Kahn's Algorithm (BFS)
Topological Sort works on **Directed Acyclic Graphs (DAGs)**. Kahn's algorithm efficiently finds the sort or detects a cycle using **in-degrees**.

#### Algorithm Steps:
1. **Calculate In-Degrees:** For every edge `u -> v`, increment `inDegree[v]`.
2. **Initialize Queue:** Add all nodes with `inDegree == 0` to the queue.
3. **Process Queue:**
   - Pop node `u`. Add to result list.
   - For each neighbor `v` of `u`:
     - Decrement `inDegree[v]`.
     - If `inDegree[v] == 0`, push `v` to queue.
4. **Cycle Detection:** If the size of the result list is **less than** `numCourses`, there is a cycle (impossible topology). Return empty.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(V + E)$. We visit every node and every edge once.
- **Space Complexity:** $O(V + E)$ for adjacency list and in-degree array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> inDegree(numCourses, 0);
        
        for(auto& edge : prerequisites) {
            adj[edge[1]].push_back(edge[0]);
            inDegree[edge[0]]++;
        }
        
        queue<int> q;
        for(int i = 0; i < numCourses; ++i) {
            if(inDegree[i] == 0) q.push(i);
        }
        
        vector<int> order;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            
            for(int v : adj[u]) {
                inDegree[v]--;
                if(inDegree[v] == 0) q.push(v);
            }
        }
        
        if(order.size() == numCourses) return order;
        return {};
    }
};
```

### Python
```python
from typing import List
from collections import deque, defaultdict

class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        adj = defaultdict(list)
        in_degree = [0] * numCourses
        
        for dest, src in prerequisites:
            adj[src].append(dest)
            in_degree[dest] += 1
            
        q = deque([i for i in range(numCourses) if in_degree[i] == 0])
        order = []
        
        while q:
            u = q.popleft()
            order.append(u)
            
            for v in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    q.append(v)
                    
        return order if len(order) == numCourses else []
```

### Java
```java
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.List;

class Solution {
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        List<List<Integer>> adj = new ArrayList<>();
        for(int i = 0; i < numCourses; i++) adj.add(new ArrayList<>());
        
        int[] inDegree = new int[numCourses];
        
        for(int[] edge : prerequisites) {
            adj.get(edge[1]).add(edge[0]);
            inDegree[edge[0]]++;
        }
        
        Queue<Integer> q = new LinkedList<>();
        for(int i = 0; i < numCourses; i++) {
            if(inDegree[i] == 0) q.offer(i);
        }
        
        int[] order = new int[numCourses];
        int idx = 0;
        
        while(!q.isEmpty()) {
            int u = q.poll();
            order[idx++] = u;
            
            for(int v : adj.get(u)) {
                inDegree[v]--;
                if(inDegree[v] == 0) q.offer(v);
            }
        }
        
        return idx == numCourses ? order : new int[0];
    }
}
```

## 🌍 Real-World Analogy
### **Building Prerequisites:**
You cannot put the roof on a house before building the walls. You cannot build walls before the foundation.
Topological sort gives you the construction schedule: Foundation -> Walls -> Roof.

## 🎯 Summary
✅ **In-Degree:** Crucial for identifying independent (ready-to-process) nodes.
✅ **BFS Queue:** Ensures we process nodes level by level of dependency resolution.
