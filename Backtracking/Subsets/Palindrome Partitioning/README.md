# Palindrome Partitioning

## 🧩 Problem Statement
Given a string `s`, partition `s` such that every substring of the partition is a **palindrome**. Return all possible palindrome partitioning of `s`.

### 🔹 Example 1:
#### Input:
```plaintext
s = "aab"
```
#### Output:
```plaintext
[["a","a","b"],["aa","b"]]
```

### 🔹 Example 2:
#### Input:
```plaintext
s = "a"
```
#### Output:
```plaintext
[["a"]]
```

## 🔍 Approaches

### 1. Backtracking
We want to split the string at every possible position, but only if the left part is a palindrome.
- Start at index `0`.
- Iterate `end` from `start` to `s.length()`.
- Check if `s[start...end]` is a palindrome.
- If yes:
  - Add this substring to `path`.
  - Recurse from `end + 1`.
  - Backtrack.

### 2. Optimization (DP)
We can precompute the palindrome validity for all substrings using Dynamic Programming to make the check $O(1)$.
- `dp[i][j]` is true if `s[i...j]` is a palindrome.
- `s[i] == s[j]` and (`j-i <= 2` or `dp[i+1][j-1]`).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot 2^N)$ in worst case (e.g., "aaaa").
- **Space Complexity:** $O(N)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> path;
        backtrack(s, 0, path, res);
        return res;
    }

private:
    void backtrack(const string& s, int start, vector<string>& path, vector<vector<string>>& res) {
        if (start == s.length()) {
            res.push_back(path);
            return;
        }
        
        for (int i = start; i < s.length(); ++i) {
            if (isPalindrome(s, start, i)) {
                path.push_back(s.substr(start, i - start + 1));
                backtrack(s, i + 1, path, res);
                path.pop_back();
            }
        }
    }
    
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        res = []
        self._backtrack(s, 0, [], res)
        return res

    def _backtrack(self, s, start, path, res):
        if start == len(s):
            res.append(path[:])
            return
            
        for i in range(start, len(s)):
            if self._isPalindrome(s, start, i):
                path.append(s[start:i+1])
                self._backtrack(s, i + 1, path, res)
                path.pop()

    def _isPalindrome(self, s, left, right):
        while left < right:
            if s[left] != s[right]:
                return False
            left += 1
            right -= 1
        return True
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<String>> partition(String s) {
        List<List<String>> res = new ArrayList<>();
        backtrack(s, 0, new ArrayList<>(), res);
        return res;
    }
    
    private void backtrack(String s, int start, List<String> path, List<List<String>> res) {
        if (start == s.length()) {
            res.add(new ArrayList<>(path));
            return;
        }
        
        for (int i = start; i < s.length(); i++) {
            if (isPalindrome(s, start, i)) {
                path.add(s.substring(start, i + 1));
                backtrack(s, i + 1, path, res);
                path.remove(path.size() - 1);
            }
        }
    }
    
    private boolean isPalindrome(String s, int left, int right) {
        while (left < right) {
            if (s.charAt(left++) != s.charAt(right--)) return false;
        }
        return true;
    }
}
```

## 🌍 Real-World Analogy
### **Segmenting a Word:**
Cutting a ribbon into pieces, but every piece must look the same forward and backward.
`aab`: 
- Cut `a`, left with `ab`. 
  - Cut `a`, left with `b`.
    - Cut `b`. Done! (`a`, `a`, `b`)
- Cut `aa`, left with `b`.
  - Cut `b`. Done! (`aa`, `b`)

## 🎯 Summary
✅ **Splitting:** Try every possible cut point.
✅ **Constraint:** Only explore deeper if the current piece is a palindrome.
