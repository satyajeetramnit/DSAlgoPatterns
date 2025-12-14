# Generate Parentheses

## 🧩 Problem Statement
Given `n` pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

### 🔹 Example 1:
#### Input:
```plaintext
n = 3
```
#### Output:
```plaintext
["((()))","(()())","(())()","()(())","()()()"]
```

### 🔹 Example 2:
#### Input:
```plaintext
n = 1
```
#### Output:
```plaintext
["()"]
```

## 🔍 Approaches

### 1. Backtracking (Open vs Close Count)
We view this as building a string of length `2n`. At each step, we can append `(` or `)`.
However, we must maintain validity:
1. We can add an opening parenthesis `(` if we haven't used all `n` opening parentheses yet (`open < n`).
2. We can add a closing parenthesis `)` if we have more open parentheses than closed ones currently (`close < open`).
3. Base Case: If the string length is `2n`, we have a valid combination.

### 2. Brute Force (Not Recommended)
Generate all $2^{2n}$ sequences of `(` and `)`, then check if valid. Much slower.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\frac{4^n}{\sqrt{n}})$ (Catalan number).
- **Space Complexity:** $O(n)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backtrack(n, 0, 0, "", res);
        return res;
    }

private:
    void backtrack(int n, int open, int close, string current, vector<string>& res) {
        if (current.length() == n * 2) {
            res.push_back(current);
            return;
        }
        
        if (open < n) {
            backtrack(n, open + 1, close, current + "(", res);
        }
        
        if (close < open) {
            backtrack(n, open, close + 1, current + ")", res);
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def generateParenthesis(self, n: int) -> List[str]:
        res = []
        self._backtrack(n, 0, 0, [], res)
        return res

    def _backtrack(self, n, open_count, close_count, current, res):
        if len(current) == n * 2:
            res.append("".join(current))
            return
        
        if open_count < n:
            current.append("(")
            self._backtrack(n, open_count + 1, close_count, current, res)
            current.pop()
            
        if close_count < open_count:
            current.append(")")
            self._backtrack(n, open_count, close_count + 1, current, res)
            current.pop()
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> res = new ArrayList<>();
        backtrack(n, 0, 0, new StringBuilder(), res);
        return res;
    }
    
    private void backtrack(int n, int open, int close, StringBuilder current, List<String> res) {
        if (current.length() == n * 2) {
            res.add(current.toString());
            return;
        }
        
        if (open < n) {
            current.append('(');
            backtrack(n, open + 1, close, current, res);
            current.deleteCharAt(current.length() - 1);
        }
        
        if (close < open) {
            current.append(')');
            backtrack(n, open, close + 1, current, res);
            current.deleteCharAt(current.length() - 1);
        }
    }
}
```

## 🌍 Real-World Analogy
### **Nested Code Blocks:**
Writing code in a C-like language. You can open a new block `{` whenever you want (up to a limit), but you can only close a block `}` if there is one currently open. You can't have a dangling `}`.

## 🎯 Summary
✅ **Balance Check:** `close < open` ensures we never add an invalid closing char.
✅ **Constraint:** `open < n` ensures we don't exceed the pairs.
