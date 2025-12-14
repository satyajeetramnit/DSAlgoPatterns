# Subset Sum Problem

## 🧩 Problem Statement
Given a set of non-negative integers `nums` and a value `target`, determine if there is a subset of the given set with sum equal to `target`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [3, 34, 4, 12, 5, 2], target = 9
```
#### Output:
```plaintext
True
```
**Explanation:** There is a subset (4, 5) with sum 9.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [3, 34, 4, 12, 5, 2], target = 30
```
#### Output:
```plaintext
False
```
**Explanation:** There is no subset that adds up to 30.

## 🔍 Approaches

### 1. Dynamic Programming (0/1 Knapsack Pattern)
This problem is a variation of the **0/1 Knapsack** problem. For each element, we have two choices:
1. **Include** the element in the subset (if it's not greater than the remaining required sum).
2. **Exclude** the element from the subset.

#### Recursive State:
`isSubsetSum(n, target)` returns true if a subset of the first `n` elements sums to `target`.
- Base Cases:
  - `target == 0`: True (empty subset).
  - `n == 0 && target != 0`: False.
- Recurrence:
  - If `nums[n-1] > target`: We can't include it. `isSubsetSum(n-1, target)`
  - Else: `isSubsetSum(n-1, target) || isSubsetSum(n-1, target - nums[n-1])`

#### Tabulation (Bottom-Up):
Create a 2D boolean table `dp[n+1][target+1]`.
- `dp[i][j]` is true if a sum of `j` can be achieved using the first `i` elements.
- **Initialization:**
  - `dp[0][0] = true`
  - `dp[0][j] = false` for `j > 0`
  - `dp[i][0] = true` (sum 0 is always possible with empty set)
- **Transition:**
  - `dp[i][j] = dp[i-1][j]` (Exclude)
  - If `j >= nums[i-1]`: `dp[i][j] = dp[i][j] || dp[i-1][j - nums[i-1]]` (Include)

#### Space Optimization:
Since `dp[i][j]` only depends on `dp[i-1][...]`, we can reduce space to a 1D array `dp[target+1]`. We iterate backwards to avoid using the same element multiple times for the same sum level.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot T)$, where $N$ is the number of elements and $T$ is the target sum.
- **Space Complexity:** $O(N \cdot T)$ for 2D table, or $O(T)$ for space-optimized 1D array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isSubsetSum(vector<int>& nums, int target) {
        int n = nums.size();
        vector<bool> dp(target + 1, false);
        
        dp[0] = true; // Sum of 0 is always possible
        
        for (int num : nums) {
            for (int j = target; j >= num; --j) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        
        return dp[target];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def isSubsetSum(self, nums: List[int], target: int) -> bool:
        # dp[i] will be True if sum i is achievable
        dp = [False] * (target + 1)
        dp[0] = True
        
        for num in nums:
            # Iterate backwards to avoid using the same element twice for the same target
            for j in range(target, num - 1, -1):
                if dp[j - num]:
                    dp[j] = True
                    
        return dp[target]
```

### Java
```java
class Solution {
    public boolean isSubsetSum(int[] nums, int target) {
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;
        
        for(int num : nums) {
            for(int j = target; j >= num; j--) {
                if(dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        return dp[target];
    }
}
```

## 🌍 Real-World Analogy
### **Paying Exact Change:**
You have a collection of coins/bills. Can you pay exactly $X amount using a subset of your money without getting change back?

## 🎯 Summary
✅ **0/1 Knapsack Pattern:** Decision at each step is "take it or leave it".
✅ **Space Optimization:** Iterate backwards when compressing 2D DP to 1D to prevent reusing the current item.
