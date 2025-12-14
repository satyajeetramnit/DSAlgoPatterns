# Interleaving String

## 🧩 Problem Statement
Given strings `s1`, `s2`, and `s3`, find whether `s3` is formed by an **interleaving** of `s1` and `s2`.

An interleaving of two strings `s` and `t` is a configuration where `s` and `t` are divided into `n` and `m` substrings respectively, such that:
- `s = s_1 + s_2 + ... + s_n`
- `t = t_1 + t_2 + ... + t_m`
- `|n - m| <= 1`
- The interleaving is `s_1 + t_1 + s_2 + t_2 + ...` or `t_1 + s_1 + t_2 + s_2 + ...`

Essentially, `s3` is formed by shuffling `s1` and `s2` while maintaining the relative order of characters from each string.

### 🔹 Example 1:
#### Input:
```plaintext
s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
```
#### Output:
```plaintext
true
```
**Explanation:** 
`s1` split: "aa" + "bc" + "c"
`s2` split: "dbbc" + "a"
Interleaved: "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac"

### 🔹 Example 2:
#### Input:
```plaintext
s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
```
#### Output:
```plaintext
false
```

## 🔍 Approaches

### 1. Dynamic Programming (2D)
Let `dp[i][j]` be true if `s3[0...i+j-1]` is formed by interleaving `s1[0...i-1]` and `s2[0...j-1]`.
- **Transitions:**
  - If we pick last char from `s1`: `dp[i][j] = dp[i-1][j] && s1[i-1] == s3[i+j-1]`
  - If we pick last char from `s2`: `dp[i][j] = dp[i][j-1] && s2[j-1] == s3[i+j-1]`
  - `dp[i][j]` is true if either of the above is true.
- **Base Case:**
  - `dp[0][0] = true`
  - First row `dp[0][j]`: `dp[0][j-1] && s2[j-1] == s3[j-1]`
  - First col `dp[i][0]`: `dp[i-1][0] && s1[i-1] == s3[i-1]`

### 2. Space Optimized DP (1D)
Notice `dp[i][j]` depends on `dp[i][j-1]` (left) and `dp[i-1][j]` (up).
We can use a 1D boolean array `dp` of size `len(s2) + 1`.
- `dp[j]` becomes `dp[i][j]`.
- Old `dp[j]` acts as `dp[i-1][j]` (from above).
- `dp[j-1]` is new `dp[i][j-1]` (calculated in current loop).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$
- **Space Complexity:** $O(M \cdot N)$ (standard) or $O(\min(M, N))$ (optimized).

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.length(), n = s2.length(), k = s3.length();
        if (m + n != k) return false;
        
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        // Initialize first row (using only s2)
        for (int j = 1; j <= n; ++j) {
            dp[j] = dp[j-1] && (s2[j-1] == s3[j-1]);
        }
        
        for (int i = 1; i <= m; ++i) {
            dp[0] = dp[0] && (s1[i-1] == s3[i-1]); // Update first column
            for (int j = 1; j <= n; ++j) {
                // dp[j] is currently dp[i-1][j] (from top)
                // dp[j-1] is currently dp[i][j-1] (from left)
                bool fromTop = dp[j] && (s1[i-1] == s3[i+j-1]);
                bool fromLeft = dp[j-1] && (s2[j-1] == s3[i+j-1]);
                dp[j] = fromTop || fromLeft;
            }
        }
        
        return dp[n];
    }
};
```

### Python
```python
class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if len(s1) + len(s2) != len(s3):
            return False
            
        m, n = len(s1), len(s2)
        dp = [False] * (n + 1)
        dp[0] = True
        
        # Init first row
        for j in range(1, n + 1):
            dp[j] = dp[j-1] and s2[j-1] == s3[j-1]
            
        for i in range(1, m + 1):
            dp[0] = dp[0] and s1[i-1] == s3[i-1]
            for j in range(1, n + 1):
                from_top = dp[j] and s1[i-1] == s3[i+j-1]
                from_left = dp[j-1] and s2[j-1] == s3[i+j-1]
                dp[j] = from_top or from_left
                
        return dp[n]
```

### Java
```java
class Solution {
    public boolean isInterleave(String s1, String s2, String s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        
        int m = s1.length();
        int n = s2.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;
        
        for (int j = 1; j <= n; j++) {
            dp[j] = dp[j-1] && s2.charAt(j-1) == s3.charAt(j-1);
        }
        
        for (int i = 1; i <= m; i++) {
            dp[0] = dp[0] && s1.charAt(i-1) == s3.charAt(i-1);
            for (int j = 1; j <= n; j++) {
                boolean fromTop = dp[j] && s1.charAt(i-1) == s3.charAt(i+j-1);
                boolean fromLeft = dp[j-1] && s2.charAt(j-1) == s3.charAt(i+j-1);
                dp[j] = fromTop || fromLeft;
            }
        }
        
        return dp[n];
    }
}
```

## 🌍 Real-World Analogy
### **Shuffling Cards / Merging Traffic:**
Think of a zipper merge in traffic. Cars from two lanes (`s1`, `s2`) merge into a single lane (`s3`). The relative order of cars from the same origin lane is preserved, but they are interleaved with cars from the other lane.

## 🎯 Summary
✅ **Zipper Logic:** DP effectively checks if the zipper merge is valid at every step.
