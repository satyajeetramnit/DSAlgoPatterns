# Perfect Squares

## 🧩 Problem Statement
Given an integer `n`, return the least number of perfect square numbers that sum to `n`.

A **perfect square** is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.

### 🔹 Example 1:
#### Input:
```plaintext
n = 12
```
#### Output:
```plaintext
3
```
**Explanation:** 12 = 4 + 4 + 4.

### 🔹 Example 2:
#### Input:
```plaintext
n = 13
```
#### Output:
```plaintext
2
```
**Explanation:** 13 = 4 + 9.

## 🔍 Approaches

### 1. Dynamic Programming ($O(N \sqrt{N})$)
- **Concept:** `dp[i]` = min squares to sum to `i`.
- **Transition:** `dp[i] = min(dp[i], dp[i - j*j] + 1)` for all `j*j <= i`.
- **Base Case:** `dp[0] = 0`.

### 2. Breadth-First Search ($O(N)$)
- **Concept:** Shortest path problem on a graph where nodes are numbers `0` to `n`. Edges exist from `u` to `v` if `v = u + square`.
- **Algorithm:**
  - Start BFS from `n`.
  - Level 1: `n - 1^2`, `n - 2^2`, ...
  - Stop when we reach 0. Depth is the answer.

### 3. Lagrange's Four Square Theorem ($O(\sqrt{N})$)
- **Theorem:** Every natural number can be represented as the sum of four integer squares.
- **Rules:**
  1. If `n` is a perfect square, answer is 1.
  2. If `n = 4^k * (8m + 7)`, answer is 4.
  3. If `n` is sum of two squares, answer is 2.
  4. Otherwise, answer is 3.

## ⏳ Time & Space Complexity
- **Time Complexity:**
  - DP: $O(N \sqrt{N})$.
  - Mathematical (Lagrange): $O(\sqrt{N})$.
- **Space Complexity:**
  - DP: $O(N)$.
  - Mathematical: $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        // DP Approach
        vector<int> dp(n + 1, n);
        dp[0] = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j * j <= i; ++j) {
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
```

### Python
```python
class Solution:
    def numSquares(self, n: int) -> int:
        dp = [n] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            j = 1
            while j * j <= i:
                dp[i] = min(dp[i], dp[i - j * j] + 1)
                j += 1
                
        return dp[n]
```

### Java
```java
import java.util.Arrays;

class Solution {
    public int numSquares(int n) {
        int[] dp = new int[n + 1];
        Arrays.fill(dp, Integer.MAX_VALUE);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = Math.min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
}
```

## 🌍 Real-World Analogy
### **Tiling a Bathroom:**
You want to tile a floor of area `n` using only square tiles of sizes $1 \times 1$, $2 \times 2$, $3 \times 3$, etc.
- You want to use the **minimum number of tiles** possible.
- This is a partition problem: How can we sum up square numbers to equal `n` with the fewest terms?

### **Change Making:**
This is exactly the Coin Change problem where the denominations are dynamic: $1^2, 2^2, 3^2, \dots$ (1, 4, 9, 16...). We want to pay amount `n` with the fewest coins.

## 🎯 Summary
✅ **DP:** Standard variation of Unbounded Knapsack.
✅ **Math:** Lagrange's Theorem provides a direct mathematical categorization.
