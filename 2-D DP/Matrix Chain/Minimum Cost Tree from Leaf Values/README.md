# Minimum Cost Tree From Leaf Values

## 🧩 Problem Statement
Given an array `arr` of positive integers, consider all binary trees such that:
1. Each node has either 0 or 2 children.
2. The values of `arr` correspond to the values of each **leaf** in an in-order traversal of the tree.
3. The value of each **non-leaf** node is equal to the product of the largest leaf value in its left and right subtree respectively.

Among all possible binary trees considered, return the smallest possible sum of the values of each **non-leaf** node.

### 🔹 Example 1:
#### Input:
```plaintext
arr = [6,2,4]
```
#### Output:
```plaintext
32
```
**Explanation:** 
There are two possible trees. 
The first has non-leaf node sum 36, and the second has 32.

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4

Leaf values in-order: [6, 2, 4]
1. ((6, 2), 4):
   - Internal node 1: max(6, 2) * max(4) = 6 * 4 = 24 (Left child is node with leaf 6,2; Right is 4)
   - Left subtree internal node: max(6) * max(2) = 12.
   - Total = 24 + 12 = 36.
   
2. (6, (2, 4)):
   - Internal node 1: max(6) * max(2, 4) = 6 * 4 = 24.
   - Right subtree internal node: max(2) * max(4) = 8.
   - Total = 24 + 8 = 32.

### 🔹 Example 2:
#### Input:
```plaintext
arr = [4,11]
```
#### Output:
```plaintext
44
```

## 🔍 Approaches

### 1. Monotonic Stack (Greedy - $O(N)$)
This problem is equivalent to repeatedly removing the smallest element `x` from the array and adding a cost equal to `x * min(left_neighbor, right_neighbor)`. We want to pair small numbers with their smallest available neighbor to minimize the product.
- Use a **decreasing** stack.
- Iterate through the array with value `num`.
- While `stack` is not empty and `stack.top() <= num`:
  - `mid = stack.pop()`
  - The neighbors of `mid` are the new `stack.top()` (left) and `num` (right).
  - Note: If stack is empty after pop, it only has a right neighbor.
  - `cost += mid * min(stack.top(), num)` (handle edge cases for infinity).
- Push `num` to stack.
- After loop, process remaining elements in stack (which are sorted descending). Combine them by multiplying adjacent elements.

### 2. Dynamic Programming ($O(N^3)$)
Similar to Matrix Chain Multiplication.
- `dp[i][j]` = min cost for range `arr[i...j]`.
- `maxVal[i][j]` = max value in range `arr[i...j]`.
- `dp[i][j] = min(dp[i][k] + dp[k+1][j] + maxVal[i][k] * maxVal[k+1][j])` for all split points `k`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$ for Stack approach, $O(N^3)$ for DP.
- **Space Complexity:** $O(N)$ for Stack (storage), $O(N^2)$ for DP.

## 🚀 Code Implementations

### C++
```cpp
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int res = 0;
        stack<int> st;
        st.push(INT_MAX); // Sentinel
        
        for (int num : arr) {
            while (st.top() <= num) {
                int mid = st.top();
                st.pop();
                res += mid * min(st.top(), num);
            }
            st.push(num);
        }
        
        // Process remaining elements (except sentinel)
        while (st.size() > 2) {
            int mid = st.top();
            st.pop();
            res += mid * st.top();
        }
        
        return res;
    }
};
```

### Python
```python
from typing import List

class Solution:
    def mctFromLeafValues(self, arr: List[int]) -> int:
        res = 0
        stack = [float('inf')]
        
        for num in arr:
            while stack[-1] <= num:
                mid = stack.pop()
                res += mid * min(stack[-1], num)
            stack.append(num)
            
        while len(stack) > 2:
            mid = stack.pop()
            res += mid * stack[-1]
            
        return res
```

### Java
```java
import java.util.Stack;

class Solution {
    public int mctFromLeafValues(int[] arr) {
        int res = 0;
        Stack<Integer> stack = new Stack<>();
        stack.push(Integer.MAX_VALUE);
        
        for (int num : arr) {
            while (stack.peek() <= num) {
                int mid = stack.pop();
                res += mid * Math.min(stack.peek(), num);
            }
            stack.push(num);
        }
        
        while (stack.size() > 2) {
            int mid = stack.pop();
            res += mid * stack.peek();
        }
        
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Merging Files:**
Similar to Huffman Coding/Merging Ropes, but here we can only merge adjacent items. We want to merge small items first, but since the "cost" of the new node depends on the MAX of its children (rather than SUM), we want to keep small values deep in the tree and pair them with the smallest possible neighbors.

## 🎯 Summary
✅ **Greedy Strategy:** It is always optimal to eliminate the smallest available local minimum by multiplying it with its smaller neighbor.
✅ **Stack Pattern:** Classic "next greater element" pattern usage.
