# Rotate Image

## 🧩 Problem Statement
You are given an `n x n` 2D matrix representing an image, rotate the image by **90 degrees (clockwise)**.

You have to rotate the image **in-place**, which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

### 🔹 Example 1:
#### Input:
```plaintext
matrix = [[1,2,3],[4,5,6],[7,8,9]]
```
#### Output:
```plaintext
[[7,4,1],[8,5,2],[9,6,3]]
```

### 🔹 Example 2:
#### Input:
```plaintext
matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
```
#### Output:
```plaintext
[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

## 🔍 Approaches

### 1. Transpose + Reverse ($O(N^2)$)
- **Concept:** Rotating 90 degrees clockwise is equivalent to transposing the matrix and then reversing each row.
- **Steps:**
  1. **Transpose:** Swap `matrix[i][j]` with `matrix[j][i]` (for $i < j$).
  2. **Reverse:** Reverse each row `matrix[i]`. `[1,2,3]` becomes `[3,2,1]`.

### 2. Four-Way Swap ($O(N^2)$)
- **Concept:** Rotate layers one by one. Swap four elements at a time in a cycle.
- **Cycle:**
  - `temp = top_left`
  - `top_left = bottom_left`
  - `bottom_left = bottom_right`
  - `bottom_right = top_right`
  - `top_right = temp`

We will implement **Transpose + Reverse** as it's cleaner to write and remember.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^2)$ (visit each cell twice).
- **Space Complexity:** $O(1)$ (in-place).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        
        // Transpose
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
        
        // Reverse rows
        for (int i = 0; i < n; ++i) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};
```

### Python
```python
from typing import List

class Solution:
    def rotate(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        n = len(matrix)
        
        # Transpose
        for i in range(n):
            for j in range(i, n):
                matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]
        
        # Reverse rows
        for i in range(n):
            matrix[i].reverse()
```

### Java
```java
class Solution {
    public void rotate(int[][] matrix) {
        int n = matrix.length;
        
        // Transpose
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
        }
        
        // Reverse rows
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][n - 1 - j];
                matrix[i][n - 1 - j] = temp;
            }
        }
    }
}
```

## 🌍 Real-World Analogy
### **Physical Photo Rotation:**
If you execute the Transpose step, you are flipping the image across its main diagonal (top-left to bottom-right). The Reverse step then flips it horizontally. The combination results in a 90-degree turn.

## 🎯 Summary
✅ **Transpose + Reverse:** A very common matrix manipulation trick for rotation.
