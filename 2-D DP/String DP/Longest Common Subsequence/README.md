# Longest Common Subsequence

## 🧩 Problem Statement
Given two strings `text1` and `text2`, return the length of their longest common subsequence. If there is no common subsequence, return `0`.

A **subsequence** of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, `"ace"` is a subsequence of `"abcde"`.

A **common subsequence** of two strings is a subsequence that is common to both strings.

### 🔹 Example 1:
#### Input:
```plaintext
text1 = "abcde", text2 = "ace" 
```
#### Output:
```plaintext
3
```
**Explanation:** The longest common subsequence is "ace" and its length is 3.

### 🔹 Example 2:
#### Input:
```plaintext
text1 = "abc", text2 = "abc"
```
#### Output:
```plaintext
3
```
**Explanation:** The longest common subsequence is "abc" and its length is 3.

## 🔍 Approaches

### 1. Dynamic Programming (2D)
Let `dp[i][j]` be the length of LCS between `text1[0...i-1]` and `text2[0...j-1]`.
- **Match:** If `text1[i-1] == text2[j-1]`, then `dp[i][j] = 1 + dp[i-1][j-1]`.
  - We found a match, so we extend the LCS found without these characters.
- **No Match:** If `text1[i-1] != text2[j-1]`, then `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`.
  - We skip either the character from `text1` or `text2` and take the max length found so far.

### 2. Space Optimized DP (1D)
Notice `dp[i][j]` only depends on the previous row `i-1`.
We can use a 1D array `dp` of size `len(text2) + 1`.
When updating `dp[j]`, we need `dp[i-1][j-1]` (diagonal).
We can store `dp[i-1][j-1]` in a `prev` variable before overwriting `dp[j]`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N)$
- **Space Complexity:** $O(M \cdot N)$ (standard) or $O(\min(M, N))$ (optimized).

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        // Ensure text2 is smaller for space optimization
        if (m < n) return longestCommonSubsequence(text2, text1);
        
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= m; ++i) {
            int prev = 0; // Represents dp[i-1][j-1]
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j]; // Store current dp[j] (which is dp[i-1][j]) for next iteration
                if (text1[i-1] == text2[j-1]) {
                    dp[j] = 1 + prev;
                } else {
                    dp[j] = max(dp[j], dp[j-1]);
                }
                prev = temp; // Update prev to be the old dp[j]
            }
        }
        
        return dp[n];
    }
};
```

### Python
```python
class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        if len(text1) < len(text2):
            text1, text2 = text2, text1
            
        m, n = len(text1), len(text2)
        dp = [0] * (n + 1)
        
        for i in range(1, m + 1):
            prev = 0
            for j in range(1, n + 1):
                temp = dp[j]
                if text1[i-1] == text2[j-1]:
                    dp[j] = 1 + prev
                else:
                    dp[j] = max(dp[j], dp[j-1])
                prev = temp
                
        return dp[n]
```

### Java
```java
class Solution {
    public int longestCommonSubsequence(String text1, String text2) {
        if (text1.length() < text2.length()) {
            return longestCommonSubsequence(text2, text1);
        }
        
        int m = text1.length();
        int n = text2.length();
        int[] dp = new int[n + 1];
        
        for (int i = 1; i <= m; i++) {
            int prev = 0;
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];
                if (text1.charAt(i-1) == text2.charAt(j-1)) {
                    dp[j] = 1 + prev;
                } else {
                    dp[j] = Math.max(dp[j], dp[j-1]);
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }
}
```

## 🌍 Real-World Analogy
### **DNA Sequencing:**
Finding the similarity between two DNA strands involves finding the longest common subsequence of nucleotides (A, C, G, T) to determine evolutionary relationships.

## 🎯 Summary
✅ **Fundamental String DP:** LCS is the basis for diff tools (like git diff), spell checkers, and bioinformatics.
