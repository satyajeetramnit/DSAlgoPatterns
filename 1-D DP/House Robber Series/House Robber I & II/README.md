# House Robber I & II

## 🧩 Problem Statement

### House Robber I
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

Given an integer array `nums` representing the amount of money of each house, return the maximum amount of money you can rob tonight **without alerting the police**.

### House Robber II
The problem is the same as above, except that **all houses at this place are arranged in a circle**. That means the first house is the neighbor of the last one.

## 🔍 Approaches

### 1. Dynamic Programming (Linear) - House Robber I
Let `dp[i]` be the maximum money we can rob from the first `i` houses.
- For house `i`, we have two choices:
  1. **Rob it:** We get `nums[i]` + max money from `i-2` houses (`dp[i-2]`).
  2. **Skip it:** We keep max money from `i-1` houses (`dp[i-1]`).
- Recurrence: `dp[i] = max(nums[i] + dp[i-2], dp[i-1])`.
- Space Optimization: We only need the previous two values, so we can use two variables `prev1` and `prev2`.

### 2. Handling Circularity - House Robber II
Since the first and last houses are neighbors, we cannot rob both.
This breaks the problem into two linear House Robber I subproblems:
1. Rob houses from index `0` to `n-2` (exclude the last house).
2. Rob houses from index `1` to `n-1` (exclude the first house).
- The answer is `max(robLinear(0, n-2), robLinear(1, n-1))`.
- Base case: If size is 1, return `nums[0]`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$ for both versions.
- **Space Complexity:** $O(1)$ (using space-optimized DP variables).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int robLinear(vector<int>& nums, int start, int end) {
        int prev2 = 0, prev1 = 0;
        for (int i = start; i <= end; ++i) {
            int current = max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }

    int rob1(vector<int>& nums) {
        if (nums.empty()) return 0;
        return robLinear(nums, 0, nums.size() - 1);
    }

    int rob2(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        // Max of: robbing 0 to n-2 OR robbing 1 to n-1
        return max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }
};
```

### Python
```python
from typing import List

class Solution:
    def robLinear(self, nums: List[int]) -> int:
        prev1, prev2 = 0, 0
        for num in nums:
            current = max(prev1, prev2 + num)
            prev2 = prev1
            prev1 = current
        return prev1

    def rob1(self, nums: List[int]) -> int:
        return self.robLinear(nums)

    def rob2(self, nums: List[int]) -> int:
        n = len(nums)
        if n == 0: return 0
        if n == 1: return nums[0]
        return max(self.robLinear(nums[:-1]), self.robLinear(nums[1:]))
```

### Java
```java
class Solution {
    public int robLinear(int[] nums, int start, int end) {
        int prev2 = 0, prev1 = 0;
        for (int i = start; i <= end; i++) {
            int current = Math.max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }

    public int rob1(int[] nums) {
        if (nums.length == 0) return 0;
        return robLinear(nums, 0, nums.length - 1);
    }

    public int rob2(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        return Math.max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }
}
```

## 🌍 Real-World Analogy
### **Picking Flowers:**
You want to pick flowers from a garden row, but picking two adjacent flowers ruins the roots of both. You want to maximize the bouquet value. If the garden is circular, dealing with the loop requires splitting the logic.

## 🎯 Summary
✅ **Decomposition:** Reducing Circular problem to two Linear problems.
✅ **Space Optimization:** Standard DP technique reducing $O(N)$ array to $O(1)$ variables.
