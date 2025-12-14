# Find Target in Sorted Array (Binary Search)

## 🧩 Problem Statement
Given an array of integers `nums` which is sorted in ascending order, and an integer `target`, write a function to search `target` in `nums`. If `target` exists, then return its index. Otherwise, return `-1`.

You must write an algorithm with **O(log n)** runtime complexity.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [-1,0,3,5,9,12], target = 9
```
#### Output:
```plaintext
4
```
#### Explanation:
9 exists in nums and its index is 4.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [-1,0,3,5,9,12], target = 2
```
#### Output:
```plaintext
-1
```
#### Explanation:
2 does not exist in nums so return -1.

## 🔍 Approaches

### 1. Binary Search (Iterative)
Since the array is sorted, we can use Binary Search.
We define a search space `[left, right]`. We check the `mid` element.
- If `nums[mid] == target`, we found it.
- If `nums[mid] < target`, the target must be in the right half, so we move `left = mid + 1`.
- If `nums[mid] > target`, the target must be in the left half, so we move `right = mid - 1`.

### ✨ Intuition
Binary search works by repeatedly dividing the search interval in half.
Imagine looking for a word in a dictionary. You open the middle.
- If the word is alphabetically after, you discard the first half.
- If before, you discard the second half.
- Repeat until found.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `right = n - 1`.
2. While `left <= right`:
   - Calculate `mid = left + (right - left) / 2`. (Avoids overflow compared to `(left + right) / 2`)
   - If `nums[mid] == target`, return `mid`.
   - If `nums[mid] < target`, `left = mid + 1`.
   - If `nums[mid] > target`, `right = mid - 1`.
3. If loop finishes, return `-1`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log n)$, halving search space each step.
- **Space Complexity:** $O(1)$, iterative.

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
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
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
            elif nums[mid] < target:
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
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
}
```

## 🌍 Real-World Analogy
### **Guess the Number Game:**
Someone thinks of a number between 1 and 100.
- You guess 50.
- They say "Higher".
- You know it's between 51-100. You guess 75.
- They say "Lower".
- You know it's between 51-74.
- You keep halving the range efficiently.

## 🎯 Summary
✅ **O(log n):** Most efficient search for sorted data.
✅ **Overflow Safety:** Use `left + (right - left) / 2`.
