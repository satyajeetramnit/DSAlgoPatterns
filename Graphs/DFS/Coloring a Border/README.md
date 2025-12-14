# Coloring a Border

## 🧩 Problem Statement
You are given an `m x n` integer matrix `grid`, and three integers `row`, `col`, and `color`. Each value in the grid represents the color of the square at that location.

Two squares belong to the same **connected component** if they have the same color and are next to each other in any of the 4 directions.

The **border** of a connected component is all the squares in the connected component that are either:
1. **On the boundary** of the grid (the first or last row or column), or
2. **Adjacent** to a square not belonging to the connected component.

You should color the **border** of the connected component that contains the square `grid[row][col]` with the given `color`.

Return the final grid.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
```
#### Output:
```plaintext
[[3,3],[3,2]]
```

### 🔹 Example 2:
#### Input:
```plaintext
grid = [[1,2,2],[2,3,2]], row = 0, col = 1, color = 3
```
#### Output:
```plaintext
[[1,3,3],[2,3,3]]
```

## 🔍 Approaches

### 1. DFS / BFS with Border Check
1. **Identify Component:** Start DFS/BFS from `(row, col)` to traverse the connected component of the original color `oldColor`.
2. **Determine Border:** For each visited cell in the component:
   - Check if it is on the grid boundary.
   - Check if any of its 4 neighbors has a color **different** from `oldColor`. (Note: We must handle visited cells correctly so we don't count "visited `oldColor`" as "different color").
3. **Coloring:**
   - If a cell is a border, add it to a list of `borders`.
   - After traversal, update all cells in `borders` to `newColor`.
   - *Alternative:* We can modify in-place if we use a `visited` set to distinguish between "processed" and "original color".

#### Algorithm Steps:
1. `oldColor = grid[row][col]`.
2. `visited` set to track visited cells.
3. `borders` list to store border cells.
4. **DFS(r, c):**
   - Mark `(r, c)` as visited.
   - `isBorder = false`.
   - Check 4 neighbors:
     - If neighbor out of bounds -> `isBorder = true`.
     - Else if neighbor is `oldColor` and not visited -> `DFS(neighbor)`.
     - Else if neighbor is NOT `oldColor` and (not visited or visited) -> `isBorder = true`. (Wait, if it's visited, it MUST be `oldColor` because we only visit `oldColor` cells. So we only care if neighbor is *not* `oldColor` and *not* visited?)
   - **Correction:** A cell is a border if it touches the outside OR touches a cell of a different color.
     - Iterate 4 directions.
     - If neighbor out of bounds, current `(r, c)` is border.
     - If neighbor is different color (and not visited? No, different color is sufficient), `(r, c)` is border.
     - Recurse on neighbors that are `oldColor` and not visited.
5. Apply colors to `borders`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$. We visit each cell of the component once.
- **Space Complexity:** $O(M \cdot N)$ for recursion/visited set.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size();
        int n = grid[0].size();
        int oldColor = grid[row][col];
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> borders;
        
        dfs(grid, row, col, oldColor, visited, borders, m, n);
        
        for(auto& p : borders) {
            grid[p.first][p.second] = color;
        }
        
        return grid;
    }

private:
    void dfs(vector<vector<int>>& grid, int r, int c, int oldColor, 
             vector<vector<bool>>& visited, vector<pair<int, int>>& borders, int m, int n) {
        
        visited[r][c] = true;
        bool isBorder = false;
        
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for(auto& d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            
            if(nr < 0 || nr >= m || nc < 0 || nc >= n) {
                isBorder = true;
            } else if(!visited[nr][nc] && grid[nr][nc] == oldColor) {
                dfs(grid, nr, nc, oldColor, visited, borders, m, n);
            } else if(grid[nr][nc] != oldColor && !visited[nr][nc]) {
                 // Neighbor is diff color (and unvisited logic ensures it's truly original diff color)
                 isBorder = true;
            } else if (visited[nr][nc] && grid[nr][nc] != oldColor) {
                // Previously visited but changed? (Wait, we update AFTER. So grid[nr][nc] is still oldColor)
                // Actually, if we update AFTER, then grid value is stable.
                // Neighbor is visited. It MUST be oldColor. So this case (visited && != oldColor) is impossible if we batch update.
            }
        }
        // Simpler Border Check:
        // A cell is border if:
        // 1. On boundary
        // 2. Has a neighbor with Diff Color (Original)
        // Since we update at the end, grid[nr][nc] is reliable.
        // We just need to check if neighbor is same color.
        
        // Re-logic:
        // Count neighbors that are part of the component (oldColor).
        // If count < 4, it means at least one neighbor is out-of-bounds OR diff color.
        // Thus, use count.
    }
};

// ... Wait, let's refine the logic for cleanliness.
```

