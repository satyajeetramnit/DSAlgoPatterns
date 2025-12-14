# Linked List Cycle II

## 🧩 Problem Statement
Given the `head` of a linked list, return the node where the cycle begins. If there is no cycle, return `null`.

There is a cycle in a linked list if there is some node in the list that can be reached again by continuously following the `next` pointer.

Do not modify the linked list.

### 🔹 Example 1:
#### Input:
```plaintext
head = [3,2,0,-4], pos = 1
```
#### Output:
```plaintext
tail connects to node index 1
```
#### Explanation:
There is a cycle in the linked list, where tail connects to the second node.

### 🔹 Example 2:
#### Input:
```plaintext
head = [1,2], pos = 0
```
#### Output:
```plaintext
tail connects to node index 0
```

## 🔍 Approaches

### 1. Floyd's Tortoise and Hare (Cycle Detection)
We use two pointers: `slow` (moves 1 step) and `fast` (moves 2 steps).
If there is a cycle, they will meet.
If they meet, there's a mathematical property to find the entrance.

### ✨ Intuition
- **Phase 1 (Detection):**
  - Iterate until `fast` becomes null (no cycle) or `fast == slow` (cycle detected).
- **Phase 2 (Entrance Finding):**
  - Let $L$ be the distance from head to cycle entry.
  - Let $C$ be the length of the cycle.
  - Let $X$ be the distance from entry to meeting point.
  - Distance traveled by slow: $L + X$
  - Distance traveled by fast: $L + nC + X$ (where n is integer)
  - Since fast is twice as fast: $2(L + X) = L + nC + X$
  - Simplifying: $L + X = nC \implies L = nC - X$.
  - This means if we reset `slow` to `head` and keep `fast` at meeting point, and move both 1 step at a time, they will meet exactly at the cycle entry after $L$ steps.

### 🔥 Algorithm Steps
1. Initialize `slow = head`, `fast = head`.
2. While `fast` and `fast.next` are not null:
   - `slow = slow.next`
   - `fast = fast.next.next`
   - If `slow == fast`:
     - Break (Cycle found).
3. If loop finished and `fast` or `fast.next` is null, return `null` (No cycle).
4. Reset `slow = head`.
5. While `slow != fast`:
   - `slow = slow.next`
   - `fast = fast.next`
6. Return `slow`.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, we traverse the list a constant number of times.
- **Space Complexity:** $O(1)$, only two pointers used.

## 🚀 Code Implementations

### C++
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        bool hasCycle = false;
        
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                hasCycle = true;
                break;
            }
        }
        
        if (!hasCycle) return NULL;
        
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
```

### Python
```python
# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, x):
#         self.val = x
#         self.next = None

class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        slow, fast = head, head
        
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                break
        else:
            return None
            
        slow = head
        while slow != fast:
            slow = slow.next
            fast = fast.next
            
        return slow
```

### Java
```java
/**
 * Definition for singly-linked list.
 * class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) {
 *         val = x;
 *         next = null;
 *     }
 * }
 */
public class Solution {
    public ListNode detectCycle(ListNode head) {
        ListNode slow = head, fast = head;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) break;
        }
        
        if (fast == null || fast.next == null) return null;
        
        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }
        return slow;
    }
}
```

## 🌍 Real-World Analogy
### **Meeting on a Track:**
Imagine a race on a looped track (lollipop shape).
- A fast runner and a slow runner start together.
- The fast runner enters the loop, laps the slow runner, and meets them.
- If the slow runner restarts at the beginning and walks, and the fast runner (now tired) walks from the meeting point, they will bump into each other exactly at the gate of the loop.

## 🎯 Summary
✅ **Floyd's Cycle Finding:** Standard algorithm.
✅ **Two-Phase:** Detect then Locate.
