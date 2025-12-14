# Unique Paths

## 🧩 Problem Statement
There is a robot on an `m x n` grid. The robot is initially located at the **top-left corner** (i.e., `grid[0][0]`). The robot tries to move to the **bottom-right corner** (i.e., `grid[m - 1][n - 1]`). The robot can only move either **down** or **right** at any point in time.

Given the two integers `m` and `n`, return the number of possible unique paths that the robot can take to reach the bottom-right corner.

The test cases are generated so that the answer will be less than or equal to `2 * 10^9`.

### 🔹 Example 1:
#### Input:
```plaintext
m = 3, n = 7
```
#### Output:
```plaintext
28
```

### 🔹 Example 2:
#### Input:
```plaintext
m = 3, n = 2
```
#### Output:
```plaintext
3
```
**Explanation:** 
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down

## 🔍 Approaches

### 1. Dynamic Programming (2D)
Let `dp[i][j]` be the number of unique paths to reach cell `(i, j)`.
- **Transitions:** Since we can only come from above or left:
  - `dp[i][j] = dp[i-1][j] + dp[i][j-1]`
- **Base Case:**
  - `dp[0][0] = 1`
  - First row `dp[0][j] = 1` (can only come from left)
  - First col `dp[i][0] = 1` (can only come from above)

### 2. Space Optimized DP (1D)
Notice `dp[i][j]` only depends on the current row and the previous row.
We can maintain a single row `dp` of size `n`.
- `dp[j] = dp[j] + dp[j-1]`
  - new `dp[j]` represents `dp[i][j]`
  - old `dp[j]` represents `dp[i-1][j]`
  - `dp[j-1]` represents `dp[i][j-1]` (already updated in current iteration)

### 3. Combinatorics
To reach `(m-1, n-1)` from `(0, 0)`, we must make exactly `m-1` Down moves and `n-1` Right moves.
Total moves = `(m-1) + (n-1) = m + n - 2`.
We need to choose `m-1` positions for Down moves (or `n-1` for Right moves) out of the total moves.
Formula: $C(m+n-2, m-1) = \frac{(m+n-2)!}{(m-1)!(n-1)!}$

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$ for DP, $O(\min(M, N))$ for Combinatorics.
- **Space Complexity:** $O(N)$ for optimized DP, $O(1)$ for Combinatorics.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[j] += dp[j-1];
            }
        }
        
        return dp[n-1];
    }
};
```

### Python
```python
class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [1] * n
        
        for i in range(1, m):
            for j in range(1, n):
                dp[j] += dp[j-1]
                
        return dp[n-1]
```

### Java
```java
class Solution {
    public int uniquePaths(int m, int n) {
        int[] dp = new int[n];
        for(int i=0; i<n; i++) dp[i] = 1;
        
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                dp[j] += dp[j-1];
            }
        }
        return dp[n-1];
    }
}
```

## 🌍 Real-World Analogy
### **Manhattan Grid:**
Walking in a city with a grid layout (like NYC). To get from 1st Ave & 1st St to 5th Ave & 3rd St, you can only walk East or South (towards higher numbers). How many different routes can you take?

## 🎯 Summary
✅ **Pascal's Triangle:** The path counts on the grid mirror the values in Pascal's Triangle.
✅ **Combinatorics:** This is a classic "stars and bars" or binomial coefficient problem.
