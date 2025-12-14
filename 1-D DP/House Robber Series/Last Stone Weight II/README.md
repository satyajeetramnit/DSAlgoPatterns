# Last Stone Weight II

## 🧩 Problem Statement
You are given an array of integers `stones` where `stones[i]` is the weight of the `i-th` stone.

We are playing a game with the stones. On each turn, we choose any two stones and smash them together. Suppose the stones have weights `x` and `y` with `x <= y`. The result of this smash is:
- If `x == y`, both stones are destroyed.
- If `x != y`, the stone of weight `x` is destroyed, and the stone of weight `y` has new weight `y - x`.

At the end of the game, there is at most one stone left.
Return the smallest possible weight of the left stone. If there are no stones left, return 0.

### 🔹 Example 1:
#### Input:
```plaintext
stones = [2,7,4,1,8,1]
```
#### Output:
```plaintext
1
```
**Explanation:** 
- Combine 2 and 4 to get 2, so the array converts to [2,7,1,8,1] then,
- Combine 7 and 8 to get 1, so the array converts to [2,1,1,1] then,
- Combine 2 and 1 to get 1, so the array converts to [1,1,1] then,
- Combine 1 and 1 to get 0, so the array converts to [1], then that's the optimal value.

### 🔹 Example 2:
#### Input:
```plaintext
stones = [31,26,33,21,40]
```
#### Output:
```plaintext
5
```

## 🔍 Approaches

### 1. Dynamic Programming (Subset Sum Variation)
The problem effectively asks to partition the stones into two groups $S_1$ and $S_2$ such that $|S_1 - S_2|$ is minimized.
Why? Because smashing two stones $x$ and $y$ ($y > x$) results in $y - x$. Eventually, every stone is either added or subtracted from the final result.
We want to minimize $TotalSum - 2 \cdot SubsetSum$, where $SubsetSum \le TotalSum/2$.

This transforms the problem into finding the largest `SubsetSum` that is $\le TotalSum/2$.
This is essentially the **0/1 Knapsack Problem** (or Subset Sum) with capacity `TotalSum/2`.

#### Algorithm:
1. Calculate `sum = total weight`.
2. Target capacity `C = sum / 2`.
3. Use a boolean DP array `dp` of size `C + 1` to track reachable sums.
   - `dp[0] = true`.
   - For each stone `s`:
     - Update `dp` backwards. `dp[i] = dp[i] || dp[i - s]`.
4. Find the largest `i` such that `dp[i]` is true.
5. Result is `sum - 2 * i`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \cdot S)$, where $N$ is number of stones and $S$ is the total sum.
- **Space Complexity:** $O(S)$ for the DP array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int totalSum = accumulate(stones.begin(), stones.end(), 0);
        int target = totalSum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        
        for (int stone : stones) {
            for (int j = target; j >= stone; --j) {
                if (dp[j - stone]) {
                    dp[j] = true;
                }
            }
        }
        
        for (int i = target; i >= 0; --i) {
            if (dp[i]) {
                return totalSum - 2 * i;
            }
        }
        return 0;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def lastStoneWeightII(self, stones: List[int]) -> int:
        total_sum = sum(stones)
        target = total_sum // 2
        
        # dp set containing all achievable sums <= target
        dp = {0}
        
        for stone in stones:
            new_sums = set()
            for s in dp:
                if s + stone <= target:
                    new_sums.add(s + stone)
            dp.update(new_sums)
            
        max_s1 = max(dp)
        return total_sum - 2 * max_s1
```

### Java
```java
class Solution {
    public int lastStoneWeightII(int[] stones) {
        int totalSum = 0;
        for (int s : stones) totalSum += s;
        int target = totalSum / 2;
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;
        
        for (int stone : stones) {
            for (int j = target; j >= stone; j--) {
                if (dp[j - stone]) {
                    dp[j] = true;
                }
            }
        }
        
        for (int i = target; i >= 0; i--) {
            if (dp[i]) {
                return totalSum - 2 * i;
            }
        }
        return 0;
    }
}
```

## 🌍 Real-World Analogy
### **Tug of War:**
You want to divide a group of people into two teams for Tug of War such that the strength difference is minimized. Smashing stones is like opposing forces canceling each other out.

## 🎯 Summary
✅ **Minimize Difference:** Equivalent to maximizing one subset's sum up to `Total/2`.
✅ **Subset Sum Reused:** Same logic as Partition Equal Subset Sum, just different output interpretation.
