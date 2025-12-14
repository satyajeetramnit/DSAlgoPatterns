# Dungeon Game

## 🧩 Problem Statement
The demons had captured the princess and imprisoned her in the **bottom-right corner** of a `dungeon`. The `dungeon` consists of `m x n` rooms laid out in a 2D grid. Our valiant knight was initially positioned in the **top-left corner** and must fight his way through `dungeon` to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to `0` or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only **rightward** or **downward** in each step.

Return the **knight's minimum initial health** so that he can rescue the princess.

### 🔹 Example 1:
#### Input:
```plaintext
dungeon = [[-2, -3, 3],
           [-5, -10, 1],
           [10, 30, -5]]
```
#### Output:
```plaintext
7
```
**Explanation:** The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.

1. Start at `[-2]` (Need 7 -> moves to 5)
2. Move Right to `[-3]` (Need 5 -> moves to 2)
3. Move Right to `[3]` (Need 2 -> moves to 5)
4. Move Down to `[1]` (Need 5 -> moves to 6)
5. Move Down to `[-5]` (Need 6 -> moves to 1 => Success)

### 🔹 Example 2:
#### Input:
```plaintext
dungeon = [[0]]
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Dynamic Programming (Bottom-Up)
We should work **backwards** from the princess to the start.
Let `dp[i][j]` be the minimum health the knight needs to have **before entering** room `(i, j)` to safely reach the end.

- **Transition:**
  - From `(i, j)`, we can go to `(i+1, j)` (Down) or `(i, j+1)` (Right).
  - We want to pick the path requiring less health: `min(dp[i+1][j], dp[i][j+1])`.
  - Let this minimum required next health be `min_next`.
  - The health required at `(i, j)` must satisfy: `curr_health + dungeon[i][j] >= min_next`.
  - Therefore, `curr_health >= min_next - dungeon[i][j]`.
  - Also, `curr_health` must be at least 1 (to be alive).
  - So: `dp[i][j] = max(1, min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j])`.

- **Base Cases:**
  - At the princess `(m-1, n-1)`: Next state is "exit" dealing 0 damage, requiring 1 HP.
    `dp[m-1][n-1] = max(1, 1 - dungeon[m-1][n-1])`.
  - Boundary: Imagine an infinitely high cost wall around the grid, so `min` will always pick the valid inner cell.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$
- **Space Complexity:** $O(M \cdot N)$ (or $O(N)$ with space optimization).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        
        // dp[i][j] stores min HP needed at dungeon[i][j]
        // Initialize with MAX_INT
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
        
        // Dummy values for bottom and right boundary for eased calculation at (m-1, n-1)
        dp[m][n-1] = 1;
        dp[m-1][n] = 1;
        
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int need = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
                dp[i][j] = max(1, need);
            }
        }
        
        return dp[0][0];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        m, n = len(dungeon), len(dungeon[0])
        
        # Initialize dp with infinity
        dp = [[float('inf')] * (n + 1) for _ in range(m + 1)]
        
        # Base case boundaries for the destination cell
        dp[m][n-1] = 1
        dp[m-1][n] = 1
        
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                need = min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j]
                dp[i][j] = max(1, need)
                
        return dp[0][0]
```

### Java
```java
class Solution {
    public int calculateMinimumHP(int[][] dungeon) {
        int m = dungeon.length;
        int n = dungeon[0].length;
        
        int[][] dp = new int[m + 1][n + 1];
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = Integer.MAX_VALUE;
            }
        }
        
        dp[m][n-1] = 1;
        dp[m-1][n] = 1;
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int need = Math.min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
                dp[i][j] = Math.max(1, need);
            }
        }
        
        return dp[0][0];
    }
}
```

## 🌍 Real-World Analogy
### **Budgeting for a Trip:**
You plan a trip where some cities earn you money (work gigs) and others cost money (expensive hotels). You want to know the minimum savings you need to start with so you never go bankrupt (balance < 0) before reaching your destination. Since you can earn money later, you work backwards to see how much "buffer" you need at each step.

## 🎯 Summary
✅ **Reverse DP:** Standard forward DP is hard here because `max(health)` doesn't necessarily mean best path (could lead to death locally). Minimizing required health from end is deterministic. 
