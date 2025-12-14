# Find Middle Index in Array

## 🧩 Problem Statement
Given a **0-indexed** integer array `nums`, find the **leftmost** `middleIndex` (i.e., the smallest amongst all the possible ones).

A `middleIndex` is an index where:
$$ \text{sum}(\text{nums}[0] \dots \text{nums}[\text{middleIndex}-1]) == \text{sum}(\text{nums}[\text{middleIndex}+1] \dots \text{nums}[n-1]) $$

If `middleIndex == 0`, the left side sum is considered to be `0`. Similarly, if `middleIndex == nums.length - 1`, the right side sum is considered to be `0`.

Return the **leftmost** `middleIndex` that satisfies the condition, or `-1` if there is no such index.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [2,3,-1,8,4]
```
#### Output:
```plaintext
3
```
#### Explanation:
- Sum before index 3: $2 + 3 + -1 = 4$
- Sum after index 3: $4 = 4$

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1,-1,4]
```
#### Output:
```plaintext
2
```
#### Explanation:
- Sum before index 2: $1 + -1 = 0$
- Sum after index 2: $0$

## 🔍 Approaches

### 1. Prefix Sum Calculation
We need to check if `leftSum == rightSum` at each index `i`.
We know that `totalSum = leftSum + nums[i] + rightSum`.
Therefore, `rightSum = totalSum - leftSum - nums[i]`.
The condition `leftSum == rightSum` becomes `leftSum == totalSum - leftSum - nums[i]`, or `2 * leftSum + nums[i] == totalSum`.

### ✨ Intuition
- Calculate the `totalSum` of the array first.
- Iterate through the array maintaining a running `leftSum`.
- At each step, calculate `rightSum`.
- Check if they are equal.

### 🔥 Algorithm Steps
1. Calculate `totalSum = sum(nums)`.
2. Initialize `leftSum = 0`.
3. Iterate `i` from `0` to `n-1`:
   - Calculate `rightSum = totalSum - leftSum - nums[i]`.
   - If `leftSum == rightSum`, return `i`.
   - Update `leftSum += nums[i]`.
4. If checking all indices fails, return `-1`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, two passes (one for sum, one for check).
- **Space Complexity:** $O(1)$, only constant extra space used.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int findMiddleIndex(vector<int>& nums) {
        int totalSum = 0;
        for (int n : nums) totalSum += n;
        
        int leftSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            int rightSum = totalSum - leftSum - nums[i];
            if (leftSum == rightSum) return i;
            leftSum += nums[i];
        }
        return -1;
    }
};
```

### Python
```python
class Solution:
    def findMiddleIndex(self, nums: List[int]) -> int:
        totalSum = sum(nums)
        leftSum = 0
        
        for i, n in enumerate(nums):
            rightSum = totalSum - leftSum - n
            if leftSum == rightSum:
                return i
            leftSum += n
        return -1
```

### Java
```java
class Solution {
    public int findMiddleIndex(int[] nums) {
        int totalSum = 0;
        for (int n : nums) totalSum += n;
        
        int leftSum = 0;
        for (int i = 0; i < nums.length; i++) {
            int rightSum = totalSum - leftSum - nums[i];
            if (leftSum == rightSum) return i;
            leftSum += nums[i];
        }
        return -1;
    }
}
```

## 🌍 Real-World Analogy
### **Balancing a Scale:**
Imagine a rod with weights along it. You want to find a pivot point where the rod balances perfectly.
- The weight at the pivot point doesn't contribute to either side's torque (in this simplified analogy, or assume it's the fulcrum).
- The total weight on the left must equal the total weight on the right.

## 🎯 Summary
✅ **O(n) Time:** Efficient linear scan.
✅ **Prefix Sum Pattern:** Fundamental technique for array problems.
