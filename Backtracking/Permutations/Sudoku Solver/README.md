# Sudoku Solver

## 🧩 Problem Statement
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:
1. Each of the digits `1-9` must occur exactly once in each row.
2. Each of the digits `1-9` must occur exactly once in each column.
3. Each of the digits `1-9` must occur exactly once in each of the 9 `3x3` sub-boxes of the grid.

The `'.'` character indicates empty cells.

### 🔹 Example 1:
#### Input:
```plaintext
board = [
 ["5","3",".",".","7",".",".",".","."],
 ["6",".",".","1","9","5",".",".","."],
 [".","9","8",".",".",".",".","6","."],
 ["8",".",".",".","6",".",".",".","3"],
 ["4",".",".","8",".","3",".",".","1"],
 ["7",".",".",".","2",".",".",".","6"],
 [".","6",".",".",".",".","2","8","."],
 [".",".",".","4","1","9",".",".","5"],
 [".",".",".",".","8",".",".","7","9"]
]
```
#### Output:
```plaintext
board = [
 ["5","3","4","6","7","8","9","1","2"],
 ["6","7","2","1","9","5","3","4","8"],
 ["1","9","8","3","4","2","5","6","7"],
 ["8","5","9","7","6","1","4","2","3"],
 ["4","2","6","8","5","3","7","9","1"],
 ["7","1","3","9","2","4","8","5","6"],
 ["9","6","1","5","3","7","2","8","4"],
 ["2","8","7","4","1","9","6","3","5"],
 ["3","4","5","2","8","6","1","7","9"]
]
```

## 🔍 Approaches

### 1. Backtracking
We fill empty cells one by one.
For the first empty cell, we try placing digits `1` through `9`.
- **Check Validity:** If placing multiple `k` doesn't violate Sudoku rules (Row, Col, Box), we place it and move to the next empty cell.
- **Recurse:** If the next steps eventually lead to a solution (return true), we are done.
- **Backtrack:** If we get stuck (no valid digit for a future cell), we reset the current cell to `.` and try the next digit `k+1`.

#### Helper Function `isValid(board, row, col, char c)`
- Check `board[row][i] == c` for all columns.
- Check `board[i][col] == c` for all rows.
- Check `board[3*(row/3) + i/3][3*(col/3) + i%3] == c` for the $3 \times 3$ block.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(9^M)$, where M is the number of empty cells. In worst case (empty board), it is huge, but constraints and pruning make it feasible.
- **Space Complexity:** $O(M)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
    
private:
    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; ++c) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) return true;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; ++i) {
            // Check row
            if (board[row][i] == c) return false;
            // Check col
            if (board[i][col] == c) return false;
            // Check 3x3 box
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        self.solve(board)

    def solve(self, board):
        for i in range(len(board)):
            for j in range(len(board[0])):
                if board[i][j] == '.':
                    for c in "123456789":
                        if self.isValid(board, i, j, c):
                            board[i][j] = c
                            if self.solve(board):
                                return True
                            board[i][j] = '.'
                    return False
        return True

    def isValid(self, board, row, col, c):
        for i in range(9):
            if board[row][i] == c: return False
            if board[i][col] == c: return False
            if board[3 * (row // 3) + i // 3][3 * (col // 3) + i % 3] == c: return False
        return True
```

### Java
```java
class Solution {
    public void solveSudoku(char[][] board) {
        solve(board);
    }
    
    private boolean solve(char[][] board) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board[0].length; j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;
                            if (solve(board)) return true;
                            board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    private boolean isValid(char[][] board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == c) return false;
            if (board[i][col] == c) return false;
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c) return false;
        }
        return true;
    }
}
```

## 🌍 Real-World Analogy
### **Filling a Schedule:**
You have a 9-day schedule with 9 time slots. Certain tasks must happen once per row-category, once per column-category, and once per team-block. You pencil in a task. If it creates a conflict later, you erase it and try a different task time.

## 🎯 Summary
✅ **In-Place Modification:** The board is updated directly.
✅ **Backtracking:** Standard try-check-undo pattern.
