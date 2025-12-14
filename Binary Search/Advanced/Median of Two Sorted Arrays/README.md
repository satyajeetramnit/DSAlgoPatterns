# Median of Two Sorted Arrays

## 🧩 Problem Statement
Given two sorted arrays `nums1` and `nums2` of size `m` and `n` respectively, return the **median** of the two sorted arrays.

The overall run time complexity should be **O(log (m+n))**.

### 🔹 Example 1:
#### Input:
```plaintext
nums1 = [1,3], nums2 = [2]
```
#### Output:
```plaintext
2.00000
```
#### Explanation:
Merged array = [1,2,3] and median is 2.

### 🔹 Example 2:
#### Input:
```plaintext
nums1 = [1,2], nums2 = [3,4]
```
#### Output:
```plaintext
2.50000
```
#### Explanation:
Merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

## 🔍 Approaches

### 1. Binary Search on Partition
We want to find a partition in both arrays such that:
1.  The left parts of both arrays contain approximately half of total elements.
2.  Every element in left parts <= Every element in right parts.

Let `nums1` be the smaller array (swap if needed) for efficiency.
- Cut `nums1` at `i` and `nums2` at `j`.
- Left partition has `nums1[0..i-1]` and `nums2[0..j-1]`.
- Right partition has `nums1[i..m-1]` and `nums2[j..n-1]`.
- Total elements in left = `(m + n + 1) / 2`.
- `j = (m + n + 1) / 2 - i`.

Conditions:
- `nums1[i-1] <= nums2[j]`
- `nums2[j-1] <= nums1[i]`

### ✨ Intuition
- **Median Definition:** Divides the set into two equal halves.
- By binary searching the cut position `i` on the smaller array, we implicitly determine `j`.
- If `nums1[i-1] > nums2[j]`: `i` is too far right (left part of nums1 is too big/large). Decrease `i`.
- If `nums2[j-1] > nums1[i]`: `i` is too far left. Increase `i`.
- Boundary cases: If `i=0` or `i=m`, use `-infinity` or `+infinity`.

### 🔥 Algorithm Steps
1.  Ensure `nums1` is the smaller array (size `m <= n`).
2.  `left = 0`, `right = m`.
3.  While `left <= right`:
    - `partition1 = (left + right) / 2`.
    - `partition2 = (m + n + 1) / 2 - partition1`.
    - Get `left1`, `right1`, `left2`, `right2` (handle edges with `INT_MIN`/`INT_MAX`).
    - If `left1 <= right2` and `left2 <= right1`:
        - Found correct partition.
        - If `m + n` is even: `avg(max(left1, left2), min(right1, right2))`.
        - If `m + n` is odd: `max(left1, left2)`.
    - Else if `left1 > right2`: `right = partition1 - 1`.
    - Else: `left = partition1 + 1`.

### 🏛️ Visual Logic: Partitioning the "Merged" Array

We want to cut `nums1` and `nums2` such that the Left Half has exactly `Half` elements.
Nums1: `[1, 3, 8, 9, 15]`, Nums2: `[7, 11, 18, 19, 21, 25]`
Total: 11. Half = 6.

#### Step 1: Initial Random Cut
- **Cut Nums1** at index 2 (between 3 and 8). Left1: `[1, 3]`. Right1: `[8...]`.
- **Implied Cut Nums2** (need size 6 total) -> Cut at index 4 (6 - 2 = 4).
- **Left2**: `[7, 11, 18, 19]`. **Right2**: `[21...]`.
- **Check Cross Conditions**:
  - `L1(3) <= R2(21)` ? Yes.
  - `L2(19) <= R1(8)` ? **NO**. (19 > 8).
- **Diagnosis**: `L2` is too big, `L1` is too small.
- **Action**: Move `nums1` cut to the **Right** (include more small numbers from `nums1`).

#### Step 2: Adjust Cut Correctly
- **Cut Nums1** at index 3 (between 8 and 9). Left1: `[1, 3, 8]`.
- **Implied Cut Nums2** at index 3 (6 - 3 = 3). Left2: `[7, 11, 18]`.
- **Check Cross Conditions**:
  - `L1(8) <= R2(19)` ? Yes.
  - `L2(18) <= R1(9)` ? **NO**. (18 > 9).
- **Action**: Move `nums1` cut Right.

