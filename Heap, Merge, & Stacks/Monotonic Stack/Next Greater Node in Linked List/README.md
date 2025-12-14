# Next Greater Node In Linked List

## 🧩 Problem Statement
You are given the `head` of a linked list with `n` nodes.

For each node in the list, find the value of the **next greater node**. That is, for each node, find the value of the first node that is next to it and has a **structure.strictly larger** value. If no such node exists, return `0` for that node.

Return an integer array `answer` where `answer[i]` is the value of the next greater node of the `i`th node (1-indexed).

### 🔹 Example 1:
#### Input:
```plaintext
head = [2,1,5]
```
#### Output:
```plaintext
[5,5,0]
```
#### Explanation:
- Node 2 -> Next greater is 5.
- Node 1 -> Next greater is 5.
- Node 5 -> No greater node.

## 🔍 Approaches

### 1. Vector Conversion + Monotonic Stack ($O(N)$)
- **Concept:** Linked lists are hard to backtrack or jump around. Converting to an array (vector) simplifies the problem to standard "Next Greater Element".
- **Algorithm:**
  1. Convert Linked List to Array/Vector `vals`.
  2. Initialize `answer` with `0`.
  3. Use a stack to store indices.
  4. Iterate through `vals`. While `vals[i] > vals[stack.top()]`:
     - `idx = stack.pop()`
     - `answer[idx] = vals[i]`
  5. Push `i` to stack.
- **Why convert?** Stack needs to update *previous* indices. Arrays give $O(1)$ access to previous indices.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N)$ (one pass to convert, one pass to process).
- **Space Complexity:** $O(N)$ for array and stack.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    vector<int> nextLargerNodes(ListNode* head) {
        vector<int> vals;
        while (head) {
            vals.push_back(head->val);
            head = head->next;
        }
        
        vector<int> res(vals.size(), 0);
        stack<int> st; // stores indices
        
        for (int i = 0; i < vals.size(); i++) {
            while (!st.empty() && vals[i] > vals[st.top()]) {
                res[st.top()] = vals[i];
                st.pop();
            }
            st.push(i);
        }
        
        return res;
    }
};
```

### Python
```python
from typing import List, Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        vals = []
        curr = head
        while curr:
            vals.append(curr.val)
            curr = curr.next
            
        res = [0] * len(vals)
        stack = [] # indices
        
        for i, val in enumerate(vals):
            while stack and val > vals[stack[-1]]:
                idx = stack.pop()
                res[idx] = val
            stack.append(i)
            
        return res
```

### Java
```java
import java.util.*;

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; }
}

class Solution {
    public int[] nextLargerNodes(ListNode head) {
        List<Integer> vals = new ArrayList<>();
        while (head != null) {
            vals.add(head.val);
            head = head.next;
        }
        
        int[] res = new int[vals.size()];
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < vals.size(); i++) {
            while (!stack.isEmpty() && vals.get(i) > vals.get(stack.peek())) {
                res[stack.pop()] = vals.get(i);
            }
            stack.push(i);
        }
        
        return res;
    }
}
```

## 🌍 Real-World Analogy
### **Train Stations:**
You are on a train visiting stations [2, 1, 5]. At station 2, you wonder "What is the next station with more passengers than this one?". You have to keep checking down the line. It's easier if you have a map (array) of the whole line first than just looking out the window (linked list).

## 🎯 Summary
✅ **Convert to Array:** Simplifies Linked List stack problems significantly.
