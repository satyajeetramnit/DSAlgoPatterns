# Kruskal's Algorithm (Minimum Spanning Tree)

## 🧩 Problem Statement
Given a weighted, undirected graph with `V` vertices and `E` edges. You want to find a **Minimum Spanning Tree (MST)** of the graph.
An MST is a subset of the edges that connects all vertices in the graph together, without any cycles and with the minimum possible total edge weight.

Return the **sum of weights** of the edges in the MST.

Vertices are labeled from `0` to `V-1`. Edges are given as a list `edges` where `edges[i] = [u, v, w]`.

### 🔹 Example 1:
#### Input:
```plaintext
V = 3, edges = [[0,1,5], [1,2,3], [0,2,1]]
```
#### Output:
```plaintext
4
```
**Explanation:**
- Edges: (0,1,5), (1,2,3), (0,2,1).
- Sort edges by weight: (0,2,1), (1,2,3), (0,1,5).
- Pick (0,2,1) -> Connects 0-2. Cost 1.
- Pick (1,2,3) -> Connects 1-2. Cost 1+3=4. All connected.
- Skip (0,1,5) as 0 and 1 are already connected via 2.
- Total cost: 4.

### 🔹 Example 2:
#### Input:
```plaintext
V = 2, edges = [[0,1,5]]
```
#### Output:
```plaintext
5
```

## 🔍 Approaches

### 1. Kruskal's Algorithm (Greedy + Union-Find)
Kruskal's builds the MST by adding edges in increasing order of weight, provided the edge doesn't form a cycle.
**Union-Find (Disjoint Set Union - DSU)** is the perfect data structure to check for cycles and connectivity.

#### Algorithm Steps:
1. **Sort Edges:** Sort all edges by weight in ascending order.
2. **Initialize DSU:** Create a Union-Find structure with `V` elements.
3. **Iterate Edges:**
   - For each edge `(u, v, w)`:
   - Check if `find(u) != find(v)`.
   - If true (they are in different components):
     - `union(u, v)`.
     - Add `w` to `mstWeight`.
     - Increment `edgesCount`.
4. **Complete:** If `edgesCount == V - 1`, we have a spanning tree.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(E \log E)$ or $O(E \log V)$ for sorting. Union-Find operations take almost constant time $O(\alpha(V))$.
- **Space Complexity:** $O(V)$ for DSU parent/rank arrays.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n);
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
    int minSpanningTree(int V, vector<vector<int>>& edges) {
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        DSU dsu(V);
        int mstWeight = 0;
        int edgesCount = 0;
        
        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            if (dsu.unite(u, v)) {
                mstWeight += w;
                edgesCount++;
            }
        }
        return mstWeight;
    }
};
```

### Python
```python
from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
    
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
    def minSpanningTree(self, V: int, edges: List[List[int]]) -> int:
        # edges: [u, v, w]
        edges.sort(key=lambda x: x[2])
        
        dsu = DSU(V)
        mst_weight = 0
        
        for u, v, w in edges:
            if dsu.union(u, v):
                mst_weight += w
                
        return mst_weight
```

### Java
```java
import java.util.Arrays;
import java.util.Comparator;

class Solution {
    static class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n];
            for(int i=0; i<n; i++) parent[i] = i;
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

    public int minSpanningTree(int V, int[][] edges) {
        Arrays.sort(edges, (a, b) -> Integer.compare(a[2], b[2]));
        
        DSU dsu = new DSU(V);
        int mstWeight = 0;
        
        for(int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            if(dsu.union(u, v)) {
                mstWeight += w;
            }
        }
        return mstWeight;
    }
}
```

## 🌍 Real-World Analogy
### **Network Cabling:**
You want to connect PC 1, PC 2, PC 3, etc. with ethernet cables.
Each cable costs a different amount depending on length.
You want to connect everyone with the *cheapest total cable cost*. Kruskal's does exactly this: always picking the cheapest cable available that connects two previously unconnected components.

## 🎯 Summary
✅ **MST:** Connects all vertices with min weight, no cycles.
✅ **Kruskal's:** Edge-centric greedy algorithm.
✅ **Use Case:** Network design, clustering.
