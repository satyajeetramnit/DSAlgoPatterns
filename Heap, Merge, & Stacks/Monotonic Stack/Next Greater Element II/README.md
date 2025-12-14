# Next Greater Element II

## 🧩 Problem Statement
Given a **circular** integer array `nums` (i.e., the next element of `nums[nums.length - 1]` is `nums[0]`), return the **next greater number** for every element in `nums`.

The **next greater number** of a number `x` is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, return `-1` for this number.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,2,1]
```
#### Output:
```plaintext
[2,-1,2]
```
#### Explanation:
- The first 1's next greater number is 2.
- The number 2 can't find next greater number.
- The second 1's next greater number needs to search circularly, which is also 2.

## 🔍 Approaches

### 1. Monotonic Decreasing Stack + Loop Twice ($O(N)$)
- **Concept:** Circular array simulation.
- **Trick:** Iterate `2 * n` times but use indices modulo `n` (`i % n`).
- **Algorithm:**
  - Initialize result array with `-1`.
  - Loop `i` from `0` to `2 * n - 1`.
  - While stack not empty AND `nums[i % n] > nums[stack.top()]`:
    - `idx = stack.pop()`.
    - `result[idx] = nums[i % n]`.
  - Push `i % n` to stack (only if `i < n` to save space, but logically pushing all works if we filter result indices). Actually, we only care about filling result for indices `0` to `n-1`. So we can always push `i % n`.
- **Optimization:** We only need to push to stack if `i < n`. If `i >= n`, we are just using the elements to pop from stack, no need to push them again as we won't find their NGE in the second pass for "new" purposes.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ for stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> st; // stores indices
        
        for (int i = 0; i < 2 * n; i++) {
            while (!st.empty() && nums[i % n] > nums[st.top()]) {
                res[st.top()] = nums[i % n];
                st.pop();
            }
            if (i < n) st.push(i);
        }
        
        return res;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [-1] * n
        stack = [] # stores indices
        
        for i in range(2 * n):
            idx = i % n
            while stack and nums[idx] > nums[stack[-1]]:
                res[stack.pop()] = nums[idx]
            if i < n:
                stack.append(idx)
                
        return res
```

### Java
```java
import java.util.Stack;
import java.util.Arrays;

class Solution {
    public int[] nextGreaterElements(int[] nums) {
        int n = nums.length;
        int[] res = new int[n];
        Arrays.fill(res, -1);
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < 2 * n; i++) {
            int idx = i % n;
            while (!stack.isEmpty() && nums[idx] > nums[stack.peek()]) {
                res[stack.pop()] = nums[idx];
            }
            if (i < n) stack.push(idx);
        }
        
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Circular Buffet:**
You are sitting at a round table looking for a dish spicier than yours. If you don't find one clockwise until you reach the end, you continue past the start (loop) to check the dishes you missed before you.

## 🎯 Summary
✅ **Double Loop Simulation:** `2 * N` traversal handles circularity elegantly.
