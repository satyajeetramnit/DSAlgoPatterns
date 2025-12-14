# Sliding Window Maximum

## 🧩 Problem Statement
You are given an array of integers `nums`, there is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,3,-1,-3,5,3,6,7], k = 3
```
#### Output:
```plaintext
[3,3,5,5,6,7]
```
#### Explanation:
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

### 🔹 Example 2:
#### Input:
```plaintext
nums = [1], k = 1
```
#### Output:
```plaintext
[1]
```

## 🔍 Approaches

### 1. Brute Force
Iterate all windows, find max in each.
- Time: $O(N \cdot K)$.

### 2. Heap (Priority Queue)
Maintain a max-heap of the current window.
- Add new element: $O(\log K)$.
- Remove old element (lazy removal): Check top.
- Time: $O(N \log N)$ (worst case lazy).

### 3. Monotonic Queue (Deque)
We want to keep "candidates" for the maximum.
If we encounter a new number `x`, any number currently in the window that is **smaller than** `x` will **never** be the maximum again (because `x` is larger AND stays longer).
- Maintain a **Decreasing Deque**.
- **Add `x`**: Pop elements from back that are $< x$. Push `x`.
- **Remove old**: If the front of deque is the element sliding out index-wise, pop front.
- **Max**: The front of the deque is always the max.

### ✨ Intuition
The deque effectively stores the "peaks" of the window in descending order. The front is the highest peak. The elements behind it are "backup" peaks for when the front slides out.

### 🔥 Algorithm Steps
1. Create a `deque` `dq` (stores indices).
2. Iterate `i` from `0` to `n-1`.
   - Remove indices out of range `[i-k+1, i]`: `if dq.front() == i - k`, pop front.
   - Remove indices whose values are smaller than `nums[i]`: `while dq.back() < nums[i]`, pop back.
   - Push `i` to back.
   - If `i >= k - 1`, add `nums[dq.front()]` to result.
3. Return result.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$. Each element is pushed and popped at most once.
- **Space Complexity:** $O(K)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> res;
        for (int i = 0; i < nums.size(); ++i) {
            // Remove indices out of window
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            
            // Remove smaller numbers in k-range as they are useless
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            if (i >= k - 1) {
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};
```

### Python
```python
from collections import deque
from typing import List

class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        dq = deque()
        res = []
        
        for i, num in enumerate(nums):
            # Remove out of bounds
            if dq and dq[0] == i - k:
                dq.popleft()
            
            # Remove smaller elements
            while dq and nums[dq[-1]] < num:
                dq.pop()
            
            dq.append(i)
            
            if i >= k - 1:
                res.append(nums[dq[0]])
                
        return res
```

### Java
```java
import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        if (nums == null || k <= 0) {
            return new int[0];
        }
        int[] res = new int[nums.length - k + 1];
        int ri = 0;
        // Deque stores indices
        Deque<Integer> dq = new ArrayDeque<>();
        
        for (int i = 0; i < nums.length; i++) {
            // Remove out of range
            if (!dq.isEmpty() && dq.peekFirst() == i - k) {
                dq.pollFirst();
            }
            // Remove smaller numbers
            while (!dq.isEmpty() && nums[dq.peekLast()] < nums[i]) {
                dq.pollLast();
            }
            dq.offerLast(i);
            
            if (i >= k - 1) {
                res[ri++] = nums[dq.peekFirst()];
            }
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Hiring a Champion:**
A company wants to showcase its "Employee of the Month" for the last `k` months.
- When a new "Superstar" (high value) joins, all current employees who are less performant than the Superstar are no longer contenders for "Best in Window" because the Superstar is both better and will stay longer.
- The Superstar effectively "overshadows" them.

## 🎯 Summary
✅ **Monotonic Queue:** Maintains elements in sorted order (descending).
✅ **Optimal:** $O(N)$ vs $O(N \log N)$ (Heap) vs $O(NK)$ (Brute).
