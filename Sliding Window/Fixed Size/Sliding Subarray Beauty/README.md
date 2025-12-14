# Sliding Subarray Beauty

## 🧩 Problem Statement
Given an integer array `nums` containing `n` integers, find the **beauty** of each subarray of size `k`.

The **beauty** of a subarray is the `x-th` **smallest integer** in the subarray if it is **negative**, or `0` if there are fewer than `x` negative integers.

Return an integer array containing `n - k + 1` integers, which denote the beauty of the subarrays.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1, -1, -3, -2, 3], k = 3, x = 2
```
#### Output:
```plaintext
[-1, -2, -2]
```
#### Explanation:
1. `[1, -1, -3]`: Negatives are {-3, -1}. 2nd smallest is -1.
2. `[-1, -3, -2]`: Negatives are {-3, -2, -1}. 2nd smallest is -2.
3. `[-3, -2, 3]`: Negatives are {-3, -2}. 2nd smallest is -2.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [-1, -2, -3], k = 2, x = 1
```
#### Output:
```plaintext
[-2, -3]
```

## 🔍 Approaches

### 1. Sliding Window with Tree Map / Sorted List
Use a data structure that keeps elements sorted and supports adding/removing elements.
- `std::multiset` in C++ or `SortedList` in Python.
- Finding the x-th element takes $O(k)$ or $O(\log k)$ depending on augmentation.
- Total time: $O(n \log k)$ or $O(nk)$.

### 2. Frequency Array (Counting Sort Logic)
The problem constraints usually specify a small range for `nums[i]` (e.g., -50 to 50).
- Since the range is small ($R \approx 100$), we can use a frequency array `freq` of size `R`.
- We only care about negative numbers `[-50, -1]`.
- Maintain `freq` of numbers in the current window.
- To find the x-th smallest number:
  - Iterate from the smallest possible number (-50) upwards.
  - Subtract the count of the current number from `x`.
  - If `x <= 0`, we found the x-th smallest.
- This query takes $O(R)$ time (constant-ish).
- Sliding takes $O(1)$ time to update `freq`.
- Total time: $O(n \cdot R)$. This is very fast when $R$ is small.

### ✨ Intuition
Since we only care about the relative order of small integers, we don't need sorting. We just need to know "how many -50s, how many -49s..." via buckets.

### 🔥 Algorithm Steps
1. Create a frequency array `count` for range `[-50, 50]` (offset by +50 to make indices positive).
2. Populate `count` for the first `k` elements.
3. Function `findXth()`:
   - `count` through range `-50` to `-1`.
   - Accumulate counts. Stop when sum $\ge x$.
   - Return that number. Return 0 otherwise.
4. Iterate `i` from `k` to `n`.
   - Update `result[i-k]` using `findXth()`.
   - Remove `nums[i-k]` from `count`.
   - Add `nums[i]` to `count`.
5. Compute last window result.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n \cdot 50)$.
- **Space Complexity:** $O(1)$ (frequency array size fixed).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int count[101] = {0}; // Offset by 50. Index 0 is -50, 50 is 0.
        int n = nums.size();
        vector<int> result;
        
        for (int i = 0; i < k; i++) {
            count[nums[i] + 50]++;
        }
        
        result.push_back(findXth(count, x));
        
        for (int i = k; i < n; i++) {
            count[nums[i] + 50]++;
            count[nums[i - k] + 50]--;
            result.push_back(findXth(count, x));
        }
        return result;
    }

private:
    int findXth(int count[], int x) {
        int currentCount = 0;
        // Check only negative numbers: -50 to -1
        // Indices 0 to 49 corresponds to -50 to -1
        for (int i = 0; i < 50; i++) {
            currentCount += count[i];
            if (currentCount >= x) {
                return i - 50;
            }
        }
        return 0;
    }
};
```

### Python
```python
class Solution:
    def getSubarrayBeauty(self, nums: List[int], k: int, x: int) -> List[int]:
        count = [0] * 101 # -50 to 50
        res = []
        
        def find_xth():
            current_count = 0
            # Iterate -50 to -1
            for val in range(-50, 0):
                current_count += count[val + 50]
                if current_count >= x:
                    return val
            return 0

        # Init first window
        for i in range(k):
            count[nums[i] + 50] += 1
            
        res.append(find_xth())
        
        # Slide
        for i in range(k, len(nums)):
            count[nums[i] + 50] += 1
            count[nums[i - k] + 50] -= 1
            res.append(find_xth())
            
        return res
```

### Java
```java
class Solution {
    public int[] getSubarrayBeauty(int[] nums, int k, int x) {
        int[] count = new int[101]; // -50 to 50
        int n = nums.length;
        int[] result = new int[n - k + 1];
        
        for (int i = 0; i < k; i++) {
            count[nums[i] + 50]++;
        }
        
        result[0] = findXth(count, x);
        
        for (int i = k; i < n; i++) {
            count[nums[i] + 50]++;
            count[nums[i - k] + 50]--;
            result[i - k + 1] = findXth(count, x);
        }
        return result;
    }
    
    private int findXth(int[] count, int x) {
        int currentCount = 0;
        // Check -50 to -1 (indices 0 to 49)
        for (int i = 0; i < 50; i++) {
            currentCount += count[i];
            if (currentCount >= x) {
                return i - 50;
            }
        }
        return 0;
    }
}
```

## 🌍 Real-World Analogy
### **Grading on a Curve (Bottom Scores):**
A teacher looks at the last `k` exam papers graded.
They want to know the "2nd worst score" (x=2) in that batch to see if students are struggling, but they only care if the score is failing (negative).
Because scores are integers 0-100 (or shifted range), they just keep tally counts of each score.

## 🎯 Summary
✅ **Frequency Array:** Exploits small range of values.
✅ **Fixed Window:** Standard add/remove pattern.
