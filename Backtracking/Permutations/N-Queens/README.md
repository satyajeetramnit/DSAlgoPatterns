# N-Queens

## 🧩 Problem Statement
The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return all distinct solutions to the **n-queens puzzle**. You may return the answer in **any order**.

Each solution contains a distinct board configuration of the n-queens' placement, where `'Q'` and `'.'` both indicate a queen and an empty space, respectively.

### 🔹 Example 1:
#### Input:
```plaintext
n = 4
```
#### Output:
```plaintext
[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
```
#### Explanation:
There exist two distinct solutions to the 4-queens puzzle as shown above.

### 🔹 Example 2:
#### Input:
```plaintext
n = 1
```
#### Output:
```plaintext
[["Q"]]
```

## 🔍 Approaches

### 1. Backtracking with Constraint Tracking
We place queens row by row (from row `0` to `n-1`).
In each row, we try to place a queen in every column `col`.
A position `(row, col)` is valid if:
1.  No other queen is in the same column `col`.
2.  No other queen is on the main diagonal (top-left to bottom-right).
3.  No other queen is on the anti-diagonal (top-right to bottom-left).

#### 🔥 Optimization (O(1) Validation):
Instead of scanning the board to check validity ($O(N)$), we can track used attacks using sets or boolean arrays:
- **Columns**: `cols` set stores used column indices.
- **Positive Diagonals (Anti-diagonal)**: properties on `row + col` are constant. store `row + col` in `posDiag`.
- **Negative Diagonals (Main diagonal)**: properties on `row - col` are constant. store `row - col` in `negDiag`.

#### Algorithm Steps:
1.  Initialize empty sets/arrays for `cols`, `posDiag`, `negDiag`.
2.  `backtrack(row)`:
    -   Base Case: If `row == n`, we found a solution. Construct the board from the current state and add to results.
    -   Iterate `col` from `0` to `n-1`:
        -   If `col` in `cols` OR `(row+col)` in `posDiag` OR `(row-col)` in `negDiag`: Continue (Invalid).
        -   **Place Queen**: Add `col`, `row+col`, `row-col` to sets. Record position.
        -   **Recurse**: `backtrack(row + 1)`.
        -   **Remove Queen (Backtrack)**: Remove `col`, `row+col`, `row-col` from sets.

### 🏛️ Visual Logic: Placing 4 Queens


#### Step 1: Row 0
- **Action**: Place Q at `(0, 0)`.
- **Constraint Updates**:
  - Col 0 blocked.
  - Diag (0+0=0) blocked.
  - Anti-Diag (0-0=0) blocked.
- **Board**:
  ```text
  Q . . .
  . x . .  <-- (1,1) blocked
  . . x .  <-- (2,2) blocked
  . . . x  <-- (3,3) blocked
  ```

<!-- slide -->

#### Step 2: Row 1
- **Try (1, 0)**: Blocked by Col 0.
- **Try (1, 1)**: Blocked by Diag from (0,0).
- **Try (1, 2)**: **Valid**. Place Q.
- **Board**:
  ```text
  Q . . .
  . . Q .
  . x x x  <-- Row 2 heavily blocked
  ```

<!-- slide -->

#### Step 3: Row 2 (Backtrack Trigger)
- **Try (2, 0)**: Blocked (Col 0).
- **Try (2, 1)**: Blocked (Diag from 1,2).
- **Try (2, 2)**: Blocked (Diag from 0,0).
- **Try (2, 3)**: Blocked (Diag from 1,2).
- **Result**: Cannot place in Row 2. **Backtrack** to Row 1.
- **Action**: Remove Q from (1, 2). Try next col (1, 3).

<!-- slide -->

#### Step 4: Row 1 (Retry)
- **Try (1, 3)**: **Valid**. Place Q.
- **Recurse** to Row 2...
- **Result**: Eventually finds valid config: `(0,1), (1,3), (2,0), (3,2)`.


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N!)$. We have N choices for first row, N-1 for second...
- **Space Complexity:** $O(N)$ for recursion stack and sets.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> posDiag(2 * n, false); // row + col
        vector<bool> negDiag(2 * n, false); // row - col + n
        
        backtrack(0, n, board, cols, posDiag, negDiag, res);
        return res;
    }

private:
    void backtrack(int row, int n, vector<string>& board, 
                   vector<bool>& cols, vector<bool>& posDiag, vector<bool>& negDiag, 
                   vector<vector<string>>& res) {
        if (row == n) {
            res.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; ++col) {
            if (cols[col] || posDiag[row + col] || negDiag[row - col + n]) {
                continue;
            }
            
            cols[col] = true;
            posDiag[row + col] = true;
            negDiag[row - col + n] = true;
            board[row][col] = 'Q';
            
            backtrack(row + 1, n, board, cols, posDiag, negDiag, res);
            
            board[row][col] = '.';
            cols[col] = false;
            posDiag[row + col] = false;
            negDiag[row - col + n] = false;
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        res = []
        col_set = set()
        pos_diag = set() # r + c
        neg_diag = set() # r - c
        board = [['.'] * n for _ in range(n)]
        
        def backtrack(r):
            if r == n:
                copy = ["".join(row) for row in board]
                res.append(copy)
                return
            
            for c in range(n):
                if c in col_set or (r + c) in pos_diag or (r - c) in neg_diag:
                    continue
                
                col_set.add(c)
                pos_diag.add(r + c)
                neg_diag.add(r - c)
                board[r][c] = 'Q'
                
                backtrack(r + 1)
                
                col_set.remove(c)
                pos_diag.remove(r + c)
                neg_diag.remove(r - c)
                board[r][c] = '.'
                
        backtrack(0)
        return res
```

### Java
```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    public List<List<String>> solveNQueens(int n) {
        List<List<String>> res = new ArrayList<>();
        char[][] board = new char[n][n];
        for (char[] row : board) Arrays.fill(row, '.');
        
        boolean[] cols = new boolean[n];
        boolean[] posDiag = new boolean[2 * n]; // r + c
        boolean[] negDiag = new boolean[2 * n]; // r - c + n
        
        backtrack(0, n, board, cols, posDiag, negDiag, res);
        return res;
    }
    
    private void backtrack(int row, int n, char[][] board, 
                           boolean[] cols, boolean[] posDiag, boolean[] negDiag, 
                           List<List<String>> res) {
        if (row == n) {
            List<String> copy = new ArrayList<>();
            for (char[] r : board) copy.add(new String(r));
            res.add(copy);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            if (cols[col] || posDiag[row + col] || negDiag[row - col + n]) {
                continue;
            }
            
            cols[col] = true;
            posDiag[row + col] = true;
            negDiag[row - col + n] = true;
            board[row][col] = 'Q';
            
            backtrack(row + 1, n, board, cols, posDiag, negDiag, res);
            
            board[row][col] = '.';
            cols[col] = false;
            posDiag[row + col] = false;
            negDiag[row - col + n] = false;
        }
    }
}
```

## 🌍 Real-World Analogy
### **Event Planning:**
You have `N` VIPs to seat at `N` banquet tables. No two VIPs can be at the same table (row) or same seat number (col). Additionally, because of their complex rivalries, they cannot even be "diagonally" visible to each other across the room.
You try seating the first VIP in the first row. Then the second VIP in the second row, checking "Is this seat visible to VIP 1?". If yes, move to next seat. If you run out of seats, ask VIP 1 to move.

## 🎯 Summary
✅ **Optimization:** Use Sets/Arrays to check attacks in O(1).
✅ **Backtracking:** Place row by row to prune the search space significantly compared to cell by cell.
