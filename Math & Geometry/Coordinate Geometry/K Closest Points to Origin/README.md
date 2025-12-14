# K Closest Points to Origin

## 🧩 Problem Statement
Given an array of points where `points[i] = [xi, yi]` represents a point on the X-Y plane and an integer `k`, return the `k` closest points to the origin `(0, 0)`.

The distance between two points on the X-Y plane is the Euclidean distance (i.e., $\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}$).

You may return the answer in any order. The answer is guaranteed to be unique (except for the order of it).

### 🔹 Example 1:
#### Input:
```plaintext
points = [[1,3],[-2,2]], k = 1
```
#### Output:
```plaintext
[[-2,2]]
```
**Explanation:** 
- Dist(1,3) = $\sqrt{1^2 + 3^2} = \sqrt{10}$.
- Dist(-2,2) = $\sqrt{(-2)^2 + 2^2} = \sqrt{8}$.
- $\sqrt{8} < \sqrt{10}$, so `[-2,2]` is closer.

### 🔹 Example 2:
#### Input:
```plaintext
points = [[3,3],[5,-1],[-2,4]], k = 2
```
#### Output:
```plaintext
[[3,3],[-2,4]]
```

## 🔍 Approaches

### 1. Max-Heap ($O(N \log K)$)
- **Concept:** Maintain a max-heap of size `k`.
- **Algorithm:**
  - Iterate through points.
  - Calculate squared distance ($x^2 + y^2$).
  - Push to heap (store distance and index/point).
  - If heap size > `k`, pop the max (farthest point).
- **Result:** The heap contains the `k` smallest distances.

### 2. QuickSelect ($O(N)$ average)
- **Concept:** Select the $k$-th smallest element by distance.
- **Algorithm:** Partition the array such that elements left of pivot are smaller, right are larger. If pivot index == `k`, we are done.

### 3. Sorting ($O(N \log N)$)
- **Concept:** Sort all points by distance and take the first `k`.

We implement **Max-Heap** as it's efficient for large $N$ and small $K$.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log K)$.
- **Space Complexity:** $O(K)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Max heap: pair <distance_squared, index>
        priority_queue<pair<long, int>> maxHeap;
        
        for (int i = 0; i < points.size(); ++i) {
             long dist = (long)points[i][0] * points[i][0] + (long)points[i][1] * points[i][1];
             maxHeap.push({dist, i});
             if (maxHeap.size() > k) {
                 maxHeap.pop();
             }
        }
        
        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            result.push_back(points[maxHeap.top().second]);
            maxHeap.pop();
        }
        
        return result;
    }
};
```

### Python
```python
import heapq
from typing import List

class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        # Max heap using negative distance (since Python has min-heap)
        heap = []
        for x, y in points:
            dist = -(x*x + y*y)
            heapq.heappush(heap, (dist, x, y))
            if len(heap) > k:
                heapq.heappop(heap)
        
        return [[x, y] for (dist, x, y) in heap]
```

### Java
```java
import java.util.PriorityQueue;

class Solution {
    public int[][] kClosest(int[][] points, int k) {
        // Max heap based on distance
        PriorityQueue<int[]> maxHeap = new PriorityQueue<>((a, b) -> 
            Integer.compare(b[0]*b[0] + b[1]*b[1], a[0]*a[0] + a[1]*a[1])
        );
        
        for (int[] p : points) {
            maxHeap.offer(p);
            if (maxHeap.size() > k) {
                maxHeap.poll();
            }
        }
        
        int[][] res = new int[k][2];
        for (int i = 0; i < k; i++) {
            res[i] = maxHeap.poll();
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Emergency Response:**
An ambulance dispatch center wants to find the `k` closest ambulances to an accident scene. They calculate distances for all available units and pick the top `k`.

## 🎯 Summary
✅ **Heap:** Excellent for finding top-k elements in a stream or large dataset.
✅ **Squared Distance:** Avoid square roots ($O(1)$ expensive op) since $d_1 < d_2 \iff d_1^2 < d_2^2$.
