# Rotten Oranges

## 🧩 Problem Statement
You are given an `m x n` grid where each cell can have one of three values:
- `0`: representing an empty cell,
- `1`: representing a fresh orange, or
- `2`: representing a rotten orange.

Every minute, any fresh orange that is **4-directionally adjacent** to a rotten orange becomes rotten.

Return the **minimum number of minutes** that must elapse until no cell has a fresh orange. If this is impossible, return `-1`.

### 🔹 Example 1:
#### Input:
```plaintext
grid = [[2,1,1],[1,1,0],[0,1,1]]
```
#### Output:
```plaintext
4
```

### 🔹 Example 2:
#### Input:
```plaintext
grid = [[0,2]]
```
#### Output:
```plaintext
0
```

## 🔍 Approaches

### 1. Multi-Source BFS
This problem asks for the minimum time to rot all oranges, which spreads level by level. This suggests BFS.
Since there can be multiple initially rotten oranges, we start BFS from **all of them simultaneously**.

#### Algorithm Steps:
1. **Initialize:** 
   - Queue `q`.
   - `freshCount = 0`.
   - `time = 0`.
2. **Scan Grid:** Iterate through the grid.
   - If cell is `2`, add to `q`.
   - If cell is `1`, increment `freshCount`.
3. **BFS:**
   - Loop while `q` is not empty **AND** `freshCount > 0`.
   - Process level by level (size of queue).
   - For each rotten orange, check 4 neighbors.
   - If neighbor is fresh (`1`):
     - Mark as rotten (`2`).
     - Decrement `freshCount`.
     - Add to `q`.
   - After processing neighbors, increment `time`.
4. **Final Check:** If `freshCount == 0`, return `time`. Else, return `-1`.

**Note:** If `freshCount` is 0 initially, return 0.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$. We visit each cell at most once.
- **Space Complexity:** $O(M \cdot N)$ for the queue.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pair<int, int>> q;
        int freshCount = 0;
        
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 2) {
                    q.push({i, j});
                } else if(grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }
        
        if(freshCount == 0) return 0;
        
        int minutes = 0;
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while(!q.empty() && freshCount > 0) {
            int size = q.size();
            while(size--) {
                auto [r, c] = q.front();
                q.pop();
                
                for(auto& dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Rot it
                        freshCount--;
                        q.push({nr, nc});
                    }
                }
            }
            minutes++;
        }
        
        return freshCount == 0 ? minutes : -1;
    }
};
```

### Python
```python
from typing import List
from collections import deque

class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        rows, cols = len(grid), len(grid[0])
        q = deque()
        fresh_count = 0
        
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == 2:
                    q.append((r, c))
                elif grid[r][c] == 1:
                    fresh_count += 1
                    
        if fresh_count == 0:
            return 0
            
        minutes = 0
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        while q and fresh_count > 0:
            for _ in range(len(q)):
                r, c = q.popleft()
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == 1:
                        grid[nr][nc] = 2 # Rot it
                        fresh_count -= 1
                        q.append((nr, nc))
            minutes += 1
            
        return minutes if fresh_count == 0 else -1
```

### Java
```java
import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int orangesRotting(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        
        Queue<int[]> q = new LinkedList<>();
        int freshCount = 0;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 2) {
                    q.offer(new int[]{i, j});
                } else if(grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }
        
        if(freshCount == 0) return 0;
        
        int minutes = 0;
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while(!q.isEmpty() && freshCount > 0) {
            int size = q.size();
            while(size-- > 0) {
                int[] curr = q.poll();
                int r = curr[0];
                int c = curr[1];
                
                for(int[] dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Rot it
                        freshCount--;
                        q.offer(new int[]{nr, nc});
                    }
                }
            }
            minutes++;
        }
        
        return freshCount == 0 ? minutes : -1;
    }
}
```

## 🌍 Real-World Analogy
### **Zombie Apocalypse:**
Fresh oranges are humans, rotten oranges are zombies.
- At time 0, multi-source infection starts.
- Zombies infect adjacent humans every minute.
- Can everyone be infected? If islanded humans exist, answer is impossible (-1).

## 🎯 Summary
✅ **Multi-Source BFS:** Start queue with ALL initial sources.
✅ **Level Tracking:** Increment time only after processing full queue snapshot.
