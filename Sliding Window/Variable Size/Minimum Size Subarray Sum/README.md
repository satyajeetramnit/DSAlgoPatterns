# Minimum Size Subarray Sum

## 🧩 Problem Statement
Given an array of positive integers `nums` and a positive integer `target`, return the **minimal length** of a contiguous subarray of which the sum is greater than or equal to `target`. If there is no such subarray, return `0` instead.

### 🔹 Example 1:
#### Input:
```plaintext
target = 7, nums = [2,3,1,2,4,3]
```
#### Output:
```plaintext
2
```
#### Explanation:
The subarray [4,3] has the minimal length under the problem constraint.

### 🔹 Example 2:
#### Input:
```plaintext
target = 4, nums = [1,4,4]
```
#### Output:
```plaintext
1
```

### 🔹 Example 3:
#### Input:
```plaintext
target = 11, nums = [1,1,1,1,1,1,1,1]
```
#### Output:
```plaintext
0
```

## 🔍 Approaches

### 1. Brute Force
Try every subarray `[i, j]`, calculate sum. Return min length.
- Time: $O(n^2)$ or $O(n^3)$.

### 2. Sliding Window (Variable Size)
Since all numbers are positive, the sum increases as we expand the window and decreases as we shrink it. This monotonicity allows a sliding window approach.
- Expand `right` pointer to increase sum.
- Once `sum >= target`, try to shrink from `left` to find the smallest valid window ending at `right`.
- Update minimal length.

### ✨ Intuition
Think of an elastic worm.
- Head stretches out until it eats enough food (Target).
- Once full, the tail shrinks forward as much as possible while staying full, to keep the worm short.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `currentSum = 0`, `minLen = infinity`.
2. Iterate `right` from `0` to `n-1`:
   - `currentSum += nums[right]`
   - While `currentSum >= target`:
     - `minLen = min(minLen, right - left + 1)`
     - `currentSum -= nums[left]`
     - `left++`
3. Return `minLen` (or `0` if it's still infinity).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$. Each element is visited at most twice (once by right, once by left).
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int currentSum = 0;
        int minLen = INT_MAX;
        
        for (int right = 0; right < nums.size(); right++) {
            currentSum += nums[right];
            
            while (currentSum >= target) {
                minLen = min(minLen, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }
        
        return (minLen == INT_MAX) ? 0 : minLen;
    }
};
```

### Python
```python
class Solution:
    def minSubArrayLen(self, target: int, nums: List[int]) -> int:
        left = 0
        current_sum = 0
        min_len = float('inf')
        
        for right in range(len(nums)):
            current_sum += nums[right]
            
            while current_sum >= target:
                min_len = min(min_len, right - left + 1)
                current_sum -= nums[left]
                left += 1
                
        return 0 if min_len == float('inf') else min_len
```

### Java
```java
class Solution {
    public int minSubArrayLen(int target, int[] nums) {
        int left = 0;
        int currentSum = 0;
        int minLen = Integer.MAX_VALUE;
        
        for (int right = 0; right < nums.length; right++) {
            currentSum += nums[right];
            
            while (currentSum >= target) {
                minLen = Math.min(minLen, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }
        
        return (minLen == Integer.MAX_VALUE) ? 0 : minLen;
    }
}
```

## 🌍 Real-World Analogy
### **Filling a Bucket:**
You have a hose (array of water drops). You need to fill a bucket of size `Target`.
- You turn on the hose.
- As soon as the bucket is full, you wonder: "Could I have filled it with fewer big drops if I started later?"
- You discard early drops until the bucket is just below full, measuring the time (length) it took.

## 🎯 Summary
✅ **Expansion/Contraction:** Classic "Expand until valid, Shrink to optimize" pattern.
✅ **Edge Case:** Return 0 if sum never reaches target.
