# Largest Rectangle in Histogram

## 🧩 Problem Statement
Given an array of integers `heights` representing the histogram's bar height where the width of each bar is `1`, return the area of the largest rectangle in the histogram.

### 🔹 Example 1:
#### Input:
```plaintext
heights = [2,1,5,6,2,3]
```
#### Output:
```plaintext
10
```
#### Explanation:
The largest rectangle has an area = 10 units.
(Height 5 and 6 form a rectangle of height 5 and width 2).

## 🔍 Approaches

### 1. Monotonic Increasing Stack ($O(N)$)
- **Concept:** For any bar `h`, the largest rectangle *using `h` as the smallest bar* extends left to the first index `i` with `heights[i] < h` and right to the first index `j` with `heights[j] < h`.
- **Width:** `(j - 1) - (i + 1) + 1` = `j - i - 1`.
- **Area:** `h * (j - i - 1)`.
- **Single Pass Logic:**
  - Maintain a stack of indices with increasing heights.
  - When we see a bar `current_h < stack_top_h`:
    - This `current_h` determines the **Right Boundary** for `stack_top_h`.
    - Pop `stack_top_h`.
    - The new `stack.top()` (after pop) is the **Left Boundary** for the popped height (since it's the closest previous element smaller than it).
    - Calculate area using `height = popped_h` and `width = current_index - stack.top() - 1`.
  - Push `current_index`.

### 🏛️ Visual Logic: Trace for `[2, 1, 5, 6, 2, 3]`

#### Step 1: Processing `2`
- **Current**: 2
- **Action**: Stack empty -> Push Index 0.
- **Stack**: `[0(2)]`
- **Explanation**: 2 is the start. No previous larger element to resolve.

<!-- slide -->

#### Step 2: Processing `1`
- **Current**: 1
- **Action**: `1 < 2` (Top).
- **Resolve**: Pop `2`. 
  - Height: 2
  - Width: `Current(1) - NewTop(-1) - 1` = `1 - (-1) - 1` = 1.
  - Area: `2 * 1 = 2`.
- **Push**: Index 1.
- **Stack**: `[1(1)]`
- **Explanation**: The bar `2` could not extend right because `1` is smaller.

<!-- slide -->

#### Step 3 & 4: Processing `5, 6`
- **Current**: 5, then 6.
- **Action**: Both > Top. Push.
- **Stack**: `[1(1), 2(5), 3(6)]`
- **Explanation**: Increasing sequence. Potential for larger rectangles builds up.

<!-- slide -->

#### Step 5: Processing `2` (Resolution)
- **Current**: 2
- **Action**: `2 < 6` (Top).
- **Resolve 6**:
  - Pop `6`. Height: 6.
  - Left Bound: `5` (Index 2). Right Bound: `2` (Index 4).
  - Width: `4 - 2 - 1 = 1`. Area: `6`.
- **Action**: `2 < 5` (New Top).
- **Resolve 5**:
  - Pop `5`. Height: 5.
  - Left Bound: `1` (Index 1). Right Bound: `2` (Index 4).
  - Width: `4 - 1 - 1 = 2`. Area: `5 * 2 = 10` (MAX!).
- **Push**: Index 4.
- **Stack**: `[1(1), 4(2)]`


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ for stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.push_back(0); // Dummy bar to flush stack
        int n = heights.size();
        stack<int> s;
        int maxArea = 0;
        
        for (int i = 0; i < n; i++) {
            while (!s.empty() && heights[i] < heights[s.top()]) {
                int h = heights[s.top()];
                s.pop();
                int w = s.empty() ? i : i - s.top() - 1;
                maxArea = max(maxArea, h * w);
            }
            s.push(i);
        }
        
        return maxArea;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        heights.append(0) # Dummy bar
        stack = [] # indices
        max_area = 0
        
        for i, h in enumerate(heights):
            while stack and h < heights[stack[-1]]:
                height = heights[stack.pop()]
                width = i if not stack else i - stack[-1] - 1
                max_area = max(max_area, height * width)
            stack.append(i)
            
        return max_area
```

### Java
```java
import java.util.Stack;

class Solution {
    public int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int maxArea = 0;
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];
            
            while (!stack.isEmpty() && h < heights[stack.peek()]) {
                int height = heights[stack.pop()];
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }
        
        return maxArea;
    }
}
```

## 🌍 Real-World Analogy
### **Finding a Building Site:**
You have a cityscape of varying heights. You want to place a giant rectangular billboard. You try to place it on top of building X. You can expand left until you hit a smaller building, and right until you hit a smaller building. Building X is the bottleneck (shortest building) in that specific range.

## 🎯 Summary
✅ **Dummy 0-Height Bar:** Ensures all elements remaining in the stack are processed at the end.
