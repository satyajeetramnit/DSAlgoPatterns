# As Far From Land as Possible

## 🧩 Problem Statement
Given an `n x n` grid containing only `0`s (water) and `1`s (land), find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or no water exists in the grid, return `-1`.

The distance used in this problem is the **Manhattan distance**: the distance between `(x0, y0)` and `(x1, y1)` is `|x0 - x1| + |y0 - y1|`.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [[1,0,1],[0,0,0],[1,0,1]]
```
#### Output:
```plaintext
2
```
**Explanation:** The cell `(1, 1)` is as far as possible from all the land with distance 2.

### 🔹 Example 2:
#### Input:
```plaintext
grid = [[1,0,0],[0,0,0],[0,0,0]]
```
#### Output:
```plaintext
4
```
**Explanation:** The cell `(2, 2)` is as far as possible from land with distance 4.

## 🔍 Approaches

### 1. Multi-Source BFS (The Inverse Approach)
Instead of searching from every water cell to find nearest land (which is slow $O(W \cdot N^2)$), we search **from all land cells simultaneously** to find the farthest water.
- This is equivalent to finding the "maximum depth" of the BFS starting from land.

#### Algorithm Steps:
1. **Initialize Queue:** Add all land cells `(1)` to the `queue`.
2. **Check Edge Cases:** If queue is empty (all water) or full (all land), return `-1`.
3. **BFS:**
   - Loop while queue is not empty.
   - For each cell, check 4 neighbors.
   - If neighbor is `0` (unvisited water):
     - Change it to `1` (mark as visited).
     - Add to `queue`.
   - Track the distance (or "level").
4. **Result:** The max distance is `level - 1` (since we started with distance 0 for land).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^2)$. We visit each cell at most once.
- **Space Complexity:** $O(N^2)$ for the queue.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;
        
        // Add all land cells to queue
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if(grid[i][j] == 1) {
                    q.push({i, j});
                }
            }
        }
        
        // All water or all land
        if(q.empty() || q.size() == n*n) return -1;
        
        int dist = -1;
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        while(!q.empty()) {
            int size = q.size();
            dist++;
            
            while(size--) {
                auto [r, c] = q.front();
                q.pop();
                
                for(auto& d : dirs) {
                    int nr = r + d[0];
                    int nc = c + d[1];
                    
                    if(nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        grid[nr][nc] = 1; // Mark visited
                        q.push({nr, nc});
                    }
                }
            }
        }
        return dist;
    }
};
```

### Python
```python
from typing import List
from collections import deque

class Solution:
    def maxDistance(self, grid: List[List[int]]) -> int:
        n = len(grid)
        q = deque()
        
        # Add all land cells to queue
        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    q.append((i, j))
                    
        if not q or len(q) == n * n:
            return -1
            
        dist = -1
        dirs = [(-1,0), (1,0), (0,-1), (0,1)]
        
        while q:
            dist += 1
            for _ in range(len(q)):
                r, c = q.popleft()
                
                for dr, dc in dirs:
                    nr, nc = r + dr, c + dc
                    
                    if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                        grid[nr][nc] = 1 # Mark visited
                        q.append((nr, nc))
                        
        return dist
```

### Java
```java
import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int maxDistance(int[][] grid) {
        int n = grid.length;
        Queue<int[]> q = new LinkedList<>();
        
        // Add all land cells to queue
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    q.offer(new int[]{i, j});
                }
            }
        }
        
        if(q.isEmpty() || q.size() == n * n) return -1;
        
        int dist = -1;
        int[][] dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        while(!q.isEmpty()) {
            int size = q.size();
            dist++;
            
            while(size-- > 0) {
                int[] curr = q.poll();
                
                for(int[] d : dirs) {
                    int nr = curr[0] + d[0];
                    int nc = curr[1] + d[1];
                    
                    if(nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        grid[nr][nc] = 1; // Mark visited
                        q.offer(new int[]{nr, nc});
                    }
                }
            }
        }
        return dist;
    }
}
```

## 🌍 Real-World Analogy
### **Shockwave Propagation:**
Imagine an earthquake hitting all land masses simultaneously. The shockwaves travel outwards to the water. The water cell reached *last* by the shockwaves is the farthest from any land.

## 🎯 Summary
✅ **Reverse Thinking:** Don't search from water to land (many start points, hard to terminate). Search from land to water (infection style).
✅ **Level-order Traversal:** The last level reached is the max distance.
