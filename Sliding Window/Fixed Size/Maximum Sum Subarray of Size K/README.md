# Maximum Sum Subarray of Size K

## 🧩 Problem Statement
Given an array of integers `nums` and a positive integer `k`, find the maximum sum of any contiguous subarray of size `k`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [2, 1, 5, 1, 3, 2], k = 3
```
#### Output:
```plaintext
9
```
#### Explanation:
Subarray with maximum sum is `[5, 1, 3]`. Sum = 5 + 1 + 3 = 9.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [2, 3, 4, 1, 5], k = 2
```
#### Output:
```plaintext
7
```
#### Explanation:
Subarray with maximum sum is `[3, 4]`. Sum = 7.

## 🔍 Approaches

### 1. Brute Force
Calculate the sum of every possible subarray of size `k`.
- Iterate from `i = 0` to `n - k`.
- For each `i`, sum `nums[i...i+k-1]`.
- Update max sum.
- **Time Complexity:** $O(n \cdot k)$

### 2. Sliding Window (Fixed Size)
Instead of recalculating the sum from scratch, we can reuse the sum of the previous window.
- Start with sum of first `k` elements.
- Slide window one step to the right:
  - **Subtract** the element going out of the window (`nums[i - 1]`).
  - **Add** the element coming into the window (`nums[i + k - 1]`).
- This allows calculating the new sum in $O(1)$ time.

### ✨ Intuition
Imagine a window frame of width `k` sliding over the array. As it moves right, one element enters the view and one leaves. The change in sum is just `+new_element - old_element`.

### 🔥 Algorithm Steps
1. Calculate the sum of the first `k` elements (`currentSum`).
2. Initialize `maxSum = currentSum`.
3. Iterate `i` from `0` to `n - k - 1` (or iterate window end from `k` to `n-1`):
   - `currentSum = currentSum - nums[i] + nums[i + k]`
   - `maxSum = max(maxSum, currentSum)`
4. Return `maxSum`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, since we pass through the array once.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int maxSumSubarray(vector<int>& nums, int k) {
        if (nums.size() < k) return -1; // Or handle error

        long long currentSum = 0;
        for (int i = 0; i < k; i++) {
            currentSum += nums[i];
        }

        long long maxSum = currentSum;
        for (int i = k; i < nums.size(); i++) {
            currentSum += nums[i] - nums[i - k];
            maxSum = max(maxSum, currentSum);
        }
        return (int)maxSum;
    }
};
```

### Python
```python
class Solution:
    def maxSumSubarray(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n < k:
            return -1

        current_sum = sum(nums[:k])
        max_sum = current_sum

        for i in range(k, n):
            current_sum += nums[i] - nums[i - k]
            max_sum = max(max_sum, current_sum)
        
        return max_sum
```

### Java
```java
class Solution {
    public int maxSumSubarray(int[] nums, int k) {
        if (nums.length < k) return -1;

        long currentSum = 0;
        for (int i = 0; i < k; i++) {
            currentSum += nums[i];
        }

        long maxSum = currentSum;
        for (int i = k; i < nums.length; i++) {
            currentSum += nums[i] - nums[i - k];
            maxSum = Math.max(maxSum, currentSum);
        }
        return (int)maxSum;
    }
}
```

## 🌍 Real-World Analogy
### **Moving Average of Sales:**
A store wants to know the best 7-day sales streak.
- Instead of adding up 7 days again and again, just take yesterday's 7-day total, subtract the sales from 8 days ago, and add today's sales.

## 🎯 Summary
✅ **Basic Pattern:** The foundation for all sliding window problems.
✅ **Linear Time:** Converts $O(n^2)$ or $O(nk)$ to $O(n)$.
