# Coin Change Problem

## 🧩 Problem Statement
You are given an integer array `coins` representing coins of different denominations and an integer `amount` representing a total amount of money.

Return the **fewest number of coins** that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return `-1`.

You may assume that you have an infinite number of each kind of coin.

### 🔹 Example 1:
#### Input:
```plaintext
coins = [1,2,5], amount = 11
```
#### Output:
```plaintext
3
```
**Explanation:** 11 = 5 + 5 + 1.

### 🔹 Example 2:
#### Input:
```plaintext
coins = [2], amount = 3
```
#### Output:
```plaintext
-1
```

## 🔍 Approaches

### 1. Dynamic Programming (Unbounded Knapsack Pattern)
This is an **Unbounded Knapsack** problem because we can use each coin multiple times. We want to minimize the number of items (coins) to reach a specific capacity (amount).

#### Tabulation (Bottom-Up):
Create a 1D array `dp` of size `amount + 1`.
- `dp[i]` represents the minimum coins needed to make amount `i`.
- **Initialization:**
  - `dp[0] = 0` (0 coins needed for 0 amount).
  - `dp[i] = infinity` for `i > 0` (initially unreachable).
- **Transition:**
  - Iterate through all amounts from `1` to `amount`.
  - For each `coin` in `coins`:
    - If `i - coin >= 0` and `dp[i - coin] != infinity`:
      - `dp[i] = min(dp[i], dp[i - coin] + 1)`

Finally, if `dp[amount]` is still infinity, return `-1`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(S \cdot N)$, where $S$ is the amount and $N$ is the number of coin denominations.
- **Space Complexity:** $O(S)$ for the DP array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // Initialize dp array with amount + 1 (impossible max value)
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; ++i) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        
        return (dp[amount] > amount) ? -1 : dp[amount];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        # Initialize dp array with amount + 1
        dp = [amount + 1] * (amount + 1)
        dp[0] = 0
        
        for i in range(1, amount + 1):
            for coin in coins:
                if i - coin >= 0:
                    dp[i] = min(dp[i], dp[i - coin] + 1)
                    
        return dp[amount] if dp[amount] <= amount else -1
```

### Java
```java
import java.util.Arrays;

class Solution {
    public int coinChange(int[] coins, int amount) {
        int max = amount + 1;
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, max);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }
}
```

## 🌍 Real-World Analogy
### **Vending Machine Change:**
The machine wants to dispense exactly $X amount of change using the fewest coins possible to keep its hopper full. It checks combinations of quarters, dimes, nickels...

## 🎯 Summary
✅ **Unbounded Knapsack:** Use items multiple times.
✅ **Minimization Problem:** Initialize with infinity, use `min()` function.
