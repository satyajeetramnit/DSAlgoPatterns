# Wiggle Subsequence

## 🧩 Problem Statement
A **wiggle sequence** is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.

- For example, `[1, 7, 4, 9, 2, 5]` is a wiggle sequence because the differences `(6, -3, 5, -7, 3)` alternate positive and negative.
- In contrast, `[1, 4, 7, 2, 5]` and `[1, 7, 4, 5, 5]` are not wiggle sequences.

Given an integer array `nums`, return the length of the longest **wiggle subsequence** of `nums`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,7,4,9,2,5]
```
#### Output:
```plaintext
6
```
#### Explanation:
The entire sequence is a wiggle sequence.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1,17,5,10,13,15,10,5,16,8]
```
#### Output:
```plaintext
7
```
#### Explanation:
There are several subsequences that achieve this length. One is `[1, 17, 10, 13, 10, 16, 8]`.

## 🔍 Approaches

### 1. Greedy (Peaks and Valleys) ($O(N)$)
- **Concept:** We want to count the number of "turning points" (peaks and valleys) in the sequence.
- **Key Insight:** If we have a sequence of increasing numbers `[1, 2, 3, 4]`, the longest wiggle subsequence we can pick is just length 2 (start and end). We can't use the middle numbers.
- **Algorithm:**
  - Maintain two counters: `up` and `down`.
  - `up`: The length of the longest wiggle subsequence ending with an **upward** move (positive difference).
  - `down`: The length of the longest wiggle subsequence ending with a **downward** move (negative difference).
  - Iterate through `nums` from index 1:
    - If `nums[i] > nums[i-1]` (Increasing): "Up" state is now `down + 1`. (We extend a valley with a peak).
    - If `nums[i] < nums[i-1]` (Decreasing): "Down" state is now `up + 1`. (We extend a peak with a valley).
    - If `nums[i] == nums[i-1]`: Do nothing (duplicates don't help wiggle).
  - Return `max(up, down)`.

This logic implicitly skips over monotonic segments and only counts the extremes.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Single pass.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.empty()) return 0;
        int up = 1;
        int down = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > nums[i-1]) {
                up = down + 1;
            } else if (nums[i] < nums[i-1]) {
                down = up + 1;
            }
        }
        return max(up, down);
    }
};
```

### Python
```python
from typing import List

class Solution:
    def wiggleMaxLength(self, nums: List[int]) -> int:
        if not nums:
            return 0
            
        up = 1
        down = 1
        
        for i in range(1, len(nums)):
            if nums[i] > nums[i-1]:
                up = down + 1
            elif nums[i] < nums[i-1]:
                down = up + 1
                
        return max(up, down)
```

### Java
```java
class Solution {
    public int wiggleMaxLength(int[] nums) {
        if (nums.length == 0) return 0;
        
        int up = 1;
        int down = 1;
        
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] > nums[i-1]) {
                up = down + 1;
            } else if (nums[i] < nums[i-1]) {
                down = up + 1;
            }
        }
        return Math.max(up, down);
    }
}
```

## 🌍 Real-World Analogy
### **Stock Market Trends:**
Imagine tracking a stock price. You want to buy at every local bottom and sell at every local top to maximize transactions. A steady rise `10 -> 20 -> 30` only counts as one "Buy -> Sell". You need volatility (`10 -> 20 -> 15 -> 25`) to increase your action count.

## 🎯 Summary
✅ **Turning Points:** The problem reduces to counting how many times the slope flips direction.
