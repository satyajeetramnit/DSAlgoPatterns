# Split Array Largest Sum

## 🧩 Problem Statement
Given an integer array `nums` and an integer `k`, split `nums` into `k` non-empty subarrays such that the largest sum of any subarray is **minimized**.

Return the minimized largest sum of the split.

A **subarray** is a contiguous part of an array.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [7,2,5,10,8], k = 2
```
#### Output:
```plaintext
18
```
#### Explanation:
There are four ways to split nums into 2 subarrays.
The best way is to split it into `[7,2,5]` and `[10,8]`, where the largest sum is `max(14, 18) = 18`.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1,2,3,4,5], k = 2
```
#### Output:
```plaintext
9
```
#### Explanation:
Best split is `[1,2,3]` and `[4,5]`. Largest sum is `max(6, 9) = 9`.

## 🔍 Approaches

### 1. Binary Search on Answer
This problem is identical to "Capacity to Ship Packages" and "Book Allocation Problem".
- We want to minimize the maximum sum.
- **Lower Bound:** `max(nums)` (a subarray must contain at least the largest element).
- **Upper Bound:** `sum(nums)` (one subarray contains everything).
- We check if a value `mid` is a valid "max sum".

### ✨ Intuition
- If we set a max sum limit `S`, can we split the array into `<= k` subarrays such that no subarray sum exceeds `S`?
- As `S` increases, the number of required subarrays decreases (strictly non-increasing).
- This monotonicity allows Binary Search.
- We want the *smallest* `S` such that required subarrays `<= k`.

### 🔥 Algorithm Steps
1. `left = max(nums)`, `right = sum(nums)`.
2. Function `canSplit(maxSum)`:
   - Iterate through `nums`, accumulating sum.
   - If adding `nums[i]` exceeds `maxSum`, start a new subarray.
   - Count subarrays used.
   - Return `true` if `count <= k`.
3. Binary Search:
   - `mid = left + (right - left) / 2`.
   - If `canSplit(mid)`:
     - Feasible. Try to minimize further: `right = mid - 1`.
   - Else:
     - Not feasible (need more splits implies `maxSum` is too small): `left = mid + 1`.
4. Return `left`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n \cdot \log(\sum \text{nums}))$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        long long left = 0, right = 0;
        for (int n : nums) {
            left = max(left, (long long)n);
            right += n;
        }

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (canSplit(nums, k, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return (int)left;
    }

private:
    bool canSplit(const vector<int>& nums, int k, long long maxSum) {
        int subarrays = 1;
        long long currentSum = 0;
        
        for (int n : nums) {
            if (currentSum + n > maxSum) {
                subarrays++;
                currentSum = n;
            } else {
                currentSum += n;
            }
        }
        return subarrays <= k;
    }
};
```

### Python
```python
class Solution:
    def splitArray(self, nums: List[int], k: int) -> int:
        def canSplit(max_sum):
            subarrays = 1
            current_sum = 0
            for num in nums:
                if current_sum + num > max_sum:
                    subarrays += 1
                    current_sum = num
                else:
                    current_sum += num
            return subarrays <= k

        left, right = max(nums), sum(nums)
        
        while left <= right:
            mid = (left + right) // 2
            if canSplit(mid):
                right = mid - 1
            else:
                left = mid + 1
        return left
```

### Java
```java
class Solution {
    public int splitArray(int[] nums, int k) {
        long left = 0, right = 0;
        for (int n : nums) {
            left = Math.max(left, n);
            right += n;
        }

        while (left <= right) {
            long mid = left + (right - left) / 2;
            if (canSplit(nums, k, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return (int)left;
    }

    private boolean canSplit(int[] nums, int k, long maxSum) {
        int subarrays = 1;
        long currentSum = 0;
        
        for (int n : nums) {
            if (currentSum + n > maxSum) {
                subarrays++;
                currentSum = n;
            } else {
                currentSum += n;
            }
        }
        return subarrays <= k;
    }
}
```

## 🌍 Real-World Analogy
### **Printing Book Volumes:**
You have a manuscript with chapters of varying lengths. You need to print it in `k` volumes.
- You want the volumes to be as balanced as possible.
- Minimizing the largest volume size ensures no single volume is excessively thick.

## 🎯 Summary
✅ **Identical Structure:** Same logic as "Capacity to Ship Packages", just different context.
✅ **Long Long:** Use `long long`/`long` for sums to prevent overflow during calculations.
