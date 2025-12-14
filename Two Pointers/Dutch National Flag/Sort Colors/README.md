# Sort Colors

## 🧩 Problem Statement
Given an array `nums` with `n` objects colored red, white, or blue, sort them **in-place** so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers `0`, `1`, and `2` to represent the color red, white, and blue, respectively.

You must solve this problem without using the library's sort function.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [2,0,2,1,1,0]
```
#### Output:
```plaintext
[0,0,1,1,2,2]
```

### 🔹 Example 2:
#### Input:
```plaintext
nums = [2,0,1]
```
#### Output:
```plaintext
[0,1,2]
```

## 🔍 Approaches

### 1. Counting Sort (Two Pass)
Count the number of 0s, 1s, and 2s. Then rewrite the array.

### 2. Dutch National Flag Algorithm (One Pass)
We use three pointers to divide the array into four sections:
- `[0, low-1]`: 0s (Red)
- `[low, mid-1]`: 1s (White)
- `[mid, high]`: Unknown
- `[high+1, n-1]`: 2s (Blue)

### ✨ Intuition
- `low` tracks the boundary for 0s.
- `mid` traverses the array.
- `high` tracks the boundary for 2s.
- When `nums[mid]` is 0: swap with `nums[low]`, increment both `low` and `mid`.
- When `nums[mid]` is 1: just increment `mid` (it's in the correct place for now).
- When `nums[mid]` is 2: swap with `nums[high]`, decrement `high` (don't increment `mid` yet, as the swapped element needs checking).

### 🔥 Algorithm Steps
1. Initialize `low = 0`, `mid = 0`, `high = n - 1`.
2. While `mid <= high`:
   - If `nums[mid] == 0`:
     - Swap `nums[mid]` and `nums[low]`.
     - `low++`, `mid++`.
   - Else if `nums[mid] == 1`:
     - `mid++`.
   - Else (`nums[mid] == 2`):
     - Swap `nums[mid]` and `nums[high]`.
     - `high--`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, one pass.
- **Space Complexity:** $O(1)$, in-place.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0, mid = 0, high = nums.size() - 1;
        
        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums[mid], nums[low]);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                swap(nums[mid], nums[high]);
                high--;
            }
        }
    }
};
```

### Python
```python
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        low, mid, high = 0, 0, len(nums) - 1
        
        while mid <= high:
            if nums[mid] == 0:
                nums[low], nums[mid] = nums[mid], nums[low]
                low += 1
                mid += 1
            elif nums[mid] == 1:
                mid += 1
            else:
                nums[high], nums[mid] = nums[mid], nums[high]
                high -= 1
```

### Java
```java
class Solution {
    public void sortColors(int[] nums) {
        int low = 0, mid = 0, high = nums.length - 1;
        
        while (mid <= high) {
            if (nums[mid] == 0) {
                swap(nums, mid, low);
                low++;
                mid++;
            } else if (nums[mid] == 1) {
                mid++;
            } else {
                swap(nums, mid, high);
                high--;
            }
        }
    }
    
    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}
```

## 🌍 Real-World Analogy
### **Sorting Laundry:**
You have a pile of clothes: Red, White, and Blue.
- You stand in the middle (`mid`) picking up clothes.
- If it's Red, throw it to the left pile (`low`).
- If it's White, leave it in the middle.
- If it's Blue, throw it to the right pile (`high`).

## 🎯 Summary
✅ **One Pass:** Efficient O(n).
✅ **Partitioning:** Classic partitioning logic used in QuickSort.
