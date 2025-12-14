# Range Sum Query - Mutable

## 🧩 Problem Statement
Given an integer array `nums`, handle multiple queries of the following types:

1. **Update**: Update the value of `nums[index]` to `val`.
2. **Sum Range**: Calculate the sum of the elements of `nums` between indices `left` and `right` **inclusive** where `left <= right`.

Implement the `NumArray` class:
- `NumArray(int[] nums)` Initializes the object with the integer array `nums`.
- `void update(int index, int val)` Updates the value of `nums[index]` to `val`.
- `int sumRange(int left, int right)` Returns the sum of the elements of `nums` between indices `left` and `right` inclusive (i.e. `nums[left] + nums[left + 1] + ... + nums[right]`).

### 🔹 Example 1:
#### Input:
```plaintext
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
```
#### Output:
```plaintext
[null, 9, null, 8]
```
#### Explanation:
1. `NumArray([1, 3, 5])`
2. `sumRange(0, 2)` -> $1 + 3 + 5 = 9$
3. `update(1, 2)` -> `nums` becomes `[1, 2, 5]`
4. `sumRange(0, 2)` -> $1 + 2 + 5 = 8$

## 🔍 Approaches

### 1. Segment Tree (Optimal)
A **Segment Tree** is a binary tree where each node represents an interval.
- **Root**: Represents the entire array range `[0, n-1]`.
- **Leaf**: Represents a single element `[i, i]`.
- **Internal Node**: Represents sum of its children (left child `[L, mid]`, right child `[mid+1, R]`).

**Operations:**
- **Build**: $O(n)$. Recursively build left and right children, then sum them up.
- **Update**: $O(\log n)$. Traverse down to the specific leaf, update it, and recalculate sums on the way up.
- **Query**: $O(\log n)$. Combine sums of relevant nodes that fully/partially overlap with the query range.

### 🏛️ Visual Logic: Segment Tree for `[1, 3, 5, 7]`

#### Step 1: Tree Structure
- **Root [0-3]**: Sum $1+3+5+7 = 16$.
- **Left [0-1]**: Sum $1+3=4$.  **Right [2-3]**: Sum $5+7=12$.
- **Leaves**: `[0]:1`, `[1]:3`, `[2]:5`, `[3]:7`.

<!-- slide -->

#### Step 2: Query Sum(0, 2)
- **Goal**: Sum indices `0` to `2`.
- **Start at Root [0-3]**: Range matches partially. Split.
- **Go Left [0-1]**: Range `[0, 1]` is fully inside `[0, 2]`. **Return 4**.
- **Go Right [2-3]**: Range `[2, 3]` partially overlaps `[0, 2]`. Split.
  - **Right->Left [2-2]**: Range `[2, 2]` fully inside. **Return 5**.
  - **Right->Right [3-3]**: Range `[3, 3]` outside. **Return 0**.
- **Total**: $4 + 5 = 9$.

<!-- slide -->

#### Step 3: Update Index 1 to 2
- **Path**: Root -> Left Child [0-1] -> Leaf [1].
- **Update Leaf [1]**: Value becomes `2`.
- **Backtrack**:
  - **Left [0-1]**: Recalculate `Leaf[0](1) + Leaf[1](2) = 3`.
  - **Root [0-3]**: Recalculate `Left(3) + Right(12) = 15`.
- **New Tree Sum**: 15.

## ⏳ Time & Space Complexity
- **Time Complexity:**
  - Build: $O(n)$
  - Update: $O(\log n)$
  - Query: $O(\log n)$
- **Space Complexity:** $O(n)$ (Tree array size is $\approx 4n$).

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
using namespace std;

class NumArray {
    vector<int> tree;
    int n;

    void build(vector<int>& nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node, start, mid);
            build(nums, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // Out of range
        }
        if (l <= start && end <= r) {
            return tree[node]; // Fully in range
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }

public:
    NumArray(vector<int>& nums) {
        n = nums.size();
        if (n > 0) {
            tree.resize(4 * n);
            build(nums, 1, 0, n - 1);
        }
    }
    
    void update(int index, int val) {
        if (n > 0) update(1, 0, n - 1, index, val);
    }
    
    int sumRange(int left, int right) {
        if (n > 0) return query(1, 0, n - 1, left, right);
        return 0;
    }
};
```

### Python
```python
from typing import List

class NumArray:
    def __init__(self, nums: List[int]):
        self.n = len(nums)
        self.tree = [0] * (4 * self.n)
        if self.n > 0:
            self.build(nums, 1, 0, self.n - 1)

    def build(self, nums, node, start, end):
        if start == end:
            self.tree[node] = nums[start]
        else:
            mid = (start + end) // 2
            self.build(nums, 2 * node, start, mid)
            self.build(nums, 2 * node + 1, mid + 1, end)
            self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]

    def update(self, index: int, val: int) -> None:
        self._update(1, 0, self.n - 1, index, val)

    def _update(self, node, start, end, idx, val):
        if start == end:
            self.tree[node] = val
        else:
            mid = (start + end) // 2
            if start <= idx <= mid:
                self._update(2 * node, start, mid, idx, val)
            else:
                self._update(2 * node + 1, mid + 1, end, idx, val)
            self.tree[node] = self.tree[2 * node] + self.tree[2 * node + 1]

    def sumRange(self, left: int, right: int) -> int:
        return self._query(1, 0, self.n - 1, left, right)

    def _query(self, node, start, end, l, r):
        if r < start or end < l:
            return 0
        if l <= start and end <= r:
            return self.tree[node]
        mid = (start + end) // 2
        p1 = self._query(2 * node, start, mid, l, r)
        p2 = self._query(2 * node + 1, mid + 1, end, l, r)
        return p1 + p2
```

### Java
```java
class NumArray {
    int[] tree;
    int n;

    public NumArray(int[] nums) {
        n = nums.length;
        if (n > 0) {
            tree = new int[4 * n];
            build(nums, 1, 0, n - 1);
        }
    }

    private void build(int[] nums, int node, int start, int end) {
        if (start == end) {
            tree[node] = nums[start];
        } else {
            int mid = (start + end) / 2;
            build(nums, 2 * node, start, mid);
            build(nums, 2 * node + 1, mid + 1, end);
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    public void update(int index, int val) {
        if (n > 0) update(1, 0, n - 1, index, val);
    }

    private void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(2 * node, start, mid, idx, val);
            } else {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }
    
    public int sumRange(int left, int right) {
        if (n > 0) return query(1, 0, n - 1, left, right);
        return 0;
    }

    private int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int p1 = query(2 * node, start, mid, l, r);
        int p2 = query(2 * node + 1, mid + 1, end, l, r);
        return p1 + p2;
    }
}
```

## 🌍 Real-World Analogy
### **Financial Portfolio value:**
Imagine you track a portfolio of stocks.
- **Update**: A stock price changes rarely (or you adjust your holdings).
- **Query**: You frequently want the total value of specific sectors (ranges of stocks in your list).
- Using a simple array, calculating sector value is $O(N)$. With a Segment Tree (or Financial Aggregation Tree), it is $O(\log N)$, allowing real-time dashboards to update instantly as prices tick.
