# Search Insert Position

## 🧩 Problem Statement
Given a sorted array of distinct integers and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You must write an algorithm with **O(log n)** runtime complexity.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,3,5,6], target = 5
```
#### Output:
```plaintext
2
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1,3,5,6], target = 2
```
#### Output:
```plaintext
1
```

### 🔹 Example 3:
#### Input:
```plaintext
nums = [1,3,5,6], target = 7
```
#### Output:
```plaintext
4
```

## 🔍 Approaches

### 1. Binary Search
This is a variation of binary search where we want to find the first element `>=` target (lower_bound logic).
If we find `nums[mid] == target`, we return `mid`.
If the loop finishes without finding `target`, `left` will naturally point to the correction insertion position.

### ✨ Intuition
- Standard binary search finds an exact match.
- Here, we narrow down the range.
- When `left > right`, the loop terminates.
- At termination, `left` is the index of the first element greater than target, which is exactly where target should go.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `right = n - 1`.
2. While `left <= right`:
   - `mid = left + (right - left) / 2`.
   - If `nums[mid] == target`, return `mid`.
   - If `nums[mid] < target`, `left = mid + 1`.
   - If `nums[mid] > target`, `right = mid - 1`.
3. Return `left`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log n)$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;    
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
};
```

### Python
```python
class Solution:
    def searchInsert(self, nums: List[int], target: int) -> int:
        left, right = 0, len(nums) - 1
        
        while left <= right:
            mid = (left + right) // 2
            
            if nums[mid] == target:
                return mid
            
            if nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
                
        return left
```

### Java
```java
class Solution {
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }
}
```

## 🌍 Real-World Analogy
### **Library Bookshelf:**
You have a row of books sorted by ID. You want to place a new book with ID `X`.
- You check the middle book. ID is smaller than X? Look right.
- ID is bigger than X? Look left.
- Eventually, you find a spot between two books (or at an end) where the left book is smaller and right book is bigger. That's your spot.

## 🎯 Summary
✅ **O(log n):** Required complexity.
✅ **Return `left`:** The key modification to standard binary search.
