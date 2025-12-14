# Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

## 🧩 Problem Statement
Given an array of integers `nums` and an integer `limit`, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to `limit`.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [8,2,4,7], limit = 4
```
#### Output:
```plaintext
2
```
#### Explanation:
All subarrays are:
[8] with len 1
[8, 2] diff |8-2| = 6 > 4 (Invalid)
[8, 2, 4] diff |8-2| = 6 > 4 (Invalid)
[8, 2, 4, 7] diff |8-2| = 6 > 4 (Invalid)
[2] with len 1
[2, 4] with max-min = 4-2 = 2 <= 4 (Valid, len 2)
[2, 4, 7] with max-min = 7-2 = 5 > 4 (Invalid)
[4] with len 1
[4, 7] with max-min = 7-4 = 3 <= 4 (Valid, len 2)
[7] with len 1
Max valid length is 2.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [10,1,2,4,7,2], limit = 5
```
#### Output:
```plaintext
4
```
#### Explanation:
The subarray [2,4,7,2] is the longest since the maximum absolute diff is |7-2| = 5 <= 5.

## 🔍 Approaches

### 1. Brute Force
Check all subarrays, find max/min in each.
- Time: $O(N^3)$. With optimization $O(N^2)$.

### 2. Two Deques (Monotonic Queues)
To know the absolute difference of a window, we need `max(window) - min(window)`.
- Use a **Decreasing Deque** to track the Maximum.
- Use an **Increasing Deque** to track the Minimum.
- Expand `right` pointer:
    - Update both deques.
    - Check condition: `maxDeque.front() - minDeque.front() <= limit`.
    - If false, shrink `left` pointer and pop elements from deques that are sliding out.
    - Update `maxLength`.

### 3. Tree Map / Sorted List
Maintain a sorted window. `last() - first() <= limit`.
- $O(N \log N)$.

### ✨ Intuition
This is a standard sliding window problem where the "validity" check is expensive ($O(K)$) if done naively. Monotonic queues reduce the max/min query to $O(1)$.
If `max - min > limit`, there is no way to make the window valid by adding elements on the right (max can grow, min can shrink, diff increases). We *must* shrink from the left to potentially drop the extreme value.

### 🔥 Algorithm Steps
1. Init `maxD` (deque) and `minD` (deque). `left = 0`.
2. Iterate `right` from `0` to `n-1`.
   - Update `maxD`: Pop back if `nums[right] > back`. Push `right`.
   - Update `minD`: Pop back if `nums[right] < back`. Push `right`.
   - While `nums[maxD.front()] - nums[minD.front()] > limit`:
     - `left++`.
     - If `maxD.front() < left`, pop front.
     - If `minD.front() < left`, pop front.
   - `res = max(res, right - left + 1)`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ (worst case deques store all elements).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        deque<int> maxD, minD;
        int left = 0, res = 0;
        
        for (int right = 0; right < nums.size(); ++right) {
            while (!maxD.empty() && nums[maxD.back()] <= nums[right]) maxD.pop_back();
            while (!minD.empty() && nums[minD.back()] >= nums[right]) minD.pop_back();
            
            maxD.push_back(right);
            minD.push_back(right);
            
            while (nums[maxD.front()] - nums[minD.front()] > limit) {
                left++;
                if (maxD.front() < left) maxD.pop_front();
                if (minD.front() < left) minD.pop_front();
            }
            res = max(res, right - left + 1);
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
    def longestSubarray(self, nums: List[int], limit: int) -> int:
        max_d = deque()
        min_d = deque()
        left = 0
        res = 0
        
        for right, num in enumerate(nums):
            while max_d and nums[max_d[-1]] <= num:
                max_d.pop()
            while min_d and nums[min_d[-1]] >= num:
                min_d.pop()
            
            max_d.append(right)
            min_d.append(right)
            
            while nums[max_d[0]] - nums[min_d[0]] > limit:
                left += 1
                if max_d[0] < left:
                    max_d.popleft()
                if min_d[0] < left:
                    min_d.popleft()
            
            res = max(res, right - left + 1)
            
        return res
```

### Java
```java
import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int longestSubarray(int[] nums, int limit) {
        Deque<Integer> maxD = new ArrayDeque<>();
        Deque<Integer> minD = new ArrayDeque<>();
        int left = 0;
        int res = 0;
        
        for (int right = 0; right < nums.length; right++) {
            while (!maxD.isEmpty() && nums[maxD.peekLast()] <= nums[right]) {
                maxD.pollLast();
            }
            while (!minD.isEmpty() && nums[minD.peekLast()] >= nums[right]) {
                minD.pollLast();
            }
            
            maxD.offerLast(right);
            minD.offerLast(right);
            
            while (nums[maxD.peekFirst()] - nums[minD.peekFirst()] > limit) {
                left++;
                if (maxD.peekFirst() < left) maxD.pollFirst();
                if (minD.peekFirst() < left) minD.pollFirst();
            }
            
            res = Math.max(res, right - left + 1);
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Temperature Stability:**
You want to find the longest period of days where the temperature fluctuation didn't exceed `X` degrees.
- You track the Hottest day in the window.
- You track the Coldest day in the window.
- If Hottest - Coldest > X, the period is too volatile, so you shrink the period from the start.

## 🎯 Summary
✅ **Double Monotonic Queues:** One for Max, One for Min.
✅ **Efficient:** $O(N)$ allows processing large streams of data.
