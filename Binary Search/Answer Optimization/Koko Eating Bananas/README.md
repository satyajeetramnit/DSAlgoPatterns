# Koko Eating Bananas

## 🧩 Problem Statement
Koko loves to eat bananas. There are `n` piles of bananas, the `i-th` pile has `piles[i]` bananas. The guards have gone and will come back in `h` hours.

Koko can decide her bananas-per-hour eating speed of `k`. Each hour, she chooses some pile of bananas and eats `k` bananas from that pile. If the pile has less than `k` bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer `k` such that she can eat all the bananas within `h` hours.

### 🔹 Example 1:
#### Input:
```plaintext
piles = [3,6,7,11], h = 8
```
#### Output:
```plaintext
4
```
#### Explanation:
If k=4:
- Pile 3: 1 hour (eats 3)
- Pile 6: 2 hours (eats 4, then 2)
- Pile 7: 2 hours (eats 4, then 3)
- Pile 11: 3 hours (eats 4, then 4, then 3)
Total hours = 1 + 2 + 2 + 3 = 8 hours. Allowed = 8.
(Note: k=3 would take 10 hours, which is > 8).

### 🔹 Example 2:
#### Input:
```plaintext
piles = [30,11,23,4,20], h = 5
```
#### Output:
```plaintext
30
```

### 🔹 Example 3:
#### Input:
```plaintext
piles = [30,11,23,4,20], h = 6
```
#### Output:
```plaintext
23
```

## 🔍 Approaches

### 1. Binary Search on Answer
- The minimum possible speed `k` is 1.
- The maximum possible speed is `max(piles)` (eating the biggest pile in 1 hour).
- Range: `[1, max(piles)]`.
- We want to find the **minimum** `k` in this range such that `hoursneeded(k) <= h`.
- The function `hoursneeded(k)` is monotonically decreasing with `k` (faster eating -> fewer hours).

### ✨ Intuition
- If Koko eats at speed `k`, the time taken for a pile of size `p` is `ceil(p / k)`.
- Using integer arithmetic, `ceil(p / k)` is `(p + k - 1) / k`.
- Sum up the hours for all piles. If `total_hours <= h`, then speed `k` is valid.
- We try to find the smallest valid `k`.

### 🔥 Algorithm Steps
1. `left = 1`, `right = max(piles)`.
2. Binary Search:
   - `mid = left + (right - left) / 2`.
   - Calculate total hours needed with speed `mid`.
     - `hours = sum((p + mid - 1) / mid for p in piles)`.
   - If `hours <= h`:
     - This speed works. Try smaller: `right = mid - 1`.
   - Else:
     - Too slow. Need higher speed: `left = mid + 1`.
3. Return `left`.

### 🏛️ Visual Logic: Search Space Reduction

Input: `piles = [3, 6, 7, 11]`, `h = 8`. Range `[1, 11]`.


#### Step 1: Initial State
- **Range**: `[1, 11]`. Mid = `6`.
- **Calculate Hours for k=6**:
  - `ceil(3/6)=1, ceil(6/6)=1, ceil(7/6)=2, ceil(11/6)=2`.
  - Total: `6` hours.
- **Check**: `6 <= 8`. **Met SLA**.
- **Action**: 6 is fast enough. Can we go slower (save costs)?
- **New Range**: `[1, 5]`. (Discard [6, 11]).

<!-- slide -->

#### Step 2: Try Slower Speed
- **Range**: `[1, 5]`. Mid = `3`.
- **Calculate Hours for k=3**:
  - `ceil(3/3)=1, ceil(6/3)=2, ceil(7/3)=3, ceil(11/3)=4`.
  - Total: `10` hours.
- **Check**: `10 > 8`. **Missed SLA**.
- **Action**: Too slow! Need more capacity.
- **New Range**: `[4, 5]`. (Discard [1, 3]).

<!-- slide -->

#### Step 3: Refinement
- **Range**: `[4, 5]`. Mid = `4`.
- **Calculate Hours for k=4**:
  - Total: `8` hours (Calculated in problem statement).
- **Check**: `8 <= 8`. **Met SLA**.
- **Action**: 4 works. Try slower?
- **New Range**: `[4, 3]` -> Invalid.
- **Result**: **4** is the logic minimum.


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n \cdot \log(\max P))$, where $n$ is # of piles and $P$ is max pile size.
- **Space Complexity:** $O(1)$.

## 🚀 Code Implementations

### C++
```cpp
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = 0;
        for (int p : piles) right = max(right, p);
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long hours = 0;
            for (int p : piles) {
                hours += (p + mid - 1) / mid;
            }
            
            if (hours <= h) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
};
```

### Python
```python
import math

class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        left, right = 1, max(piles)
        
        while left <= right:
            k = (left + right) // 2
            hours = sum(math.ceil(p / k) for p in piles)
            
            if hours <= h:
                right = k - 1
            else:
                left = k + 1
        return left
```

### Java

```java
class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int left = 1;
        int right = 0;
        for (int p : piles) right = Math.max(right, p);
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long hours = 0;
            for (int p : piles) {
                hours += (p + mid - 1) / mid;
            }
            
            if (hours <= h) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }
}
```

## 🌍 Real-World Analogy
### **Cloud Auto-Scaling:**
Imagine you run a cloud service (Koko). You have a backlog of **Jobs** (`piles`) of varying sizes (DB queries, image processing tasks).
- **Constraint**: You must clear the entire backlog within **H hours** (SLA Deadline).
- **Variable**: You can provision a server with processing power **K** (jobs/hour).
- **Trade-off**:
  - Higher **K** = Faster processing, but **Expensive** (Over-provisioning).
  - Lower **K** = Cheaper, but might **Miss the Deadline**.
- **Objective**: Find the **Minimum K** (Cheapest Server) that guarantees meeting the SLA.


## 🎯 Summary
✅ **Ceiling Division:** `(p + k - 1) / k` is a handy integer trick for `ceil(p/k)`.
✅ **64-bit Integers:** Be careful `total hours` doesn't overflow 32-bit int (though usually `h` is widely constrained, `piles` length could make intermediate sum large).
