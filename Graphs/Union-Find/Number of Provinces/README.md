# Number of Provinces

## 🧩 Problem Statement
There are `n` cities. Some of them are connected, while some are not. If city `a` is connected directly with city `b`, and city `b` is connected directly with city `c`, then city `a` is connected indirectly with city `c`.

A **province** is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an `n x n` matrix `isConnected` where `isConnected[i][j] = 1` if the `i-th` city and the `j-th` city are directly connected, and `isConnected[i][j] = 0` otherwise.

Return the total number of **provinces**.

### 🔹 Example 1:
#### Input:
```plaintext
isConnected = [[1,1,0],[1,1,0],[0,0,1]]
```
#### Output:
```plaintext
2
```
**Explanation:** City 0 and 1 are connected, so they form a province. City 2 is separate.

### 🔹 Example 2:
#### Input:
```plaintext
isConnected = [[1,0,0],[0,1,0],[0,0,1]]
```
#### Output:
```plaintext
3
```
**Explanation:** Each city is in its own province.

## 🔍 Approaches

### 1. Union-Find (Disjoint Set Union)
We can treat each city as a node in a graph.
- Initialize DSU with `n` components.
- Iterate through the matrix. If `isConnected[i][j] == 1` and `i != j`, call `union(i, j)`.
- If `union` is successful (they were in different sets), decrement the component count.
- The final count is the number of provinces.

### 2. DFS / BFS
Iterate through each city `0` to `n-1`.
- If city `i` is not visited:
  - Increment `provinces`.
  - Start DFS/BFS from `i` to visit all connected cities.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^2)$ to traverse the adjacency matrix. Union-Find operations are nearly constant.
- **Space Complexity:** $O(N)$ for DSU parent array or visited array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    int count; // Number of connected components
    
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        count = n;
    }
    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            parent[rootX] = rootY;
            count--;
        }
    }
};

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        DSU dsu(n);
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j] == 1) {
                    dsu.unite(i, j);
                }
            }
        }
        return dsu.count;
    }
};
```

### Python
```python
from typing import List

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.count = n
        
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
        
    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            self.parent[rootX] = rootY
            self.count -= 1

class Solution:
    def findCircleNum(self, isConnected: List[List[int]]) -> int:
        n = len(isConnected)
        dsu = DSU(n)
        
        for i in range(n):
            for j in range(i + 1, n):
                if isConnected[i][j] == 1:
                    dsu.union(i, j)
                    
        return dsu.count
```

### Java
```java
class Solution {
    static class DSU {
        int[] parent;
        int count;
        
        DSU(int n) {
            parent = new int[n];
            for(int i=0; i<n; i++) parent[i] = i;
            count = n;
        }
        int find(int x) {
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
                count--;
            }
        }
    }

    public int findCircleNum(int[][] isConnected) {
        int n = isConnected.length;
        DSU dsu = new DSU(n);
        
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(isConnected[i][j] == 1) {
                    dsu.union(i, j);
                }
            }
        }
        return dsu.count;
    }
}
```

## 🌍 Real-World Analogy
### **Friendship Circles:**
If Person A is friends with Person B, and B is friends with C, then A, B, and C are in the same friendship circle (province). We want to count how many distinct circles exist.

## 🎯 Summary
✅ **Component Counting:** Union-Find is highly efficient. Start with `N` components and reduce count on every merge.
