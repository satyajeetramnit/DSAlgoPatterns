# Range Sum Query 2D - Immutable

## 🧩 Problem Statement
Given a 2D matrix `matrix`, handle multiple queries of the following type:
- Calculate the **sum** of the elements of `matrix` inside the rectangle defined by its **upper left corner** `(row1, col1)` and **lower right corner** `(row2, col2)`.

Implement the `NumMatrix` class:
- `NumMatrix(int[][] matrix)` Initializes the object with the integer matrix `matrix`.
- `int sumRegion(int row1, int col1, int row2, int col2)` Returns the sum of the elements of `matrix` inside the rectangle defined by its upper left corner `(row1, col1)` and lower right corner `(row2, col2)`.

### 🔹 Example 1:
#### Input:
```plaintext
["NumMatrix", "sumRegion", "sumRegion", "sumRegion"]
[[[[3, 0, 1, 4, 2], [5, 6, 3, 2, 1], [1, 2, 0, 1, 5], [4, 1, 0, 1, 7], [1, 0, 3, 0, 5]]], [2, 1, 4, 3], [1, 1, 2, 2], [1, 2, 2, 4]]
```
#### Output:
```plaintext
[null, 8, 11, 12]
```
#### Explanation:
- `sumRegion(2, 1, 4, 3)` (Red rectangle) = 8
- `sumRegion(1, 1, 2, 2)` (Green rectangle) = 11
- `sumRegion(1, 2, 2, 4)` (Blue rectangle) = 12

## 🔍 Approaches

### 1. 2D Prefix Sum (Dynamic Programming)
A naive $O(m \cdot n)$ per query is too slow if we have many queries. We want $O(1)$ per query.
We precompute a sum table (DP table).

### ✨ Intuition
- Let `dp[i][j]` be the sum of the rectangle from `(0,0)` to `(i,j)`.
- **Inclusion-Exclusion Principle:**
  ![2D Prefix Sum Intuition](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d5/Inclusion-exclusion.svg/220px-Inclusion-exclusion.svg.png)
  (Conceptually similar to sets)
- `Sum(ABCD) = Sum(OD) - Sum(OB) - Sum(OC) + Sum(OA)`
  (Where O is origin, D is bottom-right, A is top-left corner of interest).

### 🔥 Algorithm Steps
1. **Pre-computation:**
   `dp[i+1][j+1] = matrix[i][j] + dp[i][j+1] + dp[i+1][j] - dp[i][j]`
   (Current cell + left sum + top sum - top-left overlap).
2. **Query:**
   `ans = dp[r2+1][c2+1] - dp[r1][c2+1] - dp[r2+1][c1] + dp[r1][c1]`

## ⏳ Time & Space Complexity
- **Time Complexity:** 
  - Initialization: $O(m \cdot n)$.
  - Query: $O(1)$.
- **Space Complexity:** $O(m \cdot n)$ for the DP table.

## 🚀 Code Implementations

### C++
```cpp
class NumMatrix {
    vector<vector<int>> dp;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        dp.resize(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i + 1][j + 1] = matrix[i][j] + dp[i][j + 1] + dp[i + 1][j] - dp[i][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1] - dp[row2 + 1][col1] + dp[row1][col1];
    }
};
```

### Python
```python
class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        m, n = len(matrix), len(matrix[0])
        self.dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(m):
            for j in range(n):
                self.dp[i + 1][j + 1] = matrix[i][j] + self.dp[i][j + 1] + self.dp[i + 1][j] - self.dp[i][j]

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return self.dp[row2 + 1][col2 + 1] - self.dp[row1][col2 + 1] - self.dp[row2 + 1][col1] + self.dp[row1][col1]
```

### Java
```java
class NumMatrix {
    private int[][] dp;

    public NumMatrix(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        dp = new int[m + 1][n + 1];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i + 1][j + 1] = matrix[i][j] + dp[i][j + 1] + dp[i + 1][j] - dp[i][j];
            }
        }
    }
    
    public int sumRegion(int row1, int col1, int row2, int col2) {
        return dp[row2 + 1][col2 + 1] - dp[row1][col2 + 1] - dp[row2 + 1][col1] + dp[row1][col1];
    }
}
```

## 🌍 Real-World Analogy
### **Farm Land Yield:**
Imagine a large farm divided into a grid of plots. You want to quickly calculate the total crop yield for any rectangular section of the farm (e.g., "The South-West sector").
- Instead of summing up every plot each time (slow), you maintain a map where each point tells you the "total yield from the top-left corner to here".
- Using this "Integral Map", you can calculate any rectangular sector's yield with just 4 lookups subtraction, regardless of the sector's size.

### **Integral Image (Computer Vision):**
In image processing, to calculate the average brightness of a rectangular area quickly (e.g., for face detection like Haar cascades), we use an "Integral Image" which is exactly this 2D prefix sum table. It allows millions of rectangular sum checks per second.

## 🎯 Summary
✅ **O(1) Queries:** Extremely fast after init.
✅ **Immutable:** Works because the matrix doesn't change.
✅ **Inclusion-Exclusion:** The core mathematical principle.
