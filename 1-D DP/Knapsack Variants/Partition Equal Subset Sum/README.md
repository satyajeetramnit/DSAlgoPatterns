# Partition Equal Subset Sum

## 🧩 Problem Statement
Given an integer array `nums`, return `true` if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or `false` otherwise.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,5,11,5]
```
#### Output:
```plaintext
true
```
**Explanation:** The array can be partitioned as [1, 5, 5] and [11]. The sum of each subset is 11.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1,2,3,5]
```
#### Output:
```plaintext
false
```
**Explanation:** The array cannot be partitioned into equal sum subsets.

## 🔍 Approaches

### 1. Dynamic Programming (Subset Sum Variation)
This problem is equivalent to finding a subset of `nums` that sums up to `totalSum / 2`.
1. Calculate `totalSum = sum(nums)`.
2. If `totalSum` is odd, we cannot divide it into two equal integers. Return `false`.
3. Set `target = totalSum / 2`.
4. Solve the **Subset Sum** problem for `target`.

#### Algorithm (Space Optimized):
- Use a boolean array `dp` of size `target + 1`.
- `dp[0] = true`.
- For each `num` in `nums`:
  - Update `dp[j]` for `j` from `target` down to `num`:
    - `dp[j] = dp[j] || dp[j - num]`

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot T)$, where $N$ is array length and $T$ is the target sum ($Sum/2$).
- **Space Complexity:** $O(T)$ for the DP array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        
        // If sum is odd, cannot partition into two equal integer subsets
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        
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
    def canPartition(self, nums: List[int]) -> bool:
        total_sum = sum(nums)
        
        if total_sum % 2 != 0:
            return False
            
        target = total_sum // 2
        dp = [False] * (target + 1)
        dp[0] = True
        
        for num in nums:
            for j in range(target, num - 1, -1):
                if dp[j - num]:
                    dp[j] = True
                    
        return dp[target]
```

### Java
```java
class Solution {
    public boolean canPartition(int[] nums) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;
        
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        
        return dp[target];
    }
}
```

## 🌍 Real-World Analogy
### **Sharing Candy:**
Two siblings want to split a bag of candies so that each gets exactly the same total weight/value of candy. You sum them up, divide by 2, and seeing if you can pick pieces that sum to that exact half.

## 🎯 Summary
✅ **Problem Reduction:** This reduces directly to 0/1 Knapsack (Subset Sum) with `target = sum / 2`.
