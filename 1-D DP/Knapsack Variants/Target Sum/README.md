# Target Sum Problem

## 🧩 Problem Statement
You are given an integer array `nums` and an integer `target`.

You want to build an expression out of nums by adding one of the symbols `'+'` and `'-'` before each integer in nums and then concatenate all the integers.

For example, if `nums = [2, 1]`, you can add a `'+'` before 2 and a `'-'` before 1 and concatenate them to build the expression `"+2-1"`.
Return the number of different expressions that you can build, which evaluates to `target`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,1,1,1,1], target = 3
```
#### Output:
```plaintext
5
```
**Explanation:** 
- -1+1+1+1+1 = 3
- +1-1+1+1+1 = 3
- +1+1-1+1+1 = 3
- +1+1+1-1+1 = 3
- +1+1+1+1-1 = 3

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1], target = 1
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Recursion with Memoization
We can try both adding and subtracting the current number.
`ways(i, currentSum) = ways(i+1, currentSum + nums[i]) + ways(i+1, currentSum - nums[i])`.
Memoize on `(index, currentSum)`. Note that `currentSum` can be negative, so we need an offset for array indexing or use a Hash Map.

### 2. Space Optimized DP (Subset Sum Transformation)
We can transform this problem into finding a subset with a specific sum.
Let $P$ be the subset of numbers with a `+` sign.
Let $N$ be the subset of numbers with a `-` sign.

We know:
1. $Sum(P) - Sum(N) = target$
2. $Sum(P) + Sum(N) = Sum(nums)$

Adding both equations:
$2 \cdot Sum(P) = target + Sum(nums)$
$Sum(P) = (target + Sum(nums)) / 2$

Thus, the problem reduces to finding the number of subsets of `nums` that sum up to `(target + totalSum) / 2`.
**Constraint:** `(target + totalSum)` must be non-negative and even. If not, return 0.

#### Algorithm Steps:
1. Calculate `totalSum = sum(nums)`.
2. Check if `(totalSum + target)` is odd or if `totalSum < abs(target)`. If so, return 0.
3. `subsetTarget = (totalSum + target) // 2`.
4. Use standard 1D DP for Subset Sum Count (0/1 Knapsack):
   - `dp[j]` = number of ways to get sum `j`.
   - `dp[0] = 1`.
   - For each number `n` in `nums`, update `dp[j]` from `subsetTarget` down to `n`:
     - `dp[j] += dp[j - n]`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot T)$, where $T$ is the `subsetTarget`.
- **Space Complexity:** $O(T)$ for the 1D DP array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        long long totalSum = accumulate(nums.begin(), nums.end(), 0LL);
        
        // Check for validity
        if ((totalSum + target) < 0 || (totalSum + target) % 2 != 0) {
            return 0;
        }
        
        int subsetTarget = (totalSum + target) / 2;
        vector<int> dp(subsetTarget + 1, 0);
        dp[0] = 1;
        
        for (int num : nums) {
            for (int j = subsetTarget; j >= num; --j) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[subsetTarget];
    }
};
```

### Python
```python
from typing import List

class Solution:
    def findTargetSumWays(self, nums: List[int], target: int) -> int:
        total_sum = sum(nums)
        
        # Check constraints: 
        # 1. total_sum + target must be non-negative (since subset sum can't be negative)
        # 2. total_sum + target must be even
        if (total_sum + target) < 0 or (total_sum + target) % 2 != 0:
            return 0
            
        subset_target = (total_sum + target) // 2
        
        dp = [0] * (subset_target + 1)
        dp[0] = 1
        
        for num in nums:
            for j in range(subset_target, num - 1, -1):
                dp[j] += dp[j - num]
                
        return dp[subset_target]
```

### Java
```java
import java.util.Arrays;

class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;
        
        if ((totalSum + target) < 0 || (totalSum + target) % 2 != 0) {
            return 0;
        }
        
        int subsetTarget = (totalSum + target) / 2;
        int[] dp = new int[subsetTarget + 1];
        dp[0] = 1;
        
        for (int num : nums) {
            for (int j = subsetTarget; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[subsetTarget];
    }
}
```

## 🌍 Real-World Analogy
### **Balancing a Scale:**
You have weights (nums). You put some on the left pan (positive) and some on the right pan (negative). You want the difference to be exactly `target`. This is mathematically equivalent to picking a subset for one pan that totals a specific weight.

## 🎯 Summary
✅ **Mathematical Reduction:** Transforming into a known problem (Subset Sum) is often better than solving simply with recursion.
✅ **Constraint Checks:** Always ensure `target` is reachable via parity checks.