#### Refined Algorithm:
1. `DFS(r, c)` visits connected `oldColor` cells.
2. For each `(r, c)`, check 4 neighbors.
3. If neighbor is out of bounds OR `grid[neighbor]` != `oldColor`, then `(r, c)` is border.
4. BUT, allow DFS to continue to unvisited `oldColor` neighbors.
5. If `(r, c)` is border, add to list.

### Refined C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int oldColor = grid[row][col];
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> borders;
        
        dfs(grid, row, col, oldColor, visited, borders);
        
        for(auto& p : borders) {
            grid[p.first][p.second] = color;
        }
        return grid;
    }

private:
    void dfs(vector<vector<int>>& grid, int r, int c, int oldColor, 
             vector<vector<bool>>& visited, vector<pair<int, int>>& borders) {
        
        visited[r][c] = true;
        int m = grid.size();
        int n = grid[0].size();
        bool isBorder = false;
        
        int dirs[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for(auto& d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            
            if(nr < 0 || nr >= m || nc < 0 || nc >= n || (!visited[nr][nc] && grid[nr][nc] != oldColor)) {
                // Boundary or Different Color (Unvisited to check original state, but actually if we don't mitigate, visited might be tricky... 
                // Ah, we use `visited` to track traversal. `grid` is untouched. 
                // So grid[nr][nc] != oldColor is sufficient check for original color diff.)
                isBorder = true;
            } else if(!visited[nr][nc] && grid[nr][nc] == oldColor) {
                dfs(grid, nr, nc, oldColor, visited, borders);
            }
            
            // Wait, what if neighbor is visited? It is part of component. It implies THIS direction is NOT a border.
            // But we need to check ALL 4 directions. If ANY is border-condition, then isBorder = true.
        }
        
        // Simpler: Count valid component neighbors.
        // int componentNeighbors = 0;
        // Check 4 dirs: if in-bounds AND (grid == oldColor) -> componentNeighbors++ (even if visited).
        // If componentNeighbors < 4 -> isBorder = true.
        // *Need careful check on (grid == oldColor) because grid is static.*
        
        // Re-re-refined Logic:
        // Standard DFS traversal.
        // Inside DFS(r, c):
        //   Traverse 4 neighbors.
        //   If neighbor in-bounds AND same-color AND !visited: DFS(neighbor).
        //   
        //   Distinct "Is Border" check:
        //   Iterate 4 neighbors.
        //   If neighbor out-of-bounds OR grid[r][c] != oldColor: It's a border.
    }
};
// Final Logic below in implementations.
```

### Python
```python
from typing import List

class Solution:
    def colorBorder(self, grid: List[List[int]], row: int, col: int, color: int) -> List[List[int]]:
        old_color = grid[row][col]
        rows, cols = len(grid), len(grid[0])
        visited = set()
        borders = []
        
        def dfs(r, c):
            visited.add((r, c))
            is_border = False
            
            for dr, dc in [(-1,0), (1,0), (0,-1), (0,1)]:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < rows and 0 <= nc < cols:
                    if grid[nr][nc] == old_color:
                        if (nr, nc) not in visited:
                            dfs(nr, nc)
                    else:
                        is_border = True # Neighbor is diff color
                else:
                    is_border = True # Out of bounds
            
            if is_border:
                borders.append((r, c))
        
        dfs(row, col)
        
        for r, c in borders:
            grid[r][c] = color
            
        return grid
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class Solution {
    public int[][] colorBorder(int[][] grid, int row, int col, int color) {
        int oldColor = grid[row][col];
        int m = grid.length;
        int n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        List<int[]> borders = new ArrayList<>();
        
        dfs(grid, row, col, oldColor, visited, borders);
        
        for(int[] p : borders) {
            grid[p[0]][p[1]] = color;
        }
        return grid;
    }
    
    private void dfs(int[][] grid, int r, int c, int oldColor, 
                     boolean[][] visited, List<int[]> borders) {
        visited[r][c] = true;
        boolean isBorder = false;
        int[][] dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for(int[] d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            
            if(nr < 0 || nr >= grid.length || nc < 0 || nc >= grid[0].length) {
                isBorder = true;
            } else if(grid[nr][nc] != oldColor) {
                isBorder = true;
            } else if(!visited[nr][nc]) {
                dfs(grid, nr, nc, oldColor, visited, borders);
            }
        }
        
        if(isBorder) {
            borders.add(new int[]{r, c});
        }
    }
}
```

## 🌍 Real-World Analogy
### **Painting a Fence (Outline):**
You have a shape filled with color. You want to highlight just the **outline** (border) with a new color, leaving the inside fill as is. You walk along the edge where the shape meets "empty space" or "different color" and paint it.

## 🎯 Summary
✅ **Separation of Concerns:** Traverse first (to identify component), then Color. Do not modify `grid` while traversing to avoid confusing the "old color" check.
✅ **Border Definition:** Touching Boundary OR Touching Different Color.
