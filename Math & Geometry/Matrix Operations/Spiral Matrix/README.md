# Spiral Matrix

## 🧩 Problem Statement
Given an `m x n` `matrix`, return all elements of the `matrix` in **spiral order**.

### 🔹 Example 1:
#### Input:
```plaintext
matrix = [[1,2,3],[4,5,6],[7,8,9]]
```
#### Output:
```plaintext
[1,2,3,6,9,8,7,4,5]
```

### 🔹 Example 2:
#### Input:
```plaintext
matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
```
#### Output:
```plaintext
[1,2,3,4,8,12,11,10,9,5,6,7]
```

## 🔍 Approaches

### 1. Simulation with Boundary Shrinking ($O(M \times N)$)
- **Concept:** Maintain 4 boundaries: `top`, `bottom`, `left`, `right`.
- **Steps:**
  1. Move **Left to Right**: `matrix[top][i]` for `i` from `left` to `right`. Increment `top`.
  2. Move **Top to Bottom**: `matrix[i][right]` for `i` from `top` to `bottom`. Decrement `right`.
  3. Move **Right to Left**: `matrix[bottom][i]` for `i` from `right` to `left`. Decrement `bottom`.
  4. Move **Bottom to Top**: `matrix[i][left]` for `i` from `bottom` to `top`. Increment `left`.
- **Condition:** Repeat while `top <= bottom` and `left <= right`.
- **Check:** Need careful checks inside the loop (e.g., if `top > bottom` after step 1, don't do step 3).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(M \times N)$ (visit each cell once).
- **Space Complexity:** $O(1)$ (excluding output array).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if (matrix.empty()) return res;
        
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        
        while (top <= bottom && left <= right) {
            // Left to Right
            for (int i = left; i <= right; ++i) res.push_back(matrix[top][i]);
            top++;
            
            // Top to Bottom
            for (int i = top; i <= bottom; ++i) res.push_back(matrix[i][right]);
            right--;
            
            // Check
            if (top <= bottom) {
                // Right to Left
                for (int i = right; i >= left; --i) res.push_back(matrix[bottom][i]);
                bottom--;
            }
            
            if (left <= right) {
                // Bottom to Top
                for (int i = bottom; i >= top; --i) res.push_back(matrix[i][left]);
                left++;
            }
        }
        
        return res;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        res = []
        if not matrix: return res
        
        top, bottom = 0, len(matrix) - 1
        left, right = 0, len(matrix[0]) - 1
        
        while top <= bottom and left <= right:
            # Left to Right
            for i in range(left, right + 1):
                res.append(matrix[top][i])
            top += 1
            
            # Top to Bottom
            for i in range(top, bottom + 1):
                res.append(matrix[i][right])
            right -= 1
            
            if top <= bottom:
                # Right to Left
                for i in range(right, left - 1, -1):
                    res.append(matrix[bottom][i])
                bottom -= 1
            
            if left <= right:
                # Bottom to Top
                for i in range(bottom, top - 1, -1):
                    res.append(matrix[i][left])
                left += 1
                
        return res
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<Integer> spiralOrder(int[][] matrix) {
        List<Integer> res = new ArrayList<>();
        if (matrix == null || matrix.length == 0) return res;
        
        int top = 0, bottom = matrix.length - 1;
        int left = 0, right = matrix[0].length - 1;
        
        while (top <= bottom && left <= right) {
            // Left to Right
            for (int i = left; i <= right; i++) res.add(matrix[top][i]);
            top++;
            
            // Top to Bottom
            for (int i = top; i <= bottom; i++) res.add(matrix[i][right]);
            right--;
            
            if (top <= bottom) {
                // Right to Left
                for (int i = right; i >= left; i--) res.add(matrix[bottom][i]);
                bottom--;
            }
            
            if (left <= right) {
                // Bottom to Top
                for (int i = bottom; i >= top; i--) res.add(matrix[i][left]);
                left++;
            }
        }
        
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Peeling an Onion:**
You peel the outer layer (perimeter), then you are left with a smaller onion (inner sub-matrix), and you repeat the process until nothing is left.

## 🎯 Summary
✅ **Simulation:** Simply follow the rules.
✅ **Edge Cases:** Rectangular matrices (1 row or 1 col) need the `if` checks inside the loop.
