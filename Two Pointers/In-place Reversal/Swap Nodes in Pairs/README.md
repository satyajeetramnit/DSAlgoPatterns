# Swap Nodes in Pairs

## 🧩 Problem Statement
Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed).

### 🔹 Example 1:
#### Input:
```plaintext
head = [1,2,3,4]
```
#### Output:
```plaintext
[2,1,4,3]
```

### 🔹 Example 2:
#### Input:
```plaintext
head = []
```
#### Output:
```plaintext
[]
```

### 🔹 Example 3:
#### Input:
```plaintext
head = [1]
```
#### Output:
```plaintext
[1]
```

## 🔍 Approaches

### 1. Iterative
We iterate through the list and swap pairs. We need to keep track of the node *before* the current pair to link it correctly.

### ✨ Intuition
- Use a `dummy` node pointing to `head`.
- `prev = dummy`.
- Current pair: `first = prev.next`, `second = first.next`.
- Swap:
  - `prev.next = second`
  - `first.next = second.next`
  - `second.next = first`
- Advance: `prev = first` (which is now the second node in the pair).

### 2. Recursive
Recursively swap the rest of the list (`head.next.next`) and then swap the current pair (`head` and `head.next`).

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, visit each node once.
- **Space Complexity:** $O(1)$ for iterative, $O(n)$ for recursive.

## 🚀 Code Implementations

### C++
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* prev = dummy;
        ListNode* curr = head;
        
        while (curr && curr->next) {
            ListNode* nextPair = curr->next->next;
            ListNode* second = curr->next;
            
            // Swap
            second->next = curr;
            curr->next = nextPair;
            prev->next = second;
            
            // Advance
            prev = curr;
            curr = nextPair;
        }
        return dummy->next;
    }
};
```

### Python
```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        prev = dummy
        curr = head
        
        while curr and curr.next:
            # save
            nextPair = curr.next.next
            second = curr.next
            
            # reverse
            second.next = curr
            curr.next = nextPair
            prev.next = second
            
            # update
            prev = curr
            curr = nextPair
            
        return dummy.next
```

### Java
```java
/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode() {}
 *     ListNode(int val) { this.val = val; }
 *     ListNode(int val, ListNode next) { this.val = val; this.next = next; }
 * }
 */
class Solution {
    public ListNode swapPairs(ListNode head) {
        ListNode dummy = new ListNode(0, head);
        ListNode prev = dummy;
        ListNode curr = head;
        
        while (curr != null && curr.next != null) {
            ListNode nextPair = curr.next.next;
            ListNode second = curr.next;
            
            // Swap
            second.next = curr;
            curr.next = nextPair;
            prev.next = second;
            
            // Advance
            prev = curr;
            curr = nextPair;
        }
        return dummy.next;
    }
}
```

## 🌍 Real-World Analogy
### **Square Dancing:**
People are lined up in pairs.
- The caller shouts "Swap your partner!".
- Every pair (Person A and Person B) switches places. A moves to B's spot, B moves to A's spot.
- The line order changes from A1-B1-A2-B2... to B1-A1-B2-A2...

## 🎯 Summary
✅ **Iterative Approach:** Safe from stack overflow.
✅ **Dummy Node:** Simplifies head swap logic.
