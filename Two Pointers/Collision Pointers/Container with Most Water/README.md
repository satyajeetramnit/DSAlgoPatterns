# Container With Most Water

## 🧩 Problem Statement
You are given an integer array `height` of length `n`. There are `n` vertical lines drawn such that the two endpoints of the `i-th` line are `(i, 0)` and `(i, height[i])`.

Find two lines that together with the x-axis form a container, such that the container contains the most water.

Return the maximum amount of water a container can store.

**Notice** that you may not slant the container.

### 🔹 Example 1:
#### Input:
```plaintext
height = [1,8,6,2,5,4,8,3,7]
```
#### Output:
```plaintext
49
```
#### Explanation:
The above vertical lines are represented by array `[1,8,6,2,5,4,8,3,7]`. In this case, the max area of water (blue section) the container can contain is 49.
(Lines at index 1 and 8: min(8, 7) * (8 - 1) = 7 * 7 = 49).

### 🔹 Example 2:
#### Input:
```plaintext
height = [1,1]
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Two Pointers (Greedy)
We want to maximize `Area = min(height[left], height[right]) * (right - left)`.
We start with the widest possible container (indices 0 and n-1).
To try and find a larger area, we need to overcome the reduction in width by finding taller lines.
Which pointer should we move? The one limiting the height! If we move the taller line, the area can only decrease (width decreases, height at best stays same). If we move the shorter line, we might find a taller line to compensate for the width reduction.

### ✨ Intuition
- Start with pointers at both ends.
- Calculate current area. Update max.
- Move the pointer corresponding to the shorter line inward.
- Repeat until pointers meet.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `right = n - 1`.
2. Initialize `maxArea = 0`.
3. While `left < right`:
   - Calculate `currentArea = min(height[left], height[right]) * (right - left)`.
   - Update `maxArea = max(maxArea, currentArea)`.
   - If `height[left] < height[right]`:
     - `left++`
   - Else:
     - `right--`
4. Return `maxArea`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, single pass.
- **Space Complexity:** $O(1)$, only constant extra variables.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int maxArea = 0;
        
        while (left < right) {
            int currentArea = min(height[left], height[right]) * (right - left);
            maxArea = max(maxArea, currentArea);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }
};
```

### Python
```python
class Solution:
    def maxArea(self, height: List[int]) -> int:
        l, r = 0, len(height) - 1
        res = 0
        
        while l < r:
            res = max(res, min(height[l], height[r]) * (r - l))
            if height[l] < height[r]:
                l += 1
            else:
                r -= 1
        return res
```

### Java
```java
class Solution {
    public int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int maxArea = 0;
        
        while (left < right) {
            int currentArea = Math.min(height[left], height[right]) * (right - left);
            maxArea = Math.max(maxArea, currentArea);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }
}
```

## 🌍 Real-World Analogy
### **Building a Fence:**
You have a limited amount of fencing material (width is naturally reducing as you consider closer posts). To maximize the area enclosed, you want finding the two furthest posts that are reasonably tall.
If you have a very short post on one side, keeping it is useless no matter how tall the other side is. You'd discard the short post and look for a better one further in perfectly maximizing the potential area.

## 🎯 Summary
✅ **Greedy Approach:** Always make the locally optimal choice (discard shorter line).
✅ **Two Pointers:** Efficiently scan the search space.
