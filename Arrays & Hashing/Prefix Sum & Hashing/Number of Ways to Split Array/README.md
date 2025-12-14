# Number of Ways to Split Array

## 🧩 Problem Statement
You are given a **0-indexed** integer array `nums` of length `n`.

`nums` contains a **valid split** at index `i` if the following are true:
- The sum of the first `i + 1` elements (left part) is **greater than or equal to** the sum of the last `n - i - 1` elements (right part).
- There is at least one element to the right of `i`. That is, `0 <= i < n - 1`.

Return the number of **valid splits** in `nums`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [10,4,-8,7]
```
#### Output:
```plaintext
2
```
#### Explanation:
- i=0: Left=[10], Right=[4,-8,7] (Sum 3). 10 >= 3 (Valid)
- i=1: Left=[10,4], Right=[-8,7] (Sum -1). 14 >= -1 (Valid)
- i=2: Left=[10,4,-8], Right=[7]. 6 < 7 (Invalid)

### 🔹 Example 2:
#### Input:
```plaintext
nums = [2,3,1,0]
```
#### Output:
```plaintext
2
```

## 🔍 Approaches

### 1. Prefix Sum Optimization
A naive solution would calculate the sum of left and right parts for every split, taking $O(n^2)$.
We can optimize this by calculating the `totalSum` first.

### ✨ Intuition
- `rightSum = totalSum - leftSum`.
- We want: `leftSum >= rightSum`.
- Substituting: `leftSum >= totalSum - leftSum` => `2 * leftSum >= totalSum`.
- We just need to iterate, maintain `leftSum`, and check this condition.

### 🔥 Algorithm Steps
1. Calculate `totalSum`.
2. Initialize `leftSum = 0`, `count = 0`.
3. Iterate `i` from `0` to `n-2` (must leave one element for right).
   - Add `nums[i]` to `leftSum`.
   - If `leftSum >= totalSum - leftSum`, increment `count`.
4. Return `count`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, one pass to find total sum, one pass to check splits.
- **Space Complexity:** $O(1)$, minimal extra variables used.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        long long totalSum = 0;
        for (int n : nums) totalSum += n;
        
        long long leftSum = 0;
        int count = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            leftSum += nums[i];
            long long rightSum = totalSum - leftSum;
            if (leftSum >= rightSum) {
                count++;
            }
        }
        return count;
    }
};
```

### Python
```python
class Solution:
    def waysToSplitArray(self, nums: List[int]) -> int:
        totalSum = sum(nums)
        leftSum = 0
        count = 0
        
        for i in range(len(nums) - 1):
            leftSum += nums[i]
            rightSum = totalSum - leftSum
            if leftSum >= rightSum:
                count += 1
        return count
```

### Java
```java
class Solution {
    public int waysToSplitArray(int[] nums) {
        long totalSum = 0;
        for (int n : nums) totalSum += n;
        
        long leftSum = 0;
        int count = 0;
        for (int i = 0; i < nums.length - 1; i++) {
            leftSum += nums[i];
            long rightSum = totalSum - leftSum;
            if (leftSum >= rightSum) {
                count++;
            }
        }
        return count;
    }
}
```

## 🌍 Real-World Analogy
### **Sharing the Workload:**
Imagine a project with tasks of varying difficulty (some negative if they are actually fun/rewards).
- You want to draw a line between "My tasks" and "Your tasks".
- A "Valid Split" is when you (starting first) take on a workload $\ge$ what you leave for your partner.
- You check every possible cut-off point to see if it's "fair" (for you, defining fair as taking the brunt of it).

## 🎯 Summary
✅ **O(n) Optimization:** Avoids nested loops.
✅ **Edge Cases:** Loop until `n-2` to ensure right side exists.
