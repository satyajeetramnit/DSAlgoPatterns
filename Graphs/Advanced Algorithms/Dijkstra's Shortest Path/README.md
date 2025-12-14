# Dijkstra's Shortest Path Algorithm

## 🧩 Problem Statement
Given a weighted, directed graph with `V` vertices and `E` edges, and a source vertex `S`, find the shortest path from `S` to all other vertices.

Vertices are labeled from `0` to `V-1`. The graph is given as an adjacency list where `adj[u]` contains pairs `(v, w)`, representing an edge from `u` to `v` with weight `w`.

Return a list `dist` where `dist[i]` is the shortest distance from `S` to node `i`. If a node is unreachable, the distance should be conceptually infinity (or typically `-1` or `Integer.MAX_VALUE` depending on output format).

### 🔹 Example 1:
#### Input:
```plaintext
V = 3, E = 3, S = 2
edges = [[2,1,1], [2,0,6], [1,0,3]] (u, v, w)
```
#### Output:
```plaintext
[4, 1, 0]
```
**Explanation:**
- 2 -> 0: weight 6
- 2 -> 1: weight 1
- 1 -> 0: weight 3
- Path 2->1->0 has weight 1+3 = 4, which is less than 6. Dist to 2 is 0.

### 🔹 Example 2:
#### Input:
```plaintext
V = 2, E = 1, S = 1
edges = [[1,0,9]]
```
#### Output:
```plaintext
[9, 0]
```

## 🔍 Approaches

### 1. Dijkstra's Algorithm (Priority Queue)
Dijkstra's is a greedy algorithm. We permit exploring the "cheapest" node available at any step.
1. **Initialize:** `dist` array with infinity, `dist[S] = 0`.
2. **Priority Queue:** Use a Min-Heap `pq` storing pairs `(distance, node)`. Initially add `(0, S)`.
3. **Process:**
   - While `pq` is not empty, extract min `(d, u)`.
   - If `d > dist[u]`, skip (outdated processing).
   - For every neighbor `v` of `u` with weight `w`:
     - if `dist[u] + w < dist[v]`:
       - `dist[v] = dist[u] + w`
       - `pq.push(dist[v], v)`

Note: Dijkstra works only with **non-negative** edge weights.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(E \log V)$. Each edge might update the priority queue.
- **Space Complexity:** $O(V + E)$ for adjacency list and distance array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        vector<int> dist(V, INT_MAX);
        
        dist[S] = 0;
        pq.push({0, S});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto& edge : adj[u]) {
                int v = edge[0];
                int w = edge[1];
                
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};
```

### Python
```python
import heapq
from typing import List, Tuple

class Solution:
    def dijkstra(self, V: int, adj: List[List[Tuple[int, int]]], S: int) -> List[int]:
        pq = [(0, S)]
        dist = [float('inf')] * V
        dist[S] = 0
        
        while pq:
            d, u = heapq.heappop(pq)
            
            if d > dist[u]:
                continue
            
            for v, w in adj[u]:
                if dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w
                    heapq.heappush(pq, (dist[v], v))
                    
        return [d if d != float('inf') else -1 for d in dist]
```

### Java
```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;

class Solution {
    static class Node implements Comparable<Node> {
        int v, weight;
        Node(int v, int weight) { this.v = v; this.weight = weight; }
        public int compareTo(Node that) { return this.weight - that.weight; }
    }
    
    public int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S) {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        
        dist[S] = 0;
        pq.add(new Node(S, 0));
        
        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int u = node.v;
            int d = node.weight;
            
            if (d > dist[u]) continue;
            
            for (ArrayList<Integer> edge : adj.get(u)) {
                int v = edge.get(0);
                int w = edge.get(1);
                
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.add(new Node(v, dist[v]));
                }
            }
        }
        return dist;
    }
}
```

## 🌍 Real-World Analogy
### **GPS Navigation:**
Driving from City A to City B. You always choose the road that offers the shortest accumulated time from the start, updating your estimates as you reach new intersections.

## 🎯 Summary
✅ **Min-Heap:** Essential for efficiently getting the next closest node.
✅ **Relaxation:** The process of trying to lower `dist[v]` using `dist[u] + w`.
