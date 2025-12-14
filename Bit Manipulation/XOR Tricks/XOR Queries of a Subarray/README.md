# XOR Queries of a Subarray

## 🧩 Problem Statement
You are given an array `arr` of positive integers. You are also given the array `queries` where `queries[i] = [left_i, right_i]`.

For each query `i` compute the **XOR** of elements from `left_i` to `right_i` (that is, `arr[left_i] ^ arr[left_i + 1] ^ ... ^ arr[right_i]`).

Return an array `answer` where `answer[i]` is the answer to the `i`-th query.

### 🔹 Example 1:
#### Input:
```plaintext
arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3],[3,3]]
```
#### Output:
```plaintext
[2,7,14,8]
```
**Explanation:** 
- `[0,1] = 1 ^ 3 = 2`
- `[1,2] = 3 ^ 4 = 7`
- `[0,3] = 1 ^ 3 ^ 4 ^ 8 = 14`
- `[3,3] = 8`

### 🔹 Example 2:
#### Input:
```plaintext
arr = [4,8,2,10], queries = [[2,3],[1,3],[0,0],[0,3]]
```
#### Output:
```plaintext
[8,0,4,4]
```

## 🔍 Approaches

### 1. Prefix XOR (Prefix Sum Variation)
- **Concept:** Similar to Range Sum Queries, we can use a Prefix XOR array.
- **Why?** $A \oplus A = 0$.
  - Let `P[i] = arr[0] ^ arr[1] ^ ... ^ arr[i]`.
  - To find `XOR(L, R)`:
    - We know `P[R] = XOR(0, R)`
    - We know `P[L-1] = XOR(0, L-1)`
    - `P[R] ^ P[L-1] = (XOR(0, L-1) ^ XOR(L, R)) ^ XOR(0, L-1)`
    - Since `XOR(0, L-1) ^ XOR(0, L-1) = 0`, we are left with `XOR(L, R)`.
- **Formula:** `query(L, R) = P[R] ^ P[L-1]` (if $L > 0$, else `P[R]`).
- **Algorithm:**
  1. Compute prefix XOR array `P` in $O(N)$.
  2. Answer each query in $O(1)$.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$ to build prefix, $O(Q)$ for queries. Total $O(N + Q)$.
- **Space Complexity:** $O(N)$ for prefix array (can be $O(1)$ if modifying `arr` in-place).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size();
        // Compute prefix XOR in-place or separate array
        for (int i = 1; i < n; ++i) {
            arr[i] ^= arr[i-1];
        }
        
        vector<int> res;
        for (auto& q : queries) {
            int L = q[0], R = q[1];
            if (L > 0) res.push_back(arr[R] ^ arr[L-1]);
            else res.push_back(arr[R]);
        }
        return res;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        # Prefix XOR
        for i in range(1, len(arr)):
            arr[i] ^= arr[i-1]
            
        res = []
        for l, r in queries:
            if l > 0:
                res.append(arr[r] ^ arr[l-1])
            else:
                res.append(arr[r])
        return res
```

### Java
```java
class Solution {
    public int[] xorQueries(int[] arr, int[][] queries) {
        int n = arr.length;
        // Prefix XOR
        for (int i = 1; i < n; i++) {
            arr[i] ^= arr[i-1];
        }
        
        int[] res = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int L = queries[i][0];
            int R = queries[i][1];
            if (L > 0) res[i] = arr[R] ^ arr[L-1];
            else res[i] = arr[R];
        }
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **DNA Sequence Comparison:**
Imagine you are comparing genetic sequences where certain traits "cancel out" if they appear twice. You have a long pre-computed sequence of traits.
- To analyze a specific gene segment (subarray), you don't need to re-scan it.
- If you know the cumulative traits up to the `start` and up to the `end`, you can essentially "subtract" the prefix (using XOR) to instantly isolate the traits of the segment.

### **Digital Signal Processing:**
Applying filters or masks to chunks of data. If you have the cumulative effect processed, you can isolate the effect on a specific chunk by "subtracting" (XORing out) the previous effects.

## 🎯 Summary
✅ **Range Queries:** Always think of Prefix Sums (or Prefix XORs/Products) when dealing with range aggregations if the operation is invertible.
