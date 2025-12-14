# Subset Generation (Bitmasking)

## 🧩 Problem Statement
Given an integer array `nums` of unique elements, return all possible **subsets** (the power set). The solution set must not contain duplicate subsets. Return the solution in any order.

This problem specifically asks to be solved using **Bit Manipulation** (Bitmasking).

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,2,3]
```
#### Output:
```plaintext
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [0]
```
#### Output:
```plaintext
[[],[0]]
```

## 🔍 Approaches

### 1. Bitmasking
- **Concept:** A subset can be represented by a binary mask of length `N`, where the $i$-th bit is `1` if the $i$-th element is included, and `0` otherwise.
- **Total Subsets:** There are $2^N$ possible subsets, corresponding to numbers from `0` to `2^N - 1`.
- **Algorithm:**
  1. Iterate `mask` from `0` to `2^N - 1`.
  2. For each `mask`, verify bits `j` from `0` to `N-1`.
  3. If the $j$-th bit is set (`(mask >> j) & 1`), include `nums[j]` in the current subset.
  4. Add the subset to the result.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot 2^N)$. We generate $2^N$ subsets, and for each, we iterate $N$ bits.
- **Space Complexity:** $O(N \cdot 2^N)$ to store the output.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        int totalSubsets = 1 << n; // 2^n
        vector<vector<int>> res;
        
        for (int mask = 0; mask < totalSubsets; ++mask) {
            vector<int> subset;
            for (int i = 0; i < n; ++i) {
                // Check if i-th bit is set
                if ((mask >> i) & 1) {
                    subset.push_back(nums[i]);
                }
            }
            res.push_back(subset);
        }
        
        return res;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        n = len(nums)
        total_subsets = 1 << n
        res = []
        
        for mask in range(total_subsets):
            subset = []
            for i in range(n):
                # Check if i-th bit is set
                if (mask >> i) & 1:
                    subset.append(nums[i])
            res.append(subset)
            
        return res
```

### Java
```java
import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        int n = nums.length;
        int totalSubsets = 1 << n;
        List<List<Integer>> res = new ArrayList<>();
        
        for (int mask = 0; mask < totalSubsets; mask++) {
            List<Integer> subset = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (((mask >> i) & 1) == 1) {
                    subset.add(nums[i]);
                }
            }
            res.add(subset);
        }
        
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Light Switches:**
Imagine `N` light switches (representing elements). Each unique combination of ON/OFF switches creates a distinct lighting "scene" (subset). Iterating through all binary numbers is like systematically flipping through every possible switch configuration.

## 🎯 Summary
✅ **Binary Correspondence:** Every integer maps uniquely to a subset.
✅ **Iterative vs Recursive:** This is the iterative alternative to the classic backtracking solution.
