# Single Number Series

## 🧩 Problem Statement

### I. Single Number
Given a **non-empty** array of integers `nums`, every element appears **twice** except for one. Find that single one.
You must implement a solution with a linear runtime complexity and use only constant extra space.

### II. Single Number II
Given an integer array `nums` where every element appears **three times** except for one, which appears exactly once. Find the single element and return it.
You must implement a solution with a linear runtime complexity and use only constant extra space.

### III. Single Number III
Given an integer array `nums`, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. You can return the answer in any order.
You must write an algorithm that runs in linear runtime complexity and uses only constant extra space.

---

## 🔍 Approaches

### 1. XOR Operation (Single Number I)
- **Property:** `a ^ a = 0` and `a ^ 0 = a`.
- **Logic:** XOR-ing all numbers together will cancel out the ones appearing twice, leaving the unique number.
- **Complexity:** $O(N)$ Time, $O(1)$ Space.

### 2. Bit Counting / Logic Gate (Single Number II)
- **Counting:** Count the number of set bits at each position $i$ across all numbers. `(sum_bit_i) % 3` will be the $i$-th bit of the unique number.
- **Logic Gate Optimization (Ones & Twos):**
  - Maintain `ones` (bits that appeared 1st time) and `twos` (bits that appeared 2nd time).
  - `ones` stores bits that have appeared $1 \pmod 3$ times.
  - `twos` stores bits that have appeared $2 \pmod 3$ times.
  - **Transitions:**
    - `ones = (ones ^ num) & ~twos`
    - `twos = (twos ^ num) & ~ones`
- **Complexity:** $O(N)$ Time, $O(1)$ Space.

### 3. XOR & Rightmost Set Bit (Single Number III)
- **XOR All:** `xor_all = n1 ^ n2 ^ ...`. The result is the XOR of the two unique numbers `x` and `y`.
- **Diff Bit:** Find any bit that is set in `xor_all` (e.g., rightmost set bit: `mask = xor_all & -xor_all`). This bit MUST be set in one of the unique numbers and unset in the other.
- **Partition:** Split the array into two groups based on whether this bit is set or not.
- **Solve:** XOR-ing the first group gives `x`, and the second group gives `y` (since duplicates still cancel out within each group).
- **Complexity:** $O(N)$ Time, $O(1)$ Space.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    // Single Number I
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int n : nums) res ^= n;
        return res;
    }

    // Single Number II
    int singleNumberII(vector<int>& nums) {
        int ones = 0, twos = 0;
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }

    // Single Number III
    vector<int> singleNumberIII(vector<int>& nums) {
        // Use long long to avoid overflow when computing -diff
        long long diff = 0;
        for (int n : nums) diff ^= n;
        
        diff &= -diff; // Get rightmost set bit
        
        vector<int> res(2, 0);
        for (int n : nums) {
            if (n & diff) res[0] ^= n;
            else res[1] ^= n;
        }
        return res;
    }
};
```

### Python
```python
from typing import List

class Solution:
    # Single Number I
    def singleNumber(self, nums: List[int]) -> int:
        res = 0
        for n in nums:
            res ^= n
        return res

    # Single Number II
    def singleNumberII(self, nums: List[int]) -> int:
        ones, twos = 0, 0
        for num in nums:
            ones = (ones ^ num) & ~twos
            twos = (twos ^ num) & ~ones
        return ones

    # Single Number III
    def singleNumberIII(self, nums: List[int]) -> List[int]:
        xor_all = 0
        for n in nums:
            xor_all ^= n
            
        # Get rightmost set bit
        diff = xor_all & -xor_all
        
        res = [0, 0]
        for n in nums:
            if n & diff:
                res[0] ^= n
            else:
                res[1] ^= n
        return res
```

### Java
```java
class Solution {
    // Single Number I
    public int singleNumber(int[] nums) {
        int res = 0;
        for (int n : nums) res ^= n;
        return res;
    }

    // Single Number II
    public int singleNumberII(int[] nums) {
        int ones = 0, twos = 0;
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }

    // Single Number III
    public int[] singleNumberIII(int[] nums) {
        int diff = 0;
        for (int n : nums) diff ^= n;
        
        diff &= -diff;
        
        int[] res = new int[2];
        for (int n : nums) {
            if ((n & diff) == 0) res[0] ^= n;
            else res[1] ^= n;
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Odd One Out:**
Imagine a dance floor where people are supposed to be in pairs (I) or trios (II). Everyone is wearing a unique colored shirt. If you overlay all the shirts (XOR), the colors that appear an even number of times cancel out (become transparent), leaving only the unique color visible.

## 🎯 Summary
✅ **XOR Magic:** $A \oplus A = 0$.
✅ **Bit Manipulation:** Using logic gates to track modulo 3 checks.
✅ **Two-Pass XOR:** Using a distinguishing bit to separate two unique numbers.
