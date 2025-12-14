# Critical Connections in a Network (Tarjan's Bridge Finding)

## 🧩 Problem Statement
There are `n` servers numbered from `0` to `n - 1` connected by undirected server-to-server `connections` forming a network where `connections[i] = [ai, bi]` represents a connection between servers `ai` and `bi`. Any server can reach other servers directly or indirectly through the network.

A **critical connection** is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

### 🔹 Example 1:
#### Input:
```plaintext
n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
```
#### Output:
```plaintext
[[1,3]]
```
#### Explanation:
- The graph has a cycle `0-1-2-0`. Removing any edge in the cycle (`0-1`, `1-2`, `2-0`) keeps the graph connected.
- The edge `1-3` is a "bridge". Removing it disconnects node `3` from the rest.

### 🔹 Example 2:
#### Input:
```plaintext
n = 2, connections = [[0,1]]
```
#### Output:
```plaintext
[[0,1]]
```

## 🔍 Approaches

### 1. Tarjan's Bridge-Finding Algorithm (DFS)
We need to find edges that are NOT part of any cycle.
- **Concept:** Use DFS to traverse the graph. Keep track of two values for each node `u`:
  1. `disc[u]`: Discovery time (when we first visited `u`).
  2. `low[u]`: Lowest discovery time reachable from `u` (including itself) in the DFS tree, possibly using a **back-edge** (an edge to an ancestor).
- **Bridge Condition:** An edge `u -> v` is a bridge if `low[v] > disc[u]`.
  - This means there is NO back-edge from `v` or any of its descendants to `u` or any of its ancestors. The only way to reach `v` from `u` is through the edge `u-v`.

### 🏛️ Visual Logic: Tracing `[[0,1],[1,2],[2,0],[1,3]]`

#### Step 1: Start DFS at 0
- **Time**: 0.
- **Node 0**: `disc[0]=0`, `low[0]=0`.
- **Neighbors**: 1, 2. Visit 1.

<!-- slide -->

#### Step 2: Visit 1 (Child of 0)
- **Time**: 1.
- **Node 1**: `disc[1]=1`, `low[1]=1`.
- **Neighbors**: 0 (parent), 2, 3.
- **Visit 2**: (Child of 1).

<!-- slide -->

#### Step 3: Visit 2 (Child of 1)
- **Time**: 2.
- **Node 2**: `disc[2]=2`, `low[2]=2`.
- **Neighbors**: 1 (parent), 0.
- **Visit 0**: 0 is Visited and NOT parent (Back-edge!).
- **Update**: `low[2] = min(low[2], disc[0]) = 0`.
- **Return to 1**:
  - `low[1] = min(low[1], low[2]) = 0`.
  - Check Bridge `1->2`: `low[2](0) > disc[1](1)`? **FALSE**. (Part of cycle 0-1-2).

<!-- slide -->

#### Step 4: Visit 3 (Child of 1)
- **Time**: 3.
- **Node 3**: `disc[3]=3`, `low[3]=3`.
- **Neighbors**: 1 (parent). No other neighbors.
- **Return to 1**:
  - Check Bridge `1->3`: `low[3](3) > disc[1](1)`? **TRUE**.
  - **Result**: Add `[1, 3]`.

<!-- slide -->

#### Step 5: Final State
- **Result**: `[[1, 3]]`.
- **Logic**: The back-edge `2->0` allowed the cycle nodes to have `low` value 0. Node 3 had no back-edge, so its `low` remained 3.


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(V + E)$ (Standard DFS).
- **Space Complexity:** $O(V + E)$ for graph adjacency list and recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
    vector<vector<int>> adj;
    vector<int> disc;
    vector<int> low;
    int time;
    vector<vector<int>> bridges;

    void dfs(int u, int p = -1) {
        disc[u] = low[u] = time++;
        
        for (int v : adj[u]) {
            if (v == p) continue; // Skip parent
            
            if (disc[v] != -1) {
                // Back-edge
                low[u] = min(low[u], disc[v]);
            } else {
                // Tree-edge
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            }
        }
    }

public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        adj.assign(n, vector<int>());
        for (auto& edge : connections) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        
        disc.assign(n, -1);
        low.assign(n, -1);
        time = 0;
        bridges.clear();
        
        dfs(0);
        return bridges;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def criticalConnections(self, n: int, connections: List[List[int]]) -> List[List[int]]:
        adj = [[] for _ in range(n)]
        for u, v in connections:
            adj[u].append(v)
            adj[v].append(u)
            
        disc = [-1] * n
        low = [-1] * n
        time = 0
        bridges = []
        
        def dfs(u, p):
            nonlocal time
            disc[u] = low[u] = time
            time += 1
            
            for v in adj[u]:
                if v == p:
                    continue
                
                if disc[v] != -1:
                    low[u] = min(low[u], disc[v])
                else:
                    dfs(v, u)
                    low[u] = min(low[u], low[v])
                    if low[v] > disc[u]:
                        bridges.append([u, v])
                        
        dfs(0, -1)
        return bridges
```

### Java
```java
import java.util.*;

class Solution {
    private List<List<Integer>> adj;
    private int[] disc;
    private int[] low;
    private int time;
    private List<List<Integer>> bridges;

    public List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (List<Integer> edge : connections) {
            adj.get(edge.get(0)).add(edge.get(1));
            adj.get(edge.get(1)).add(edge.get(0));
        }
        
        disc = new int[n];
        Arrays.fill(disc, -1);
        low = new int[n];
        time = 0;
        bridges = new ArrayList<>();
        
        dfs(0, -1);
        return bridges;
    }
    
    private void dfs(int u, int p) {
        disc[u] = low[u] = time++;
        
        for (int v : adj.get(u)) {
            if (v == p) continue;
            
            if (disc[v] != -1) {
                low[u] = Math.min(low[u], disc[v]);
            } else {
                dfs(v, u);
                low[u] = Math.min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    bridges.add(Arrays.asList(u, v));
                }
            }
        }
    }
}
```

## 🌍 Real-World Analogy
### **Network Reliability / Single Point of Failure:**
Think of the nodes as **Data Centers** and connections as **Fiber Optic Cables**.
- A "Critical Connection" is a cable which, if cut by a shark or backhoe, would SPLIT the internet into two disconnected islands.
- Engineers need to identify these bridges to add **redundancy** (build a second cable/cycle) so that the network remains robust against single link failures.
