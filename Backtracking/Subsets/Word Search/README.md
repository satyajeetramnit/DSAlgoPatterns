# Word Search

## 🧩 Problem Statement
Given an `m x n` grid of characters `board` and a string `word`, return `true` if `word` exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

### 🔹 Example 1:
#### Input:
```plaintext
board = [
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
], word = "ABCCED"
```
#### Output:
```plaintext
true
```

### 🔹 Example 2:
#### Input:
```plaintext
board = [
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
], word = "SEE"
```
#### Output:
```plaintext
true
```

## 🔍 Approaches

### 1. Backtracking (DFS)
We need to find if there is *any* path in the grid that spells out the word.
- Iterate through every cell `(r, c)` in the grid.
- If `board[r][c]` matches the first letter of `word`, start a DFS traversal from there.
- **DFS(r, c, index)**:
  - **Base Case:** If `index == word.length()`, we found the word. Return `true`.
  - **Boundary Check:** If `r, c` out of bounds or `board[r][c]` doesn't match `word[index]`, return `false`.
  - **Mark Visited:** Temporarily change `board[r][c]` to a special char (e.g., `#`) to avoid cycles.
  - **Recurse:** Check all 4 directions: `(r+1, c), (r-1, c), (r, c+1), (r, c-1)`.
  - **Backtrack:** Restore `board[r][c]` to original char.
  - Return result of recursion.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \cdot N \cdot 3^L)$, where $L$ is length of word. We explore 3 directions (excluding where we came from) for each step in `word`.
- **Space Complexity:** $O(L)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == word[0] && dfs(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, int i, int j, const string& word, int index) {
        if (index == word.length()) return true;
        
        if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() || board[i][j] != word[index]) {
            return false;
        }
        
        char temp = board[i][j];
        board[i][j] = '#'; // Mark visited
        
        bool found = dfs(board, i + 1, j, word, index + 1) ||
                     dfs(board, i - 1, j, word, index + 1) ||
                     dfs(board, i, j + 1, word, index + 1) ||
                     dfs(board, i, j - 1, word, index + 1);
        
        board[i][j] = temp; // Backtrack
        return found;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def exist(self, board: List[List[str]], word: str) -> bool:
        rows, cols = len(board), len(board[0])
        
        def dfs(r, c, index):
            if index == len(word):
                return True
            
            if (r < 0 or c < 0 or r >= rows or c >= cols or 
                board[r][c] != word[index]):
                return False
            
            temp = board[r][c]
            board[r][c] = '#' # Mark visited
            
            found = (dfs(r + 1, c, index + 1) or
                     dfs(r - 1, c, index + 1) or
                     dfs(r, c + 1, index + 1) or
                     dfs(r, c - 1, index + 1))
            
            board[r][c] = temp # Backtrack
            return found

        for i in range(rows):
            for j in range(cols):
                if board[i][j] == word[0] and dfs(i, j, 0):
                    return True
        return False
```

### Java
```java
class Solution {
    public boolean exist(char[][] board, String word) {
        int m = board.length;
        int n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == word.charAt(0) && dfs(board, i, j, word, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
    private boolean dfs(char[][] board, int i, int j, String word, int index) {
        if (index == word.length()) return true;
        
        if (i < 0 || i >= board.length || j < 0 || j >= board[0].length || board[i][j] != word.charAt(index)) {
            return false;
        }
        
        char temp = board[i][j];
        board[i][j] = '#'; // Mark visited
        
        boolean found = dfs(board, i + 1, j, word, index + 1) ||
                        dfs(board, i - 1, j, word, index + 1) ||
                        dfs(board, i, j + 1, word, index + 1) ||
                        dfs(board, i, j - 1, word, index + 1);
        
        board[i][j] = temp; // Backtrack
        return found;
    }
}
```

## 🌍 Real-World Analogy
### **Boggle Game:**
You are searching for a word in a grid of letter dice. You can move to any neighbor, but you can't reuse a die you've already touched in the current word chain.

## 🎯 Summary
✅ **DFS:** Explore path depth-first.
✅ **Backtracking:** Unmark visited cells to allow other paths to use them.