#### Step 3: Final Valid Partition
- **Cut Nums1** at index 4 (between 9 and 15). Left1: `[1, 3, 8, 9]`.
- **Implied Cut Nums2** at index 2 (6 - 4 = 2). Left2: `[7, 11]`.
- **Check**:
  - `L1(9) <= R2(18)` ? Yes.
  - `L2(11) <= R1(15)` ? Yes.
- **Result**: Median is `max(L1, L2) = max(9, 11) = 11` (for odd total).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(\log(\min(m, n)))$.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size();
        int n = nums2.size();
        int left = 0, right = m;

        while (left <= right) {
            int partition1 = (left + right) / 2;
            int partition2 = (m + n + 1) / 2 - partition1;

            int maxLeft1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
            int minRight1 = (partition1 == m) ? INT_MAX : nums1[partition1];

            int maxLeft2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
            int minRight2 = (partition2 == n) ? INT_MAX : nums2[partition2];

            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                if ((m + n) % 2 == 0) {
                    return (max(maxLeft1, maxLeft2) + min(minRight1, minRight2)) / 2.0;
                } else {
                    return max(maxLeft1, maxLeft2);
                }
            } else if (maxLeft1 > minRight2) {
                right = partition1 - 1;
            } else {
                left = partition1 + 1;
            }
        }
        return 0.0;
    }
};
```

### Python
```python
import sys

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        if len(nums1) > len(nums2):
            return self.findMedianSortedArrays(nums2, nums1)
        
        m, n = len(nums1), len(nums2)
        left, right = 0, m
        
        while left <= right:
            partitionX = (left + right) // 2
            partitionY = (m + n + 1) // 2 - partitionX
            
            maxLeftX = float('-inf') if partitionX == 0 else nums1[partitionX - 1]
            minRightX = float('inf') if partitionX == m else nums1[partitionX]
            
            maxLeftY = float('-inf') if partitionY == 0 else nums2[partitionY - 1]
            minRightY = float('inf') if partitionY == n else nums2[partitionY]
            
            if maxLeftX <= minRightY and maxLeftY <= minRightX:
                if (m + n) % 2 == 0:
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2
                else:
                    return max(maxLeftX, maxLeftY)
            elif maxLeftX > minRightY:
                right = partitionX - 1
            else:
                left = partitionX + 1
        return 0.0
```

### Java
```java
class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if (nums1.length > nums2.length) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.length;
        int n = nums2.length;
        int left = 0, right = m;

        while (left <= right) {
            int partition1 = (left + right) / 2;
            int partition2 = (m + n + 1) / 2 - partition1;

            int maxLeft1 = (partition1 == 0) ? Integer.MIN_VALUE : nums1[partition1 - 1];
            int minRight1 = (partition1 == m) ? Integer.MAX_VALUE : nums1[partition1];

            int maxLeft2 = (partition2 == 0) ? Integer.MIN_VALUE : nums2[partition2 - 1];
            int minRight2 = (partition2 == n) ? Integer.MAX_VALUE : nums2[partition2];

            if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
                if ((m + n) % 2 == 0) {
                    return (Math.max(maxLeft1, maxLeft2) + Math.min(minRight1, minRight2)) / 2.0;
                } else {
                    return Math.max(maxLeft1, maxLeft2);
                }
            } else if (maxLeft1 > minRight2) {
                right = partition1 - 1;
            } else {
                left = partition1 + 1;
            }
        }
        return 0.0;
    }
}
```

## 🌍 Real-World Analogy
### **Distributed Database Queries:**
You have two huge, sorted logs of timestamps from Server A and Server B. You want to find the median timestamp across both servers to analyze latency.
- Merging them (`O(m+n)`) is too slow and requires too much memory if logs are massive.
- The partition approach allows you to just "peek" at specific indices in both logs without fetching the whole dataset, drastically reducing I/O.


### **Merging Two Decks of Cards:**
You have two sorted stacks of cards. You want to cut both stacks so that the pile on the left contains the smaller half of all cards.
- You can't just count; you have to find the "cut point" where the largest card in the left pile is $\le$ smallest card in the right pile.

## 🎯 Summary
✅ **Key Insight:** Partitioning into two equal-sized halves.
✅ **Binary Search on Smaller Array:** Optimizes complexity to $O(\log(\min(m, n)))$.
