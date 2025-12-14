# Number of Islands

## 🧩 Problem Statement
Given an `m x n` 2D binary grid `grid` which represents a map of `'1'`s (land) and `'0'`s (water), return the **number of islands**.

An **island** is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
```
#### Output:
```plaintext
1
```

### 🔹 Example 2:
#### Input:
```plaintext
grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
```
#### Output:
```plaintext
3
```

## 🔍 Approaches

### 1. Depth-First Search (DFS)
We iterate through every cell in the grid.
1. If we find a cell with value `'1'` (land), it is part of an unvisited island.
   - Increment `islandCount`.
   - Start a **DFS** to visit all connected land cells.
2. In the DFS:
   - Mark the current cell as visited (e.g., change `'1'` to `'0'` or use a `visited` set).
   - Recursively visit all 4 neighbors (up, down, left, right).
3. Continue iterating until all cells are processed.

### 2. Breadth-First Search (BFS)
Similar logic to DFS, but use a Queue to explore the island layer by layer.
1. If cell is `'1'`, increment count.
2. Push to queue, mark as visited.
3. While queue not empty, pop and push adjacent `'1'`s.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$. We visit each cell at most a constant number of times.
- **Space Complexity:** $O(M \cdot N)$ in worst case (DFS recursion stack or BFS queue).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return count;
    }

private:
    void dfs(vector<vector<char>>& grid, int r, int c, int m, int n) {
        if(r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') {
            return;
        }
        
        grid[r][c] = '0'; // Mark as visited (sink the island)
        
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
    def numIslands(self, grid: List[List[str]]) -> int:
        if not grid:
            return 0
            
        rows, cols = len(grid), len(grid[0])
        count = 0
        
        def dfs(r, c):
            if r < 0 or c < 0 or r >= rows or c >= cols or grid[r][c] == "0":
                return
            
            grid[r][c] = "0" # Mark as visited
            
            dfs(r + 1, c)
            dfs(r - 1, c)
            dfs(r, c + 1)
            dfs(r, c - 1)
            
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == "1":
                    count += 1
                    dfs(r, c)
                    
        return count
```

### Java
```java
class Solution {
    public int numIslands(char[][] grid) {
        if(grid == null || grid.length == 0) return 0;
        
        int m = grid.length;
        int n = grid[0].length;
        int count = 0;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == '1') {
                    count++;
                    dfs(grid, i, j);
                }
            }
        }
        return count;
    }
    
    private void dfs(char[][] grid, int r, int c) {
        int m = grid.length;
        int n = grid[0].length;
        
        if(r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == '0') {
            return;
        }
        
        grid[r][c] = '0'; // Mark as visited
        
        dfs(grid, r + 1, c);
        dfs(grid, r - 1, c);
        dfs(grid, r, c + 1);
        dfs(grid, r, c - 1);
    }
}
```

## 🌍 Real-World Analogy
### **Counting Puddles:**
Imagine looking at a pavement with rain puddles. You want to count how many distinct puddles there are.
You step into one puddle (DFS start), and walk around splashing until you've touched every connected part of it (marking visited). Then you look for the next dry puddle to start over.

## 🎯 Summary
✅ **Flood Fill:** The core algorithm is Flood Fill (like the paint bucket tool).
✅ **DFS vs BFS:** Both work identically for connectivity components. DFS is easier to implement recursively.
