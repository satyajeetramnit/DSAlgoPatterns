# Number of Closed Islands

## 🧩 Problem Statement
Given a 2D grid consists of `0`s (land) and `1`s (water).  An island is a maximal 4-directionally connected group of `0`s and a **closed island** is an island **totally** (all left, top, right, bottom) surrounded by `1`s.

Return the number of *closed islands*.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [
  [1,1,1,1,1,1,1,0],
  [1,0,0,0,0,1,1,0],
  [1,0,1,0,1,1,1,0],
  [1,0,0,0,0,1,0,1],
  [1,1,1,1,1,1,1,0]
]
```
#### Output:
```plaintext
2
```
**Explanation:**
- The island in the middle is closed (surrounded by 1s).
- The island at the bottom right is NOT closed because it touches the edge (assumed to be infinite land, but here edge is boundary).
- The island at top right is NOT closed because it touches the edge.

### 🔹 Example 2:
#### Input:
```plaintext
grid = [
  [0,0,1,0,0],
  [0,1,0,1,0],
  [0,1,1,1,0]
]
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Flood Fill (DFS/BFS) with Boundary Check
A closed island is one that does **not** touch the boundary of the grid.
1. **Filter Non-Closed Islands:**
   - Iterate through the **boundary** cells (first row, last row, first col, last col).
   - If a boundary cell is `0` (land), it means any island connected to it is **not closed**.
   - Perform DFS/BFS from this cell to mark the entire connected component as visited (change `0` to `1` or visited).
2. **Count Closed Islands:**
   - Now, iterate through the inner grid.
   - Any remaining `0`s must be part of a closed island (since all open ones were flooded).
   - Increment count and perform DFS/BFS to mark the island.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$. Visit each cell constant times.
- **Space Complexity:** $O(M \cdot N)$ for recursion/queue.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        
        // 1. Flood fill from boundaries to remove open islands
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 0) {
                    dfs(grid, i, j, m, n);
                }
            }
        }
        
        // 2. Count remaining closed islands
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 0) {
                    count++;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<int>>& grid, int r, int c, int m, int n) {
        if(r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 1) return;
        
        grid[r][c] = 1; // Mark as visited (water)
        
        dfs(grid, r + 1, c, m, n);
        dfs(grid, r - 1, c, m, n);
        dfs(grid, r, c + 1, m, n);
        dfs(grid, r, c - 1, m, n);
    }
};
```

### Python
```python
from typing import List

class Solution:
    def closedIsland(self, grid: List[List[int]]) -> int:
        if not grid:
            return 0
        
        rows, cols = len(grid), len(grid[0])
        
        def dfs(r, c):
            if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] == 1:
                return
            grid[r][c] = 1 # Mark as visited
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)
            
        # 1. Flood fill boundaries
        for r in range(rows):
            for c in range(cols):
                if (r == 0 or r == rows - 1 or c == 0 or c == cols - 1) and grid[r][c] == 0:
                    dfs(r, c)
                    
        # 2. Count remaining
        count = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 0:
                    count += 1
                    dfs(r, c)
        return count
```

### Java
```java
class Solution {
    public int closedIsland(int[][] grid) {
        if(grid == null || grid.length == 0) return 0;
        int m = grid.length;
        int n = grid[0].length;
        
        // 1. Flood fill boundaries
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 0) {
                    dfs(grid, i, j, m, n);
                }
            }
        }
        
        // 2. Count remaining
        int count = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    count++;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return count;
    }
    
    private void dfs(int[][] grid, int r, int c, int m, int n) {
        if(r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == 1) return;
        
        grid[r][c] = 1; // Mark as visited
        
        dfs(grid, r + 1, c, m, n);
        dfs(grid, r - 1, c, m, n);
        dfs(grid, r, c + 1, m, n);
        dfs(grid, r, c - 1, m, n);
    }
}
```

## 🌍 Real-World Analogy
### **Lakes vs Oceans:**
- **Open Islands:** Land connected to the "edge of the world" (boundary). Water can flow out.
- **Closed Islands:** Landlocked lakes. Completely surrounded by water, no connection to the boundary.

## 🎯 Summary
✅ **Preprocessing:** Clearing boundary-connected components simplifies the problem to standard "Number of Islands".
