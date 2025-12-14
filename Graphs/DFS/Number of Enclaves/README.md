# Number of Enclaves

## 🧩 Problem Statement
You are given an `m x n` binary matrix `grid`, where `0` represents a sea cell and `1` represents a land cell. A **move** consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.

Return the number of land cells in `grid` for which we cannot walk off the boundary of the grid in any number of moves.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [
  [0,0,0,0],
  [1,0,1,0],
  [0,1,1,0],
  [0,0,0,0]
]
```
#### Output:
```plaintext
3
```
**Explanation:** 
- There are three 1s that are enclosed by 0s. 
- The 1 at (1,0) is on the boundary, so we can walk off.

### 🔹 Example 2:
#### Input:
```plaintext
grid = [
  [0,1,1,0],
  [0,0,1,0],
  [0,0,1,0],
  [0,0,0,0]
]
```
#### Output:
```plaintext
0
```
**Explanation:** All 1s are either on the boundary or connected to the boundary.

## 🔍 Approaches

### 1. Flood Fill from Boundary
This is very similar to "Number of Closed Islands" and "Surrounded Regions".
1. **Identify "Safe" Lands:**
   - Iterate through the **boundary** cells of the grid.
   - If a boundary cell is `1` (land), start a DFS/BFS to mark all connected land cells as "unsafe" (can walk off). Mark them as visited (e.g., change `1` to `0` or `2`).
2. **Count Enclaves:**
   - Iterate through the entire grid.
   - Any remaining `1`s are **enclaves** (cannot walk off).
   - Count them (no need to run DFS again, just sum them up).

#### Algorithm Steps:
1. Loop over boundary rows/cols.
2. If `grid[i][j] == 1`, call `DFS(i, j)`.
   - `DFS` changes `1` to `0` (sinking the island).
3. Loop over all cells.
4. If `grid[i][j] == 1`, increment `count`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$. We visit each cell constant times.
- **Space Complexity:** $O(M \cdot N)$ for recursion/queue.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // 1. Sink all land connected to the boundary
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 1) {
                    dfs(grid, i, j, m, n);
                }
            }
        }
        
        // 2. Count remaining land
        int count = 0;
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 1) {
                    count++;
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<int>>& grid, int r, int c, int m, int n) {
        if(r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) return;
        
        grid[r][c] = 0; // Sink the land
        
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
    def numEnclaves(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        
        def dfs(r, c):
            if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] == 0:
                return
            
            grid[r][c] = 0 # Sink
            
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)
            
        # 1. Sink boundary-connected land
        for r in range(rows):
            for c in range(cols):
                if (r == 0 or c == 0 or r == rows - 1 or c == cols - 1) and grid[r][c] == 1:
                    dfs(r, c)
                    
        # 2. Count remaining
        count = 0
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 1:
                    count += 1
        return count
```

### Java
```java
class Solution {
    public int numEnclaves(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        
        // 1. Sink boundary land
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 1) {
                    dfs(grid, i, j, m, n);
                }
            }
        }
        
        // 2. Count remaining
        int count = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    count++;
                }
            }
        }
        return count;
    }
    
    private void dfs(int[][] grid, int r, int c, int m, int n) {
        if(r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == 0) return;
        
        grid[r][c] = 0; // Sink
        
        dfs(grid, r + 1, c, m, n);
        dfs(grid, r - 1, c, m, n);
        dfs(grid, r, c + 1, m, n);
        dfs(grid, r, c - 1, m, n);
    }
}
```

## 🌍 Real-World Analogy
### **Castles and Moats:**
- The grid boundary is the "edge of the world" (freedom).
- Land connected to the edge allows escape.
- Enclaves are castles completely surrounded by the "sea" (0s) with no path to the edge.

## 🎯 Summary
✅ **Preprocessing (Boundary Sinking):** Eliminates all invalid paths first.
✅ **Counting:** After preprocessing, any remaining `1` is guaranteed to be an enclave.
