# Find is Mountain Array

## 🧩 Problem Statement
You may recall that an array `arr` is a **mountain array** if and only if:
- `arr.length >= 3`
- There exists some `i` with `0 < i < arr.length - 1` such that:
  - `arr[0] < arr[1] < ... < arr[i - 1] < arr[i]`
  - `arr[i] > arr[i + 1] > ... > arr[arr.length - 1]`

Given a mountain array `mountainArr`, return the **minimum** `index` such that `mountainArr.get(index) == target`. If such an index does not exist, return `-1`.

You cannot access the mountain array directly. You may only access the array using a `MountainArray` interface:
- `MountainArray.get(k)` returns the element of the array at index `k` (0-indexed).
- `MountainArray.length()` returns the length of the array.

Submissions making more than `100` calls to `MountainArray.get` will be judged *Wrong Answer*.

### 🔹 Example 1:
#### Input:
```plaintext
array = [1,2,3,4,5,3,1], target = 3
```
#### Output:
```plaintext
2
```
#### Explanation:
3 exists in the array, at index 2 and index 5. Return the minimum index, which is 2.

### 🔹 Example 2:
#### Input:
```plaintext
array = [0,1,2,4,2,1], target = 3
```
#### Output:
```plaintext
-1
```

## 🔍 Approaches

### 1. Triple Binary Search
Since we need to find the target in `O(log n)` or with limited calls, linear scan is out.
The array is bitonic (increases then decreases).
1.  **Find the Peak:** Use Binary Search to find the index of the peak element.
2.  **Search Left (Ascending):** Binary Search on `[0, peak]`. If found, return index.
3.  **Search Right (Descending):** Binary Search on `[peak + 1, n - 1]`. If found, return index.
4.  If not found in either, return `-1`.

### ✨ Intuition
- **Finding Peak:** Pattern: `arr[i] < arr[i+1]` means we are on the ascending slope. `arr[i] > arr[i+1]` means descending (or peak).
- **Ascending Search:** Standard Binary Search.
- **Descending Search:** "Reverse" Binary Search (if `mid > target`, go right).

### 🔥 Algorithm Steps
1.  **Find Peak:**
    - `left = 0`, `right = n - 1`.
    - While `left < right`:
      - `mid = left + (right - left) / 2`.
      - If `get(mid) < get(mid+1)`: `left = mid + 1` (peak is to the right).
      - Else: `right = mid` (peak is at `mid` or left).
    - `peak = left`.
2.  **Search Ascending:**
    - `binarySearch(0, peak, target, ascending=true)`.
    - If found, return it (this is minimal index).
3.  **Search Descending:**
    - `binarySearch(peak + 1, n - 1, target, ascending=false)`.
4.  Return result.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log n)$. Three binary searches.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray {
  public:
    int get(int index);
    int length();
};

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        // 1. Find Peak
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;

        // 2. Search Left (Ascending)
        left = 0; right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val < target) left = mid + 1;
            else right = mid - 1;
        }

        // 3. Search Right (Descending)
        left = peak + 1; right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val > target) left = mid + 1; // Reverse logic
            else right = mid - 1;
        }

        return -1;
    }
};
```

### Python
```python
# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
#class MountainArray:
#    def get(self, index: int) -> int:
#    def length(self) -> int:

class Solution:
    def findInMountainArray(self, target: int, mountain_arr: 'MountainArray') -> int:
        n = mountain_arr.length()
        
        # 1. Find Peak
        left, right = 0, n - 1
        while left < right:
            mid = (left + right) // 2
            if mountain_arr.get(mid) < mountain_arr.get(mid + 1):
                left = mid + 1
            else:
                right = mid
        peak = left
        
        # 2. Search Left
        left, right = 0, peak
        while left <= right:
            mid = (left + right) // 2
            val = mountain_arr.get(mid)
            if val == target:
                return mid
            elif val < target:
                left = mid + 1
            else:
                right = mid - 1
                
        # 3. Search Right
        left, right = peak + 1, n - 1
        while left <= right:
            mid = (left + right) // 2
            val = mountain_arr.get(mid)
            if val == target:
                return mid
            elif val > target: # Reverse logic
                left = mid + 1
            else:
                right = mid - 1
                
        return -1
```

### Java
```java
/**
 * // This is MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface MountainArray {
 *     public int get(int index);
 *     public int length();
 * }
 */
class Solution {
    public int findInMountainArray(int target, MountainArray mountainArr) {
        int n = mountainArr.length();
        
        // 1. Find Peak
        int left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int peak = left;
        
        // 2. Search Left
        left = 0; right = peak;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val < target) left = mid + 1;
            else right = mid - 1;
        }
        
        // 3. Search Right
        left = peak + 1; right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int val = mountainArr.get(mid);
            if (val == target) return mid;
            if (val > target) left = mid + 1; // Reverse
            else right = mid - 1;
        }
        
        return -1;
    }
}
```

## 🌍 Real-World Analogy
### **Climbing a Hill:**
You are searching for a specific elevation mark on a hill.
- The path goes Up, reaches a Peak, then goes Down.
- You first find where the Peak is.
- Then you check the path going up. "Did I pass 500m on the way up?"
- If not, check the path going down. "Did I pass 500m on the way down?"

## 🎯 Summary
✅ **Decomposition:** Break into sub-problems: Find Peak -> Binary Search Ascending -> Binary Search Descending.
✅ **Reverse Logic:** Remember the condition flips for descending arrays.
