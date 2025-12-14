# Count Number of Nice Subarrays

## 🧩 Problem Statement
Given an array of integers `nums` and an integer `k`. A continuous subarray is called **nice** if there are `k` odd numbers on it.

Return the number of **nice** sub-arrays.

### 🔹 Example 1:
#### Input:
```plaintext
nums = [1,1,2,1,1], k = 3
```
#### Output:
```plaintext
2
```
#### Explanation:
The only sub-arrays with 3 odd numbers are `[1,1,2,1]` and `[1,2,1,1]`.

### 🔹 Example 2:
#### Input:
```plaintext
nums = [2,4,6], k = 1
```
#### Output:
```plaintext
0
```

## 🔍 Approaches

### 1. Sliding Window (Three Pointer / Prefix Count)
Standard sliding window finds the longest/shortest subarray. Here we need to **count** them.
When the window `[left, right]` has exactly `k` odds, we can shrink `left` as long as we keep `k` odds (i.e., removing even numbers).
- This formulation is slightly complex (`while` loop inside `while` loop).

### 2. At Most K (Difference Trick)
A powerful trick for exact `k` counting problems:
$$ \text{Exactly}(k) = \text{AtMost}(k) - \text{AtMost}(k-1) $$
- **AtMost(k):** Count subarrays with $\le k$ odd numbers.
- This sub-problem is a standard sliding window.
  - Expand `right`.
  - While `odds > k`, shrink `left`.
  - Add `right - left + 1` to total (size of window).

### ✨ Intuition
Counting "at most" is easier because monotonicity is preserved (expanding window increases count, shrinking decreases).
Total subarrays ending at `right` with valid condition is `right - left + 1`.

### 🔥 Algorithm Steps
1. Define function `atMost(k)`:
   - `left = 0`, `res = 0`, `count = 0` (odd count).
   - Iterate `right` from `0` to `n-1`.
   - If `nums[right]` is odd, `count++`.
   - While `count > k`:
     - If `nums[left]` is odd, `count--`.
     - `left++`.
   - `res += right - left + 1`.
2. Return `atMost(k) - atMost(k - 1)`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$. Each element processed twice.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

private:
    int atMost(vector<int>& nums, int k) {
        int left = 0, res = 0, count = 0;
        for (int right = 0; right < nums.size(); right++) {
            if (nums[right] % 2 != 0) {
                count++;
            }
            while (count > k) {
                if (nums[left] % 2 != 0) {
                    count--;
                }
                left++;
            }
            res += right - left + 1;
        }
        return res;
    }
};
```

### Python
```python
class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        return self.atMost(nums, k) - self.atMost(nums, k - 1)

    def atMost(self, nums, k):
        left = 0
        res = 0
        count = 0
        for right in range(len(nums)):
            if nums[right] % 2 != 0:
                count += 1
            while count > k:
                if nums[left] % 2 != 0:
                    count -= 1
                left += 1
            res += right - left + 1
        return res
```

### Java
```java
class Solution {
    public int numberOfSubarrays(int[] nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

    private int atMost(int[] nums, int k) {
        int left = 0, res = 0, count = 0;
        for (int right = 0; right < nums.length; right++) {
            if (nums[right] % 2 != 0) {
                count++;
            }
            while (count > k) {
                if (nums[left] % 2 != 0) {
                    count--;
                }
                left++;
            }
            res += right - left + 1;
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Buying Fruit:**
You want to buy a bag of fruits (subarray) that contains exactly `k` apples (odds), no matter how many oranges (evens) are mixed in.
Calculating "bags with at most 3 apples" is easy: just grab fruits until you hit 4 apples, then drop from the start.
Subtracting "bags with at most 2 apples" removes the smaller/invalid bags, leaving usually exactly bags with 3.

## 🎯 Summary
✅ **AtMost Trick:** Turns "Exactly K" problems into two standard sliding window problems.
✅ **Parity Check:** Modulo 2 to identify "target" elements.
