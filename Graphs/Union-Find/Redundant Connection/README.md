# Redundant Connection

## 🧩 Problem Statement
In this problem, a tree is an **undirected graph** that is connected and has no cycles.

You are given a graph that started as a tree with `n` nodes labeled from `1` to `n`, with one additional edge added. The added edge has two different vertices chosen from `1` to `n`, and was not an edge that already existed. The graph is represented as an array `edges` of length `n` where `edges[i] = [ai, bi]` indicates that there is an edge between nodes `ai` and `bi` in the graph.

Return an edge that can be removed so that the resulting graph is a tree of `n` nodes. If there are multiple answers, return the answer that occurs last in the input.

### 🔹 Example 1:
#### Input:
```plaintext
edges = [[1,2], [1,3], [2,3]]
```
#### Output:
```plaintext
[2,3]
```
**Explanation:** 
- Connectivity: 1-2, 1-3.
- When [2,3] is added, 2 and 3 are already connected via 1. So [2,3] forms a cycle.

### 🔹 Example 2:
#### Input:
```plaintext
edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
```
#### Output:
```plaintext
[1,4]
```

## 🔍 Approaches

### 1. Union-Find (Disjoint Set Union)
Since we want to find the **first edge** that creates a cycle (which corresponds to the redundant edge), we can iterate through the edges and apply Union-Find.
- Initially, each node is in its own set.
- For each edge `(u, v)`:
  - Check if `find(u) == find(v)`.
  - If **True**: `u` and `v` are already connected. Adding this edge forms a cycle. This is the redundant edge.
  - If **False**: `union(u, v)`.

Since we are asked to return the *last* edge in the input that satisfies the condition, and we process edges in order, the *first* edge we encounter that creates a cycle is essentially the candidate. Wait, the problem says "return the answer that occurs last in the input". If we process from start to end, the first time `find(u) == find(v)`, typically that IS the edge that *completes* the cycle. In a graph with N nodes and N edges (1 extra edge), there is exactly one cycle. The edge that completes it allows us to detect it.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot \alpha(N))$, which is effectively $O(N)$.
- **Space Complexity:** $O(N)$ for DSU structure.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            return true;
        }
        return false;
    }
};

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        DSU dsu(n);
        
        for (auto& edge : edges) {
            if (!dsu.unite(edge[0], edge[1])) {
                return edge;
            }
        }
        return {};
    }
};
```

### Python
```python
from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n + 1))
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            self.parent[rootX] = rootY
            return True
        return False

class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        dsu = DSU(n)
        
        for u, v in edges:
            if not dsu.union(u, v):
                return [u, v]
                
        return []
```

### Java
```java
class Solution {
    static class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n + 1];
            for(int i=0; i<=n; i++) parent[i] = i;
        }
        int find(int x) {
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        boolean union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
                return true;
            }
            return false;
        }
    }

    public int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        DSU dsu = new DSU(n);
        
        for(int[] edge : edges) {
            if(!dsu.union(edge[0], edge[1])) {
                return edge;
            }
        }
        return new int[0];
    }
}
```

## 🌍 Real-World Analogy
### **Circuit Breaker:**
You are wiring a circuit. You connect components A-B, B-C. If you then try to connect C-A, you form a loop (short circuit risk). The last wire that completes the loop is the "redundant" one to be removed.

## 🎯 Summary
✅ **Cycle Detection:** Union-Find is the standard way to detect cycles in undirected graphs dynamically.
