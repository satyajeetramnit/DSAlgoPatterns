# Burst Balloons

## 🧩 Problem Statement
You are given `n` balloons, indexed from `0` to `n - 1`. Each balloon is painted with a number on it represented by an array `nums`. You are asked to burst all the balloons.

If you burst the `i-th` balloon, you will get `nums[i - 1] * nums[i] * nums[i + 1]` coins. If `i - 1` or `i + 1` goes out of bounds of the array, then treat it as if there is a balloon with a `1` painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [3,1,5,8]
```
#### Output:
```plaintext
167
```
**Explanation:** 
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1,5]
```
#### Output:
```plaintext
10
```

## 🔍 Approaches

### 1. Dynamic Programming (Matrix Chain Multiplication Pattern)
This problem can be framed as finding the order of bursting. It's easier to think about which balloon is burst **LAST** in a given range.

Let `dp[i][j]` be the maximum coins obtained from bursting all balloons **strictly between** index `i` and `j` (exclusive).
- We pad the input array with `1` at the beginning and end. New size is `n + 2`.
- We want to find `dp[0][n + 1]`.
- **Logic:**
  - For a range `(i, j)`, assume `k` is the index of the balloon burst **last** within this range (`i < k < j`).
  - Since `k` is the last one in `(i, j)`, at the moment it is burst, its neighbors are `nums[i]` and `nums[j]` (because everything between `i` and `k`, and `k` and `j` has already been burst).
  - Coins from bursting `k` last: `nums[i] * nums[k] * nums[j]`.
  - Total coins: `dp[i][k] + dp[k][j] + nums[i] * nums[k] * nums[j]`.
  - We try all valid `k` and take the maximum.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^3)$ because of three nested loops (length, left, split point).
- **Space Complexity:** $O(N^2)$ for the DP table.

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        // Pad nums with 1 at both ends
        vector<int> paddedNums;
        paddedNums.push_back(1);
        for(int x : nums) paddedNums.push_back(x);
        paddedNums.push_back(1);
        
        int n = paddedNums.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Iterate over length of the range (from 1 balloon to original N balloons)
        for (int len = 1; len <= nums.size(); ++len) {
            for (int left = 0; left < n - len - 1; ++left) {
                int right = left + len + 1;
                // Try every possible last balloon k between left and right
                for (int k = left + 1; k < right; ++k) {
                    dp[left][right] = max(dp[left][right], 
                        paddedNums[left] * paddedNums[k] * paddedNums[right] + dp[left][k] + dp[k][right]);
                }
            }
        }
        
        return dp[0][n-1];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def maxCoins(self, nums: List[int]) -> int:
        padded_nums = [1] + nums + [1]
        n = len(padded_nums)
        dp = [[0] * n for _ in range(n)]
        
        # len is the number of balloons strictly between left and right
        for length in range(1, len(nums) + 1):
            for left in range(n - length - 1):
                right = left + length + 1
                for k in range(left + 1, right):
                    dp[left][right] = max(dp[left][right],
                        padded_nums[left] * padded_nums[k] * padded_nums[right] + dp[left][k] + dp[k][right])
                        
        return dp[0][n-1]
```

### Java
```java
class Solution {
    public int maxCoins(int[] nums) {
        int n = nums.length;
        int[] paddedNums = new int[n + 2];
        paddedNums[0] = 1;
        paddedNums[n + 1] = 1;
        for (int i = 0; i < n; i++) paddedNums[i + 1] = nums[i];
        
        int[][] dp = new int[n + 2][n + 2];
        
        for (int len = 1; len <= n; len++) {
            for (int left = 0; left < n + 2 - len - 1; left++) {
                int right = left + len + 1;
                for (int k = left + 1; k < right; k++) {
                    dp[left][right] = Math.max(dp[left][right], 
                        paddedNums[left] * paddedNums[k] * paddedNums[right] + dp[left][k] + dp[k][right]);
                }
            }
        }
        
        return dp[0][n + 1];
    }
}
```

## 🌍 Real-World Analogy
### **Demolition Strategy:**
Imagine demolishing buildings in a row. Taking down a building might affect the stability (or value/cost) of adjacent ones differently depending on what is next to it. You want to plan the sequence to maximize salvage value.

## 🎯 Summary
✅ **Reverse Thinking:** Assuming which item is Last allows us to split the problem into independent subproblems.
✅ **Matrix Chain pattern:** This is a classic $O(N^3)$ interval DP structure.
