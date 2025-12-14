# Ones and Zeroes

## 🧩 Problem Statement
You are given an array of binary strings `strs` and two integers `m` and `n`.

Return the size of the largest subset of `strs` such that there are **at most** `m` `0`'s and `n` `1`'s in the subset.

A set `x` is a **subset** of a set `y` if all elements of `x` are also elements of `y`.

### 🔹 Example 1:
#### Input:
```plaintext
strs = ["10","0001","111001","1","0"], m = 5, n = 3
```
#### Output:
```plaintext
4
```
**Explanation:** The largest subset with at most 5 0's and 3 1's is `{"10", "0001", "1", "0"}`, so the answer is 4.
Other valid but smaller subsets include `{"10", "1", "0"}` (3 elements) and `{"111001"}` (1 element).

### 🔹 Example 2:
#### Input:
```plaintext
strs = ["10","0","1"], m = 1, n = 1
```
#### Output:
```plaintext
2
```
**Explanation:** The largest subest is `{"0", "1"}`, so the answer is 2. `{"10"}` has 1 zero and 1 one, which is also valid but size 1.

## 🔍 Approaches

### 1. Dynamic Programming (2D Knapsack)
This is a variation of the **0/1 Knapsack Problem**.
- **Items:** Each string in `strs`.
- **Cost:** Each item has **two costs**: number of 0's and number of 1's.
- **Value:** The value of each item is 1 (we want to maximize the count of items).
- **Capacity:** The knapsack has two capacities: `m` (for 0's) and `n` (for 1's).

#### Tabulation (Space Optimized):
Create a 2D array `dp[m+1][n+1]`.
- `dp[i][j]` represents the maximum number of strings we can pick with at most `i` zeros and `j` ones.
- **Initialization:** `dp` table initialized to 0.
- **Transition:**
  - For each string in `strs`, count its zeros (`z`) and ones (`o`).
  - Iterate `i` from `m` down to `z`.
  - Iterate `j` from `n` down to `o`.
  - `dp[i][j] = max(dp[i][j], 1 + dp[i - z][j - o])`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(S \cdot m \cdot n)$, where $S$ is the number of strings.
- **Space Complexity:** $O(m \cdot n)$ for the 2D DP array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (const string& s : strs) {
            int zeros = 0, ones = 0;
            for (char c : s) {
                if (c == '0') zeros++;
                else ones++;
            }
            
            for (int i = m; i >= zeros; --i) {
                for (int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], 1 + dp[i - zeros][j - ones]);
                }
            }
        }
        
        return dp[m][n];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        for s in strs:
            zeros = s.count('0')
            ones = s.count('1')
            
            for i in range(m, zeros - 1, -1):
                for j in range(n, ones - 1, -1):
                    dp[i][j] = max(dp[i][j], 1 + dp[i - zeros][j - ones])
                    
        return dp[m][n]
```

### Java
```java
class Solution {
    public int findMaxForm(String[] strs, int m, int n) {
        int[][] dp = new int[m + 1][n + 1];
        
        for (String s : strs) {
            int zeros = 0;
            int ones = 0;
            for (char c : s.toCharArray()) {
                if (c == '0') zeros++;
                else ones++;
            }
            
            for (int i = m; i >= zeros; i--) {
                for (int j = n; j >= ones; j--) {
                    dp[i][j] = Math.max(dp[i][j], 1 + dp[i - zeros][j - ones]);
                }
            }
        }
        
        return dp[m][n];
    }
}
```

## 🌍 Real-World Analogy
### **Packing a Dual-Compartment Bag:**
You have a bag with two compartments: one for cold items (limit `m` volume) and one for dry items (limit `n` volume). You have a list of packages, each taking up some cold space and some dry space. You want to fit as many packages as possible.

## 🎯 Summary
✅ **Multi-Dimensional Knapsack:** Expand the DP state to accommodate multiple constraints (0s and 1s).
