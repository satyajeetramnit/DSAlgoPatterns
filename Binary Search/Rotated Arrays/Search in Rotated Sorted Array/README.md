# Search in Rotated Sorted Array

## 🧩 Problem Statement
There is an integer array `nums` sorted in ascending order (with distinct values).
Prior to being passed to your function, `nums` is possibly **rotated** at an unknown pivot index `k` (`1 <= k < nums.length`) such that the resulting array is `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]`.

Given the array `nums` after the possible rotation and an integer `target`, return the index of `target` if it is in `nums`, or `-1` if it is not in `nums`.

You must write an algorithm with **O(log n)** runtime complexity.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [4,5,6,7,0,1,2], target = 0
```
#### Output:
```plaintext
4
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [4,5,6,7,0,1,2], target = 3
```
#### Output:
```plaintext
-1
```

### 🔹 Example 3:
#### Input:
```plaintext
nums = [1], target = 0
```
#### Output:
```plaintext
-1
```

## 🔍 Approaches

### 1. Binary Search
In a rotated sorted array, at least one half of the array (split by `mid`) is always sorted.
We check which half is sorted, and then check if the target lies within that sorted half.

### ✨ Intuition
1. Identify `mid`.
2. Check if the **left half** `[left...mid]` is sorted:
   - If `nums[left] <= nums[mid]`.
   - Then check if `target` is in range `[nums[left], nums[mid]]`.
     - If yes, search left (`right = mid - 1`).
     - If no, search right (`left = mid + 1`).
3. Else, the **right half** `[mid...right]` must be sorted:
   - Check if `target` is in range `[nums[mid], nums[right]]`.
     - If yes, search right (`left = mid + 1`).
     - If no, search left (`right = mid - 1`).

### 🔥 Algorithm Steps
1. `left = 0`, `right = n - 1`.
2. While `left <= right`:
   - `mid = left + (right - left) / 2`.
   - If `nums[mid] == target`, return `mid`.
   - **Check if Left Half is Sorted (`nums[left] <= nums[mid]`):**
     - If `nums[left] <= target < nums[mid]`: `right = mid - 1`.
     - Else: `left = mid + 1`.
   - **Else (Right Half must be sorted):**
     - If `nums[mid] < target <= nums[right]`: `left = mid + 1`.
     - Else: `right = mid - 1`.
3. Return `-1`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log n)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            
            // Check if left half is sorted
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // Right half is sorted
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
```

### Python
```python
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                return mid
            
            # Left half is sorted
            if nums[left] <= nums[mid]:
                if nums[left] <= target < nums[mid]:
                    right = mid - 1
                else:
                    left = mid + 1
            # Right half is sorted
            else:
                if nums[mid] < target <= nums[right]:
                    left = mid + 1
                else:
                    right = mid - 1
        return -1
```

### Java
```java
class Solution {
    public int search(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            
            if (nums[left] <= nums[mid]) {
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
}
```

## 🌍 Real-World Analogy
### **Looking for a House Number on a Circular Street:**
Imagine a street that goes 100-200, then wraps around to 1-99.
- You are at house 150. You want house 50.
- 150 > 50? Normally go left. But wait, 1-99 are to the right of 200.
- You need to know which section you are in to decide direction.

## 🎯 Summary
✅ **One sorted half:** Always guaranteed in rotated sorted arrays.
✅ **Condition logic:** Crucial to check boundary conditions correctly (`<=`).
