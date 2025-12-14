# Find Minimum in Rotated Sorted Array

## 🧩 Problem Statement
Suppose an array of length `n` sorted in ascending order is rotated between `1` and `n` times. For example, the array `original = [0,1,2,4,5,6,7]` might become:
- `[4,5,6,7,0,1,2]` if it was rotated 4 times.
- `[0,1,2,4,5,6,7]` if it was rotated 7 times.

Notice that rotating an array `[a[0], a[1], a[2], ..., a[n-1]]` 1 time results in the array `[a[n-1], a[0], a[1], a[2], ..., a[n-2]]`.

Given the sorted rotated array `nums` of **unique** elements, return the *minimum element* of this array.

You must write an algorithm that runs in **O(log n)** time.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [3,4,5,1,2]
```
#### Output:
```plaintext
1
```
#### Explanation:
The original array was [1,2,3,4,5] rotated 3 times.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [4,5,6,7,0,1,2]
```
#### Output:
```plaintext
0
```

### 🔹 Example 3:
#### Input:
```plaintext
nums = [11,13,15,17]
```
#### Output:
```plaintext
11
```

## 🔍 Approaches

### 1. Binary Search
The binary search works because even though the array isn't fully sorted, one half is always sorted.
The minimum element acts as the "pivot" point.
We compare `nums[mid]` with `nums[right]`.

### ✨ Intuition
- If `nums[mid] > nums[right]`:
  - The mid element is greater than the rightmost element.
  - This implies the pivot (minimum) is in the **right half**.
  - Example: `[4,5,6,1,2]`, mid=6, right=2. 6 > 2. Lowest is to the right.
  - New search: `left = mid + 1`.
- If `nums[mid] <= nums[right]`:
  - The right half is sorted (or single element), so the minimum is either at `mid` or in the **left half**.
  - Example: `[6,1,2,3,4]`, mid=2, right=4. 2 <= 4. Lowest is to the left (or is 2).
  - New search: `right = mid`.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `right = n - 1`.
2. While `left < right`: (loop terminates when left == right)
   - `mid = left + (right - left) / 2`.
   - If `nums[mid] > nums[right]`:
     - `left = mid + 1`
   - Else:
     - `right = mid`
3. Return `nums[left]`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log n)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }
};
```

### Python
```python
class Solution:
    def findMin(self, nums: List[int]) -> int:
        left, right = 0, len(nums) - 1
        
        while left < right:
            mid = (left + right) // 2
            if nums[mid] > nums[right]:
                left = mid + 1
            else:
                right = mid
        return nums[left]
```

### Java
```java
class Solution {
    public int findMin(int[] nums) {
        int left = 0, right = nums.length - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return nums[left];
    }
}
```

## 🌍 Real-World Analogy
### **Finding the Start of a New Cycle:**
Imagine a clock face or a dial that goes 1-12, but someone cut it and laid it flat starting from 4: `4, 5, 6, ..., 12, 1, 2, 3`.
- You want to find '1'.
- You look at the middle number. If it's bigger than the end number, you know the "reset" happened after the middle.
- If the middle number is smaller than the end, the "reset" (or 1) is to the left.

## 🎯 Summary
✅ **Pivot Finding:** Core technique for rotated array problems.
✅ **Compare to right:** Avoids edge cases compared to comparing to left.
