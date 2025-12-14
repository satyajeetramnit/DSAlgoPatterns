# Rotate Array

## 🧩 Problem Statement
Given an integer array `nums`, rotate the array to the right by `k` steps, where `k` is non-negative.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,2,3,4,5,6,7], k = 3
```
#### Output:
```plaintext
[5,6,7,1,2,3,4]
```
#### Explanation:
1. rotate 1 steps to the right: `[7,1,2,3,4,5,6]`
2. rotate 2 steps to the right: `[6,7,1,2,3,4,5]`
3. rotate 3 steps to the right: `[5,6,7,1,2,3,4]`

### 🔹 Example 2:
#### Input:
```plaintext
nums = [-1,-100,3,99], k = 2
```
#### Output:
```plaintext
[3,99,-1,-100]
```

## 🔍 Approaches

### 1. Reverse Array Method (Optimal)
We can achieve the rotation by reversing parts of the array.
- Reverse entire array.
- Reverse the first `k` elements.
- Reverse the remaining `n-k` elements.

### ✨ Intuition
- Original: `1 2 3 4 5 6 7`, k=3
- Reverse All: `7 6 5 4 3 2 1`
- Reverse first k (indices 0-2): `5 6 7 4 3 2 1`
- Reverse rest (indices 3-6): `5 6 7 1 2 3 4`
- Result: `[5, 6, 7, 1, 2, 3, 4]`. Matches!

### 2. Extra Array
Create a new array and place elements at `(i + k) % n`. Costs $O(n)$ space.

### 3. Cyclic Replacements
Move elements in cycles. More complex to implement correctly.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$. Each element is reversed twice.
- **Space Complexity:** $O(1)$. In-place.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};
```

### Python
```python
class Solution:
    def rotate(self, nums: List[int], k: int) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        k %= len(nums)
        self.reverse(nums, 0, len(nums) - 1)
        self.reverse(nums, 0, k - 1)
        self.reverse(nums, k, len(nums) - 1)
        
    def reverse(self, nums, start, end):
        while start < end:
            nums[start], nums[end] = nums[end], nums[start]
            start += 1
            end -= 1
```

### Java
```java
class Solution {
    public void rotate(int[] nums, int k) {
        k %= nums.length;
        reverse(nums, 0, nums.length - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.length - 1);
    }
    
    public void reverse(int[] nums, int start, int end) {
        while (start < end) {
            int temp = nums[start];
            nums[start] = nums[end];
            nums[end] = temp;
            start++;
            end--;
        }
    }
}
```

## 🌍 Real-World Analogy
### **Shucking Cards:**
Imagine a deck of cards. "Rotating right" is like taking `k` cards from the bottom and putting them on top.
- Reversing the whole deck, then reversing the "new top" chunk and "new bottom" chunk separately achieves the same order.

## 🎯 Summary
✅ **In-Place:** Meets strict space constraints.
✅ **Modular Arithmetic:** `k % n` handles cases where `k > n`.
