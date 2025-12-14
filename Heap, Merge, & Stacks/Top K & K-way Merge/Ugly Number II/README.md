# Ugly Number II

## 🧩 Problem Statement
An **ugly number** is a positive integer whose prime factors are limited to `2`, `3`, and `5`.

Given an integer `n`, return the `n`th **ugly number**.

### 🔹 Example 1:
#### Input:
```plaintext
n = 10
```
#### Output:
```plaintext
12
```
#### Explanation:
`[1, 2, 3, 4, 5, 6, 8, 9, 10, 12]` is the sequence of the first 10 ugly numbers.

### 🔹 Example 2:
#### Input:
```plaintext
n = 1
```
#### Output:
```plaintext
1
```
#### Explanation:
1 has no prime factors, therefore all of its prime factors are limited to 2, 3, and 5.

## 🔍 Approaches

### 1. Min-Heap ($O(N \log N)$)
- **Concept:** Generate ugly numbers in order.
- **Algorithm:**
  - Start with Heap containing `[1]`.
  - Use a Set to track visited numbers to avoid duplicates.
  - Loop `n` times:
    - Pop smallest `x`.
    - Result = `x`.
    - Push `x*2`, `x*3`, `x*5` if not visited.
- **Complexity:** $O(N \log(\text{heap size}))$. Heap size grows with N.

### 2. Dynamic Programming (Three Pointers) ($O(N)$)
- **Concept:** We want to generate the next ugly number by multiplying an existing ugly number by 2, 3, or 5.
- **Algorithm:**
  - `dp` array stores ugly numbers in order. `dp[0] = 1`.
  - Maintain 3 pointers `p2`, `p3`, `p5`, pointing to indices in `dp`.
  - Next ugly number is `min(dp[p2]*2, dp[p3]*3, dp[p5]*5)`.
  - If `next == dp[p2]*2`, increment `p2`. Same for p3, p5.
  - This handles duplicates naturally (if `2*3 == 6` and `3*2 == 6`, both pointers increment).

We will implement the **DP / Three Pointers** approach as it is optimal $O(N)$.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$.
- **Space Complexity:** $O(N)$ to store `dp` array.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n);
        dp[0] = 1;
        int p2 = 0, p3 = 0, p5 = 0;
        
        for (int i = 1; i < n; i++) {
            int next2 = dp[p2] * 2;
            int next3 = dp[p3] * 3;
            int next5 = dp[p5] * 5;
            
            dp[i] = min({next2, next3, next5});
            
            if (dp[i] == next2) p2++;
            if (dp[i] == next3) p3++;
            if (dp[i] == next5) p5++;
        }
        
        return dp[n - 1];
    }
};
```

### Python
```python
class Solution:
    def nthUglyNumber(self, n: int) -> int:
        dp = [0] * n
        dp[0] = 1
        p2 = p3 = p5 = 0
        
        for i in range(1, n):
            next2 = dp[p2] * 2
            next3 = dp[p3] * 3
            next5 = dp[p5] * 5
            
            dp[i] = min(next2, next3, next5)
            
            if dp[i] == next2:
                p2 += 1
            if dp[i] == next3:
                p3 += 1
            if dp[i] == next5:
                p5 += 1
                
        return dp[n - 1]
```

### Java
```java
class Solution {
    public int nthUglyNumber(int n) {
        int[] dp = new int[n];
        dp[0] = 1;
        int p2 = 0, p3 = 0, p5 = 0;
        
        for (int i = 1; i < n; i++) {
            int next2 = dp[p2] * 2;
            int next3 = dp[p3] * 3;
            int next5 = dp[p5] * 5;
            
            dp[i] = Math.min(next2, Math.min(next3, next5));
            
            if (dp[i] == next2) p2++;
            if (dp[i] == next3) p3++;
            if (dp[i] == next5) p5++;
        }
        
        return dp[n - 1];
    }
}
```

## 🌍 Real-World Analogy
### **Merging Queues:**
Imagine 3 manufacturing lines. Line A multiplies previous products by 2, Line B by 3, Line C by 5. They all feed into a sorted conveyor belt. To find the next product on the belt, you look at the cheapest output from A, B, or C that hasn't been placed on the belt yet.

## 🎯 Summary
✅ **3-Pointer DP:** Constant time calculation per number.
