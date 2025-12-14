# Shortest Path in Binary Matrix

## 🧩 Problem Statement
Given an `n x n` binary matrix `grid`, return the length of the shortest clear path in the matrix. If there is no clear path, return `-1`.

A **clear path** in a binary matrix is a path from the **top-left** cell (i.e., `(0, 0)`) to the **bottom-right** cell (i.e., `(n - 1, n - 1)`) such that:
1. All the visited cells of the path are `0`.
2. All the adjacent cells of the path are **8-directionally** connected (i.e., they are different and they share an edge or a corner).

The **length of a clear path** is the number of visited cells of this path.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [[0,1],[1,0]]
```
#### Output:
```plaintext
2
```

### 🔹 Example 2:
#### Input:
```plaintext
grid = [[0,0,0],[1,1,0],[1,1,0]]
```
#### Output:
```plaintext
4
```

### 🔹 Example 3:
#### Input:
```plaintext
grid = [[1,0,0],[1,1,0],[1,1,0]]
```
#### Output:
```plaintext
-1
```

## 🔍 Approaches

### 1. Breadth-First Search (BFS)
Since we need the **shortest path** in an unweighted grid, BFS is the standard choice. BFS explores layer by layer, guaranteeing that the first time we reach the target, it is via the shortest path.

#### Algorithm Steps:
1. **Check Base Case:** If `grid[0][0] == 1` or `grid[n-1][n-1] == 1`, return `-1`.
2. **Initialize:** Queue `q` with `(0, 0)`. Mark `(0, 0)` as visited (set to `1` in grid to save space, or use logical visited set).
3. **Level-Order Traversal:**
   - Track `pathLength`. Start at `1`.
   - Loop while `q` is not empty.
   - Process all nodes currently in the queue (current level).
   - For each node `(r, c)`:
     - If `(r, c) == (n-1, n-1)`, return `pathLength`.
     - Check all 8 neighbors. If neighbor is valid (in bounds) and is `0` (unvisited and clear):
       - Add to `q`.
       - Mark as visited (typically set `grid[nr][nc] = 1`).
   - Increment `pathLength`.
4. If queue empties and target not reached, return `-1`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^2)$, where N is the grid dimension. We visit each cell at most once.
- **Space Complexity:** $O(N^2)$ for the queue in worst case (e.g., all 0s).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
        
        queue<pair<int, int>> q;
        q.push({0, 0});
        grid[0][0] = 1; // Mark visited
        
        int directions[8][2] = {{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
        int pathLen = 1;
        
        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                auto [r, c] = q.front();
                q.pop();
                
                if (r == n - 1 && c == n - 1) return pathLen;
                
                for (auto& dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        q.push({nr, nc});
                        grid[nr][nc] = 1; // Mark visited
                    }
                }
            }
            pathLen++;
        }
        return -1;
    }
};
```

### Python
```python
from typing import List
from collections import deque

class Solution:
    def shortestPathBinaryMatrix(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1 or grid[n-1][n-1] == 1:
            return -1
            
        q = deque([(0, 0)])
        grid[0][0] = 1 # Mark visited
        path_len = 1
        
        directions = [
            (-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1),  (1, 0),  (1, 1)
        ]
        
        while q:
            for _ in range(len(q)):
                r, c = q.popleft()
                if r == n - 1 and c == n - 1:
                    return path_len
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < n and 0 <= nc < n and grid[nr][nc] == 0:
                        q.append((nr, nc))
                        grid[nr][nc] = 1 # Mark visited
            path_len += 1
            
        return -1
```

### Java
```java
import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int shortestPathBinaryMatrix(int[][] grid) {
        int n = grid.length;
        if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
        
        Queue<int[]> q = new LinkedList<>();
        q.offer(new int[]{0, 0});
        grid[0][0] = 1; // Mark visited
        
        int[][] directions = {
            {-1,-1}, {-1,0}, {-1,1},
            {0,-1},          {0,1},
            {1,-1},  {1,0},  {1,1}
        };
        
        int pathLen = 1;
        
        while (!q.isEmpty()) {
            int size = q.size();
            while (size-- > 0) {
                int[] curr = q.poll();
                int r = curr[0];
                int c = curr[1];
                
                if (r == n - 1 && c == n - 1) return pathLen;
                
                for (int[] dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        q.offer(new int[]{nr, nc});
                        grid[nr][nc] = 1; // Mark visited
                    }
                }
            }
            pathLen++;
        }
        return -1;
    }
}
```

## 🌍 Real-World Analogy
### **King in Chess:**
The movement is exactly like a King in Chess (can move to all 8 adjacent squares). You want to move your King from the top-left corner to the bottom-right corner of the board, avoiding obstacles (pieces or holes). BFS finds the minimum number of moves.

## 🎯 Summary
✅ **BFS:** Guarantees shortest path in unweighted graphs.
✅ **8-Directional:** Neighbor checking logic must account for diagonals.
