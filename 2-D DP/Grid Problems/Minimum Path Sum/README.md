# Minimum Path Sum

## 🧩 Problem Statement
Given a `m x n` grid filled with non-negative numbers, find a path from **top-left** to **bottom-right**, which minimizes the sum of all numbers along its path.

**Note:** You can only move either down or right at any point in time.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [[1,3,1],
        [1,5,1],
        [4,2,1]]
```
#### Output:
```plaintext
7
```
**Explanation:** Because the path `1 -> 3 -> 1 -> 1 -> 1` minimizes the sum.

### 🔹 Example 2:
#### Input:
```plaintext
grid = [[1,2,3],
        [4,5,6]]
```
#### Output:
```plaintext
12
```

## 🔍 Approaches

### 1. Dynamic Programming (2D - In Place)
We can modify the grid in place or use a 2D DP array.
`dp[i][j]` represents the minimum path sum to reach `(i, j)`.
- **Logic:**
  - `dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`
- **Base Cases:**
  - `dp[0][0] = grid[0][0]`
  - Top row: `dp[0][j] = grid[0][j] + dp[0][j-1]` (only reachable from left)
  - Left col: `dp[i][0] = grid[i][0] + dp[i-1][0]` (only reachable from top)

### 2. Space Optimized DP (1D)
We only need the logic of the previous row to calculate the current row.
- `dp[j] = grid[i][j] + min(dp[j], dp[j-1])`
  - `dp[j]` (current val before update) is from above.
  - `dp[j-1]` (val just updated) is from the left.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$
- **Space Complexity:** $O(1)$ (if modifying in place) or $O(N)$ (if using 1D row optimization), or $O(M \cdot N)$ (standard 2D).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // In-place modification to save space
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 && j == 0) continue; // Start point
                else if (i == 0) grid[i][j] += grid[i][j-1]; // First row
                else if (j == 0) grid[i][j] += grid[i-1][j]; // First col
                else grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }
        
        return grid[m-1][n-1];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                elif i == 0:
                    grid[i][j] += grid[i][j-1]
                elif j == 0:
                    grid[i][j] += grid[i-1][j]
                else:
                    grid[i][j] += min(grid[i-1][j], grid[i][j-1])
                    
        return grid[m-1][n-1]
```

### Java
```java
class Solution {
    public int minPathSum(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;
                else if (i == 0) grid[i][j] += grid[i][j-1];
                else if (j == 0) grid[i][j] += grid[i-1][j];
                else grid[i][j] += Math.min(grid[i-1][j], grid[i][j-1]);
            }
        }
        return grid[m-1][n-1];
    }
}
```

## 🌍 Real-World Analogy
### **Driving with Tolls:**
You are driving from the Northwest of the country to the Southeast. Every city you pass through charges a specific toll. You want to pick the route that costs the least amount of money.

## 🎯 Summary
✅ **In-Place Modification:** We can overwrite the input grid to calculate cumulative costs, reducing space complexity to $O(1)$.
