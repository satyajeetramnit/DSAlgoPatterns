# Set Matrix Zeroes

## 🧩 Problem Statement
Given an `m x n` integer matrix, if an element is `0`, set its entire row and column to `0`.

You must do it **in-place**.

### 🔹 Example 1:
#### Input:
```plaintext
matrix = [[1,1,1],[1,0,1],[1,1,1]]
```
#### Output:
```plaintext
[[1,0,1],[0,0,0],[1,0,1]]
```

### 🔹 Example 2:
#### Input:
```plaintext
matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
```
#### Output:
```plaintext
[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```

## 🔍 Approaches

### 1. Additional Memory ($O(M + N)$)
- **Concept:** Use two sets (or arrays) to store indices of rows and columns that need to be zeroed.
- **Steps:**
  1. Iterate matrix, record `0` locations.
  2. Iterate matrix again, set cell to `0` if `row` or `col` is in the set.

### 2. Constant Space ($O(1)$)
- **Concept:** Use the first row and first column of the matrix itself as markers.
- **Markers:**
  - `matrix[i][0] = 0` means row `i` should be zeroed.
  - `matrix[0][j] = 0` means column `j` should be zeroed.
- **Overlap:** The cell `matrix[0][0]` overlaps. We need a separate variable `col0` to track if the first column itself needs to be zeroed. (The logic for the first row is handled by `matrix[0][0]`).
- **Steps:**
  1. Iterate matrix. If `matrix[i][j] == 0`:
     - If `j == 0`, set `col0 = 0` (or boolean flag).
     - Else, set `matrix[i][0] = 0` and `matrix[0][j] = 0`.
  2. Iterate from bottom-right up to `(1, 1)`. If marker row or col is 0, set cell to 0.
  3. Handle first row using `matrix[0][0]`.
  4. Handle first column using `col0`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \times N)$ (two passes).
- **Space Complexity:** $O(1)$ (using matrix as storage).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        bool col0 = false;
        
        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0) col0 = true;
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 1; --j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
            if (col0) matrix[i][0] = 0;
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        m = len(matrix)
        n = len(matrix[0])
        col0 = False
        
        for i in range(m):
            if matrix[i][0] == 0:
                col0 = True
            for j in range(1, n):
                if matrix[i][j] == 0:
                    matrix[i][0] = 0
                    matrix[0][j] = 0
                    
        for i in range(m - 1, -1, -1):
            for j in range(n - 1, 0, -1):
                if matrix[i][0] == 0 or matrix[0][j] == 0:
                    matrix[i][j] = 0
            if col0:
                matrix[i][0] = 0
```

### Java
```java
import java.util.Arrays;

class Solution {
    public void setZeroes(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        boolean col0 = false;
        
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) col0 = true;
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 1; j--) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
            if (col0) matrix[i][0] = 0;
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] matrix = {{1,1,1},{1,0,1},{1,1,1}};
        sol.setZeroes(matrix);
        
        for (int[] row : matrix) {
            System.out.println(Arrays.toString(row));
        }
    }
}
```

## 🌍 Real-World Analogy
### **Viral Infection:**
If a person (cell) is infected (0), everyone in their aisle (row) and column gets infected. Instead of infecting immediately (which would cascade uncontrollably), we mark the start of the aisle and column with a flag, and apply the infection protocol at the end of the day.

## 🎯 Summary
✅ **Space Optimization:** Using the data structure itself (`matrix[0][j]`, `matrix[i][0]`) to store state eliminates $O(N)$ space.
