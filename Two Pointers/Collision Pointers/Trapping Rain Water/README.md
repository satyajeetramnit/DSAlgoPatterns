# Trapping Rain Water

## 🧩 Problem Statement
Given `n` non-negative integers representing an elevation map where the width of each bar is `1`, compute how much water it can trap after raining.

### 🔹 Example 1:
#### Input:
```plaintext
height = [0,1,0,2,1,0,1,3,2,1,2,1]
```
#### Output:
```plaintext
6
```
#### Explanation:
The above elevation map (black section) is represented by array `[0,1,0,2,1,0,1,3,2,1,2,1]`. In this case, 6 units of rain water (blue section) are being trapped.

### 🔹 Example 2:
#### Input:
```plaintext
height = [4,2,0,3,2,5]
```
#### Output:
```plaintext
9
```

## 🔍 Approaches

### 1. Two Pointers (Optimal)
We track `left` and `right` pointers, and also keep track of `leftMax` and `rightMax` encountered so far.
The amount of water at indices depends on the minimum of `leftMax` and `rightMax`.

### ✨ Intuition
- Water trapped at any index `i` is determined by `min(maxLeft, maxRight) - height[i]`.
- If `leftMax < rightMax`, then the water level at the `left` pointer is determined by `leftMax`. We don't care about `rightMax` because it's guaranteed to be larger or equal, so the bottleneck is `leftMax`.
- Similarly, if `rightMax <= leftMax`, we process the `right` side.

### 🔥 Algorithm Steps
1. Initialize `left = 0`, `right = n - 1`.
2. Initialize `leftMax = height[left]` and `rightMax = height[right]`.
3. While `left < right`:
   - If `leftMax < rightMax`:
     - `left++`
     - Update `leftMax = max(leftMax, height[left])`
     - `res += leftMax - height[left]`
   - Else:
     - `right--`
     - Update `rightMax = max(rightMax, height[right])`
     - `res += rightMax - height[right]`
4. Return `res`.

### 🏛️ Visual Logic: Two Pointers Interaction

Input: `[0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]`


#### Step 1: Initialization
- **L**: 0 (Val 0), **R**: 11 (Val 1)
- **L_Max**: 0, **R_Max**: 1
- **Compare**: `L_Max (0) < R_Max (1)`
- **Action**: Process Left.
- **Calc**: `L_Max - H[0] = 0 - 0 = 0`. Water: 0.
- **Move**: `L -> 1`.

<!-- slide -->

#### Step 2: Processing Left (Valley Start)
- **L**: 1 (Val 1), **R**: 11 (Val 1)
- **Update**: `L_Max` becomes `max(0, 1) = 1`.
- **Compare**: `L_Max (1) <= R_Max (1)` (Left is still bottleneck).
- **Move**: `L -> 2`.
- **L**: 2 (Val 0).
- **Calc**: `L_Max (1) - H[2] (0) = 1`. **Trap 1 unit**.

<!-- slide -->

#### Step 3: Rising Left Wall
- **L**: 3 (Val 2).
- **Update**: `L_Max` becomes `max(1, 2) = 2`.
- **Compare**: `L_Max (2) > R_Max (1)`.
- **Switch**: Right is now the bottleneck. Process Right.
- **Move**: `R -> 10`.

<!-- slide -->

#### Step 4: Processing Right
- **R**: 10 (Val 2).
- **Update**: `R_Max` becomes `max(1, 2) = 2`.
- **Compare**: `L_Max (2) <= R_Max (2)` (Both equal, pick L).
- **Process L**: ...and so on.


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, single pass.
- **Space Complexity:** $O(1)$, constant extra space.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;
        int left = 0, right = height.size() - 1;
        int leftMax = height[left], rightMax = height[right];
        int res = 0;
        
        while (left < right) {
            if (leftMax < rightMax) {
                left++;
                leftMax = max(leftMax, height[left]);
                res += leftMax - height[left];
            } else {
                right--;
                rightMax = max(rightMax, height[right]);
                res += rightMax - height[right];
            }
        }
        return res;
    }
};
```

### Python
```python
class Solution:
    def trap(self, height: List[int]) -> int:
        if not height: return 0
        l, r = 0, len(height) - 1
        leftMax, rightMax = height[l], height[r]
        res = 0
        
        while l < r:
            if leftMax < rightMax:
                l += 1
                leftMax = max(leftMax, height[l])
                res += leftMax - height[l]
            else:
                r -= 1
                rightMax = max(rightMax, height[r])
                res += rightMax - height[r]
        return res
```

### Java
```java
class Solution {
    public int trap(int[] height) {
        if (height == null || height.length == 0) return 0;
        int left = 0, right = height.length - 1;
        int leftMax = height[left], rightMax = height[right];
        int res = 0;
        
        while (left < right) {
            if (leftMax < rightMax) {
                left++;
                leftMax = Math.max(leftMax, height[left]);
                res += leftMax - height[left];
            } else {
                right--;
                rightMax = Math.max(rightMax, height[right]);
                res += rightMax - height[right];
            }
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Puddles on an Uneven Road:**
Imagine driving on a road with dips and bumps (Potholes).
- When it rains, water collects in the dips.
- The depth of a puddle at any point is determined by the **lower of the two highest points** surrounding that dip.
- If the road to your left goes up to 5m and to your right goes up to 3m, the water can only rise to 3m before spilling over to the right.
- The `Two Pointers` approach effectively scans from both ends to find these "spill-over" boundaries for every dip.

### **Filling a Valley:**
Imagine a mountain range. Water accumulates in the valleys.
- The amount of water a valley can hold is determined by the shorter of the two peaks surrounding it.
- If you stand on the left peak and look right, and see a taller peak, you know the water level can rise at least as high as your current peak (before overflowing to the left).


## 🎯 Summary
✅ **O(n) Time, O(1) Space:** Optimal solution.
✅ **Two Pointers:** Eliminates the need for prefix/suffix arrays ($O(n)$ space).
