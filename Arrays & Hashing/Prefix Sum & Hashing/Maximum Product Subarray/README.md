# Maximum Product Subarray

## 🧩 Problem Statement
Given an integer array `nums`, find a subarray that has the largest product, and return the product.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [2,3,-2,4]
```
#### Output:
```plaintext
6
```
#### Explanation:
`[2,3]` has the largest product 6.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [-2,0,-1]
```
#### Output:
```plaintext
0
```

## 🔍 Approaches

### 1. Dynamic Programming (Kadane's Variant)
This problem is similar to finding the maximum sum subarray (Kadane's Algo), but the "twist" is negative numbers. A negative number acts as a "flipper" – it makes a large positive product into a large negative one, and vice versa.

### ✨ Intuition
- We need to keep track of both the **maximum** product and the **minimum** product up to the current index.
- Why minimum? Because if the next number is negative, multiplying it by the current minimum (which could be a large negative number) might produce a huge positive number (the new maximum).
- `max_prod = max(n, n * max_prod, n * min_prod)`
- `min_prod = min(n, n * max_prod, n * min_prod)`

### 🔥 Algorithm Steps
1. Initialize `res` to the max value in array (for edge case with single negative number).
2. Initialize `curMin = 1`, `curMax = 1`.
3. Iterate through `nums`:
   - If `n == 0`, reset `curMin` and `curMax` to 1 (conceptually splitting the array).
   - Compute `temp = curMax * n`.
   - Update `curMax = max(n * curMax, n * curMin, n)`.
   - Update `curMin = min(temp, n * curMin, n)`.
   - Update `res = max(res, curMax)`.
4. Return `res`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, single pass.
- **Space Complexity:** $O(1)$, only tracking current max/min.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int res = *max_element(nums.begin(), nums.end());
        int curMin = 1, curMax = 1;
        
        for (int n : nums) {
            if (n == 0) {
                curMin = 1;
                curMax = 1;
                continue;
            }
            int tmp = curMax * n;
            curMax = max({n * curMax, n * curMin, n});
            curMin = min({tmp, n * curMin, n});
            res = max(res, curMax);
        }
        return res;
    }
};
```

### Python
```python
class Solution:
    def maxProduct(self, nums: List[int]) -> int:
        res = max(nums)
        curMin, curMax = 1, 1
        
        for n in nums:
            if n == 0:
                curMin, curMax = 1, 1
                continue
            tmp = curMax * n
            curMax = max(n * curMax, n * curMin, n)
            curMin = min(tmp, n * curMin, n)
            res = max(res, curMax)
        return res
```

### Java
```java
class Solution {
    public int maxProduct(int[] nums) {
        int res = nums[0];
        int curMin = 1, curMax = 1;
        
        for (int n : nums) {
            int tmp = curMax * n;
            curMax = Math.max(Math.max(n * curMax, n * curMin), n);
            curMin = Math.min(Math.min(tmp, n * curMin), n);
            res = Math.max(res, curMax);
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Gambling Streaks:**
Imagine betting where your money multiplies.
- A positive multiplier (x2) doubles your money.
- A negative multiplier (x-2) turns your debt into profit or profit into debt.
- To know your potential max weatlh, you must track both your max possible debt (min) and max profit (max), because a sudden "negative" event could flip that debt into a massive fortune.

## 🎯 Summary
✅ **Handling Negatives:** Tracking min/max is key.
✅ **Edge Cases:** Zeros reset the chain.
