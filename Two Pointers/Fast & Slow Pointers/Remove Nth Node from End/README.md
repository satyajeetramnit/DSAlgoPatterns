# Remove Nth Node From End of List

## 🧩 Problem Statement
Given the `head` of a linked list, remove the `n-th` node from the end of the list and return its head.

### 🔹 Example 1:
#### Input:
```plaintext
head = [1,2,3,4,5], n = 2
```
#### Output:
```plaintext
[1,2,3,5]
```

### 🔹 Example 2:
#### Input:
```plaintext
head = [1], n = 1
```
#### Output:
```plaintext
[]
```

## 🔍 Approaches

### 1. Two Pointers (One Pass)
We can use two pointers, `first` and `second`, separated by `n` nodes.
When `first` reaches the end, `second` will be exactly at the node *before* the one we want to remove.

### ✨ Intuition
- Use a `dummy` node pointing to `head` (to handle edge case where head itself is removed).
- Initialize `first = dummy`, `second = dummy`.
- Move `first` `n + 1` steps ahead. Now the gap between `first` and `second` is `n + 1`.
- Move both `first` and `second` one step at a time until `first` becomes `null`.
- At this point, `second` is at the node before the target.
- Remove the target: `second.next = second.next.next`.

### 🔥 Algorithm Steps
1. Create `dummy` node with `dummy.next = head`.
2. Set `first = dummy`, `second = dummy`.
3. Move `first` `n + 1` times forward.
4. While `first` is not null:
   - `first = first.next`
   - `second = second.next`
5. `second.next = second.next.next`
6. Return `dummy.next`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(L)$, where $L$ is length of list. We make one pass.
- **Space Complexity:** $O(1)$.

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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* first = dummy;
        ListNode* second = dummy;
        
        for (int i = 0; i <= n; i++) {
            first = first->next;
        }
        
        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }
        
        ListNode* temp = second->next;
        second->next = second->next->next;
        delete temp; // Free memory
        
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
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        dummy = ListNode(0, next=head)
        left = dummy
        right = head
        
        while n > 0 and right:
            right = right.next
            n -= 1
            
        while right:
            left = left.next
            right = right.next
            
        # delete
        left.next = left.next.next
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
    public ListNode removeNthFromEnd(ListNode head, int n) {
        ListNode dummy = new ListNode(0, head);
        ListNode first = dummy;
        ListNode second = dummy;
        
        for (int i = 0; i <= n; i++) {
            first = first.next;
        }
        
        while (first != null) {
            first = first.next;
            second = second.next;
        }
        
        second.next = second.next.next;
        return dummy.next;
    }
}
```

## 🌍 Real-World Analogy
### **Relay Race Batons:**
Imagine two runners with a solid stick connecting them that is exactly `n` meters long.
- They start at the beginning.
- They run together.
- When the front runner hits the finish line, the back runner is exactly `n` meters away from the finish.
- The back runner picks up the object at that spot.

## 🎯 Summary
✅ **One Pass:** Efficiently finds the node.
✅ **Dummy Node:** Simplifies edge cases (e.g., removing head).
