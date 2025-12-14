# Russian Doll Envelopes

## 🧩 Problem Statement
You are given a 2D array of integers `envelopes` where `envelopes[i] = [wi, hi]` represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of one envelope are strictly greater than the width and height of the other envelope.

Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

Note: You cannot rotate an envelope.

### 🔹 Example 1:
#### Input:
```plaintext
envelopes = [[5,4],[6,4],[6,7],[2,3]]
```
#### Output:
```plaintext
3
```
**Explanation:** The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4] => [6,7]).

### 🔹 Example 2:
#### Input:
```plaintext
envelopes = [[1,1],[1,1],[1,1]]
```
#### Output:
```plaintext
1
```

## 🔍 Approaches

### 1. Sorting + Longest Increasing Subsequence (LIS)
This problem is a 2D variation of LIS.
1. **Sort the envelopes:**
   - Sort primarily by width in **ascending** order.
   - If two envelopes have the same width, sort them by height in **descending** order.
2. **Apply LIS on heights:**
   - Extract the heights from the sorted envelopes.
   - Find the length of the Longest Increasing Subsequence of these heights.

**Why sort height descending for same width?**
If we have `[3, 3]` and `[3, 4]`, since `w1 == w2`, we cannot put one inside another.
If we sort width ascending and height ascending: `[3, 3], [3, 4]`. LIS on height would pick both (`3, 4`), implying `[3, 3]` fits in `[3, 4]`. This is WRONG because widths are equal.
If we sort width ascending and height descending: `[3, 4], [3, 3]`. LIS on height will pick only one, because `3` is not greater than `4`. This correctly enforces the condition that we can only pick one envelope of a specific width.

### 🏛️ Visual Logic: Why Sort Height Descending?

Consider Envelopes: `[3, 3], [3, 4], [4, 5]`


#### ❌ Incorrect Sorting: Width ASC, Height ASC
- **Sorted**: `[3, 3], [3, 4], [4, 5]`
- **Heights**: `[3, 4, 5]`
- **LIS**: `3 -> 4 -> 5` (Length 3)
- **Problem**: This implies `[3, 3]` fits in `[3, 4]`.
- **Constraint Check**: Width `3` is NOT strictly less than `3`. **INVALID**.

<!-- slide -->

#### ✅ Correct Sorting: Width ASC, Height DESC
- **Sorted**: `[3, 4], [3, 3], [4, 5]`
- **Heights**: `[4, 3, 5]`
- **LIS**: `3 -> 5` OR `4 -> 5` (Length 2)
- **Explanation**: 
  - `4` comes before `3` in the list.
  - An increasing subsequence can pick `4` OR `3` (since `3 < 4`, `3` could "extend" a previous chain ending in <3, but cannot extend `4`).
  - It CANNOT pick both `4` and `3` because `3` comes *after* `4` and is smaller.
- **Result**: Valid chain `[3, 4] -> [4, 5]` OR `[3, 3] -> [4, 5]`.


## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log N)$ due to sorting and the LIS binary search.
- **Space Complexity:** $O(N)$ for the `tails` array in LIS.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // Sort: width ascending, height descending
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });
        
        vector<int> tails;
        for (const auto& env : envelopes) {
            int h = env[1];
            auto it = lower_bound(tails.begin(), tails.end(), h);
            if (it == tails.end()) {
                tails.push_back(h);
            } else {
                *it = h;
            }
        }
        
        return tails.size();
    }
};
```

### Python
```python
from typing import List
import bisect

class Solution:
    def maxEnvelopes(self, envelopes: List[List[int]]) -> int:
        # Sort: width ascending, height descending
        # In Python, we can sort by (w, -h)
        envelopes.sort(key=lambda x: (x[0], -x[1]))
        
        tails = []
        for _, h in envelopes:
            idx = bisect.bisect_left(tails, h)
            if idx < len(tails):
                tails[idx] = h
            else:
                tails.append(h)
        return len(tails)
```

### Java
```java
import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Solution {
    public int maxEnvelopes(int[][] envelopes) {
        // Sort: width ascending, height descending
        Arrays.sort(envelopes, (a, b) -> {
            if (a[0] == b[0]) return b[1] - a[1];
            return a[0] - b[0];
        });
        
        List<Integer> tails = new ArrayList<>();
        
        for (int[] env : envelopes) {
            int h = env[1];
            int idx = Collections.binarySearch(tails, h);
            if (idx < 0) idx = -(idx + 1);
            
            if (idx == tails.size()) {
                tails.add(h);
            } else {
                tails.set(idx, h);
            }
        }
        
        return tails.size();
    }
}
```

## 🌍 Real-World Analogy
### **Nesting Boxes:**
Just like Matryoshka dolls, you can only put a box inside another if it is strictly smaller in all dimensions. To maximize the nesting, we sort by one dimension and find the longest chain in the other.

## 🎯 Summary
✅ **Sorting Trick:** Sorting one dimension allows us to reduce the problem to 1D LIS on the other dimension.
✅ **Handling Ties:** Descending sort on secondary dimension handles equal values correctly for LIS.
