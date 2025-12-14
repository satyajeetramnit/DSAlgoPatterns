# Maximum Width Ramp

## 🧩 Problem Statement
A **ramp** in an integer array `nums` is a pair `(i, j)` for which `i < j` and `nums[i] <= nums[j]`. The **width** of such a ramp is `j - i`.

Given an integer array `nums`, return the **maximum width** of a ramp in `nums`. If there is no ramp in `nums`, return `0`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [6,0,8,2,1,5]
```
#### Output:
```plaintext
4
```
#### Explanation:
The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5. Width = 5 - 1 = 4.

## 🔍 Approaches

### 1. Decreasing Stack + Reverse Iteration ($O(N)$)
- **Concept:** To maximize `j - i` where `A[i] <= A[j]`, we want the smallest `i` possible for a given `j`.
- **Candidates for `i`:** We only care about `i`'s that are "potential starts" of a ramp. If `A[k] < A[i]` and `k < i`, then `k` is a strictly better candidate for a start index than `i` because it's further left and smaller (easier to satisfy $\le$).
- **Algorithm:**
  1. Build a stack of indices `i` where `nums[i]` is strictly decreasing. This stack contains all candidates for the "start" of a ramp.
  2. Iterate `j` backwards from `n-1` to `0`.
  3. While `stack` is not empty and `nums[stack.top()] <= nums[j]`:
     - We found a valid ramp!
     - `width = j - stack.top()`.
     - Update max width.
     - `stack.pop()` (Because `stack.top()` will never form a *wider* ramp with any `k < j`, so we can discard it).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Each element is pushed and popped at most once.
- **Space Complexity:** $O(N)$ for the stack.

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
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        stack<int> s;
        
        for (int i = 0; i < n; i++) {
            if (s.empty() || nums[s.top()] > nums[i]) {
                s.push(i);
            }
        }
        
        int maxWidth = 0;
        for (int j = n - 1; j >= 0; j--) {
            while (!s.empty() && nums[s.top()] <= nums[j]) {
                maxWidth = max(maxWidth, j - s.top());
                s.pop();
            }
        }
        
        return maxWidth;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def maxWidthRamp(self, nums: List[int]) -> int:
        n = len(nums)
        stack = []
        
        # Build decreasing stack
        for i in range(n):
            if not stack or nums[stack[-1]] > nums[i]:
                stack.append(i)
                
        maxWidth = 0
        # Traverse backwards
        for j in range(n - 1, -1, -1):
            while stack and nums[stack[-1]] <= nums[j]:
                maxWidth = max(maxWidth, j - stack.pop())
                
        return maxWidth
```

### Java
```java
import java.util.Stack;

class Solution {
    public int maxWidthRamp(int[] nums) {
        int n = nums.length;
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < n; i++) {
            if (stack.isEmpty() || nums[stack.peek()] > nums[i]) {
                stack.push(i);
            }
        }
        
        int maxWidth = 0;
        for (int j = n - 1; j >= 0; j--) {
            while (!stack.isEmpty() && nums[stack.peek()] <= nums[j]) {
                maxWidth = Math.max(maxWidth, j - stack.pop());
            }
        }
        
        return maxWidth;
    }
}
```

## 🌍 Real-World Analogy
### **Building a Bridge:**
You want to build the widest bridge. You plant potential left pillars only if the ground is lower than previous spots (so you can support a higher connection later?). Then you start from the far right and try to connect to the leftmost possible pillar that is lower than you.

## 🎯 Summary
✅ **Preprocessing Potential Starts:** Identifying that we only need a decreasing subsequence for start indices is the key insight.
