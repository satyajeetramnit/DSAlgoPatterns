# Edit Distance

## 🧩 Problem Statement
Given two strings `word1` and `word2`, return the minimum number of operations required to convert `word1` to `word2`.

You have the following three operations permitted on a word:
1. **Insert** a character
2. **Delete** a character
3. **Replace** a character

### 🔹 Example 1:
#### Input:
```plaintext
word1 = "horse", word2 = "ros"
```
#### Output:
```plaintext
3
```
**Explanation:** 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')

### 🔹 Example 2:
#### Input:
```plaintext
word1 = "intention", word2 = "execution"
```
#### Output:
```plaintext
5
```
**Explanation:** 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')

## 🔍 Approaches

### 1. Dynamic Programming (2D)
Let `dp[i][j]` be the minimum edit distance between `word1[0...i-1]` and `word2[0...j-1]`.
- **Match:** If `word1[i-1] == word2[j-1]`, we don't need any new operation.
  - `dp[i][j] = dp[i-1][j-1]`
- **No Match:** We take the minimum of 3 possible operations + 1.
  - **Insert:** `dp[i][j-1] + 1` (Insert char matching `word2[j-1]` into `word1`)
  - **Delete:** `dp[i-1][j] + 1` (Delete `word1[i-1]`)
  - **Replace:** `dp[i-1][j-1] + 1` (Replace `word1[i-1]` with `word2[j-1]`)
  - `dp[i][j] = 1 + min(dp[i][j-1], dp[i-1][j], dp[i-1][j-1])`

- **Base Cases:**
  - `dp[i][0] = i`: Converting `word1[0...i-1]` to empty string requires `i` deletions.
  - `dp[0][j] = j`: Converting empty string to `word2[0...j-1]` requires `j` insertions.

### 2. Space Optimized DP (1D)
Similar to LCS, `dp[i][j]` depends on `i-1` and `j-1`. We can reduce space to $O(N)$ using a single array and a `prev` variable to store corner values.

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
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        
        for (int i = 0; i <= m; ++i) dp[i][0] = i;
        for (int j = 0; j <= n; ++j) dp[0][j] = j;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i-1] == word2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
                }
            }
        }
        
        return dp[m][n];
    }
};
```

### Python
```python
class Solution:
    def minDistance(self, word1: str, word2: str) -> int:
        m, n = len(word1), len(word2)
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(m + 1):
            dp[i][0] = i
        for j in range(n + 1):
            dp[0][j] = j
            
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i-1] == word2[j-1]:
                    dp[i][j] = dp[i-1][j-1]
                else:
                    dp[i][j] = 1 + min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])
                    
        return dp[m][n]
```

### Java
```java
class Solution {
    public int minDistance(String word1, String word2) {
        int m = word1.length();
        int n = word2.length();
        int[][] dp = new int[m + 1][n + 1];
        
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1.charAt(i-1) == word2.charAt(j-1)) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + Math.min(dp[i-1][j], Math.min(dp[i][j-1], dp[i-1][j-1]));
                }
            }
        }
        
        return dp[m][n];
    }
}
```

## 🌍 Real-World Analogy
### **Spell Checker:**
When you mistype a word, the spell checker suggests corrections based on Levenshtein distance. It suggests words that require the fewest keystrokes (insert, delete, replace) to match your typo.

## 🎯 Summary
✅ **Levenshtein Distance:** This algorithm calculates the most common metric for string similarity used in fuzzy matching.
