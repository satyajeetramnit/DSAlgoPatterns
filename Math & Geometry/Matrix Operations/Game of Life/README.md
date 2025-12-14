# Game of Life

## 🧩 Problem Statement
According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."

The board is made up of an `m x n` grid of cells, where each cell has an initial state: **live** (represented by a `1`) or **dead** (represented by a `0`). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules:

1. **Underpopulation:** Any live cell with fewer than two live neighbors dies.
2. **Survival:** Any live cell with two or three live neighbors lives on to the next generation.
3. **Overpopulation:** Any live cell with more than three live neighbors dies.
4. **Reproduction:** Any dead cell with exactly three live neighbors becomes a live cell.

The next state is created by applying the above rules simultaneously to every cell in the current state, where births and deaths occur simultaneously. Given the current state of the `m x n` grid `board`, return the **next state**.

**Constraint:** Solve it **in-place** (or minimizing extra space).

### 🔹 Example 1:
#### Input:
```plaintext
board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
```
#### Output:
```plaintext
[[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
```

## 🔍 Approaches

### 1. Copy Board ($O(M \times N)$ Space)
- Create a copy of the board.
- Iterate original board, check neighbors in copy to update original.
- Simple but uses extra space.

### 2. In-Place with State Encoding ($O(1)$ Space)
- **Problem:** Updating a cell changes the neighbor count for the *next* cell we visit. We need to know the *old* state while updating.
- **Solution:** Use temporary values to encode "Was X, Now Y".
  - `0`: Dead -> Dead
  - `1`: Live -> Live
  - `2`: Live -> Dead (Was 1, Now 0)
  - `3`: Dead -> Live (Was 0, Now 1)
- **Transitions:**
  - If `board[r][c] == 1` (Live):
    - Neighbors < 2 or > 3: `board[r][c] = 2` (Dies).
  - If `board[r][c] == 0` (Dead):
    - Neighbors == 3: `board[r][c] = 3` (Liives).
- **Counting Neighbors:** When checking neighbors, `1` and `2` count as live (since `2` was live). `0` and `3` count as dead.
- **Final Pass:** Convert `2` -> `0`, `3` -> `1`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \times N)$.
- **Space Complexity:** $O(1)$ (in-place modification).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        
        // Directions for 8 neighbors
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int liveNeighbors = 0;
                
                for (int k = 0; k < 8; ++k) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        // Check if neighbor was live (1 or 2)
                        if (board[ni][nj] == 1 || board[ni][nj] == 2) {
                            liveNeighbors++;
                        }
                    }
                }
                
                if (board[i][j] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        board[i][j] = 2; // Live -> Dead
                    }
                } else {
                    if (liveNeighbors == 3) {
                        board[i][j] = 3; // Dead -> Live
                    }
                }
            }
        }
        
        // Finalize
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 2) board[i][j] = 0;
                else if (board[i][j] == 3) board[i][j] = 1;
            }
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def gameOfLife(self, board: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        m, n = len(board), len(board[0])
        neighbors = [(-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1)]
        
        for i in range(m):
            for j in range(n):
                live_neighbors = 0
                for r, c in neighbors:
                    nr, nc = i + r, j + c
                    if 0 <= nr < m and 0 <= nc < n and abs(board[nr][nc]) == 1:
                        live_neighbors += 1
                
                if board[i][j] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                    board[i][j] = -1 # Live -> Dead
                if board[i][j] == 0 and live_neighbors == 3:
                    board[i][j] = 2 # Dead -> Live
                    
        for i in range(m):
            for j in range(n):
                if board[i][j] > 0:
                    board[i][j] = 1
                else:
                    board[i][j] = 0
```
*Note: Python implementation uses slightly different encoding (-1 for Live->Dead to use abs(), 2 for Dead->Live)*

### Java
```java
import java.util.Arrays;

class Solution {
    public void gameOfLife(int[][] board) {
        int m = board.length;
        int n = board[0].length;
        
        int[] dx = {-1, -1, -1, 0, 0, 1, 1, 1};
        int[] dy = {-1, 0, 1, -1, 1, -1, 0, 1};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int liveNeighbors = 0;
                
                for (int k = 0; k < 8; k++) {
                    int ni = i + dx[k];
                    int nj = j + dy[k];
                    
                    if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                        if (board[ni][nj] == 1 || board[ni][nj] == 2) {
                            liveNeighbors++;
                        }
                    }
                }
                
                if (board[i][j] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        board[i][j] = 2; // Live -> Dead
                    }
                } else {
                    if (liveNeighbors == 3) {
                        board[i][j] = 3; // Dead -> Live
                    }
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 2) board[i][j] = 0;
                else if (board[i][j] == 3) board[i][j] = 1;
            }
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] board = {{0,1,0},{0,0,1},{1,1,1},{0,0,0}};
        sol.gameOfLife(board);
        
        System.out.println("Test Case 1 Output:");
        for (int[] row : board) {
            System.out.println(Arrays.toString(row));
        }
    }
}
```

## 🌍 Real-World Analogy
### **Population Simulation:**
Similar to how populations grow or shrink based on resources (neighbors). Too few resources (underpopulation) -> death. Optimally populated -> Survival. Too many (overpopulation) -> death due to competition.

## 🎯 Summary
✅ **In-Place Encoding:** Critical technique for grid problems where simultaneous updates are required.
