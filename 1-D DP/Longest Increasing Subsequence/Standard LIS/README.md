# Longest Increasing Subsequence (LIS)

## 🧩 Problem Statement
Given an integer array `nums`, return the length of the longest strictly increasing subsequence.

A **subsequence** is a sequence that can be derived from an array by deleting some or no elements without changing the order of the remaining elements.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [10,9,2,5,3,7,101,18]
```
#### Output:
```plaintext
4
```
**Explanation:** The longest increasing subsequence is `[2,3,7,101]`, therefore the length is 4.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [0,1,0,3,2,3]
```
#### Output:
```plaintext
4
```
**Explanation:** `[0,1,2,3]`.

## 🔍 Approaches

### 1. Dynamic Programming - $O(N^2)$
Define `dp[i]` as the length of the longest increasing subsequence ending at index `i`.
- Initialize `dp` array of size `N` with 1s (each element is an LIS of length 1).
- For each `i` from `1` to `N-1`:
  - For each `j` from `0` to `i-1`:
    - If `nums[i] > nums[j]`: `dp[i] = max(dp[i], dp[j] + 1)`
- Return `max(dp)`.

### 2. Tail Construction with Binary Search - $O(N \log N)$
We construct an array `tails` (or `sub`) where `tails[i]` stores the smallest tail of all increasing subsequences of length `i+1` found so far.
- Iterate through each number `x` in `nums`.
- If `x` is greater than all tails, append it.
- If `x` can replace an element in `tails` to make it smaller (while maintaining increasing order), do so using Binary Search (`lower_bound`). This extends the potential to form longer subsequences later.
- The length of `tails` is the answer.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N^2)$ for DP, $O(N \log N)$ for Binary Search method.
- **Space Complexity:** $O(N)$ for the DP array or tails array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        vector<int> tails;
        
        for (int num : nums) {
            auto it = lower_bound(tails.begin(), tails.end(), num);
            if (it == tails.end()) {
                tails.push_back(num);
            } else {
                *it = num;
            }
        }
        
        return tails.size();
    }
};
```

### Python
```python
from typing import List
import bisect

class Solution:
    def lengthOfLIS(self, nums: List[int]) -> int:
        tails = []
        for x in nums:
            # Find the first element in tails >= x
            idx = bisect.bisect_left(tails, x)
            if idx < len(tails):
                tails[idx] = x
            else:
                tails.append(x)
        return len(tails)
```

### Java
```java
import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

class Solution {
    public int lengthOfLIS(int[] nums) {
        if (nums.length == 0) return 0;
        
        List<Integer> tails = new ArrayList<>();
        
        for (int num : nums) {
            // Binary search for insertion point
            int idx = Collections.binarySearch(tails, num);
            if (idx < 0) idx = -(idx + 1); // Convert to insertion point
            
            if (idx == tails.size()) {
                tails.add(num);
            } else {
                tails.set(idx, num);
            }
        }
        
        return tails.size();
    }
}
```

## 🌍 Real-World Analogy
### **Stacking Cards:**
Imagine playing patience. You place a card on top of a pile if it's smaller. If it's larger than all tops, you start a new pile to the right. The number of piles represents the LIS length.

## 🎯 Summary
✅ **Patience Sorting:** The binary search approach effectively simulates Patience Sorting.
✅ **Optimization:** $O(N \log N)$ is significantly faster than $O(N^2)$ for large inputs ($N > 10^4$).
