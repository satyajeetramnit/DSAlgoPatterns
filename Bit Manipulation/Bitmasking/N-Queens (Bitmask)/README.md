# N-Queens (Bitmask)

## 🧩 Problem Statement
The **n-queens** puzzle is the problem of placing `n` queens on an `n x n` chessboard such that no two queens attack each other.

Given an integer `n`, return the total number of distinct solutions to the n-queens puzzle.

This is an optimized version of the classic backtracking problem using **Bitmasking**.

### 🔹 Example 1:
#### Input:
```plaintext
n = 4
```
#### Output:
```plaintext
2
```
**Explanation:** 
There are two distinct solutions:
1. `[[0, 1, 0, 0], [0, 0, 0, 1], [1, 0, 0, 0], [0, 0, 1, 0]]`
2. `[[0, 0, 1, 0], [1, 0, 0, 0], [0, 0, 0, 1], [0, 1, 0, 0]]`

### 🔹 Example 2:
#### Input:
```plaintext
n = 1
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Backtracking with Bitmasking
- **Concept:** Instead of using arrays or sets to track occupied columns and diagonals, we can use integers (bitmasks).
- **State:**
  - `cols`: Bitmask where the $i$-th bit is set if column $i$ is occupied.
  - `diag1`: Bitmask for "major" diagonals (top-left to bottom-right). Computed as `row - col`.
  - `diag2`: Bitmask for "minor" diagonals (top-right to bottom-left). Computed as `row + col`.
- **Optimization:**
  - When moving to the next row, the diagonal constraints shift.
  - `diag1` shifts left (`<< 1`) because a conflict at `(r, c)` moves to `(r+1, c-1)`.
  - `diag2` shifts right (`>> 1`) because a conflict at `(r, c)` moves to `(r+1, c+1)`. (Or vice versa depending on implementation).
- **Algorithm:**
  1. `availablePositions = ~(cols | diag1 | diag2) & ((1 << n) - 1)`
  2. Iterate through bits in `availablePositions`. Beating the lowest set bit (`p = P & -P`) allows $O(1)$ extraction of the next position.
  3. Recurse: `solve(row + 1, cols | p, (diag1 | p) << 1, (diag2 | p) >> 1)`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N!)$. The bitwise operations speed up the constant factor significantly compared to array-based tracking.
- **Space Complexity:** $O(N)$ for recursion stack.

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>

using namespace std;

class Solution {
public:
    int totalNQueens(int n) {
        return solve(0, 0, 0, 0, n);
    }

private:
    int solve(int row, int cols, int diag1, int diag2, int n) {
        if (row == n) return 1;
        
        int count = 0;
        int availablePositions = ((1 << n) - 1) & ~(cols | diag1 | diag2);
        
        while (availablePositions) {
            int position = availablePositions & -availablePositions; // Get lowest set bit
            availablePositions &= availablePositions - 1; // Remove lowest set bit
            
            count += solve(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1, n);
        }
        
        return count;
    }
};
```

### Python
```python
class Solution:
    def totalNQueens(self, n: int) -> int:
        self.count = 0
        self.solve(0, 0, 0, 0, n)
        return self.count

    def solve(self, row, cols, diag1, diag2, n):
        if row == n:
            self.count += 1
            return
        
        available_positions = ((1 << n) - 1) & ~(cols | diag1 | diag2)
        
        while available_positions:
            position = available_positions & -available_positions
            available_positions &= available_positions - 1
            
            self.solve(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1, n)
```

### Java
```java
class Solution {
    private int count = 0;

    public int totalNQueens(int n) {
        count = 0;
        solve(0, 0, 0, 0, n);
        return count;
    }

    private void solve(int row, int cols, int diag1, int diag2, int n) {
        if (row == n) {
            count++;
            return;
        }

        int availablePositions = ((1 << n) - 1) & ~(cols | diag1 | diag2);

        while (availablePositions != 0) {
            int position = availablePositions & -availablePositions;
            availablePositions &= availablePositions - 1;
            
            solve(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1, n);
        }
    }
}
```

## 🌍 Real-World Analogy
### **Laser Grid Security:**
Placing sensors on a grid such that no two sensors are in the same row, column, or diagonal line of sight. Using bitmasks is like having a control panel where lit LEDs show blocked paths almost instantly.

## 🎯 Summary
✅ **Bitmask State:** Efficiently represent "occupied" columns and diagonals using single integers.
✅ **Constraint Propagation:** Shifting masks simulates `row+1` movement perfectly.
