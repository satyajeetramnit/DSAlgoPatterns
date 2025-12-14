# Reverse Linked List

## 🧩 Problem Statement
Given the `head` of a singly linked list, reverse the list, and return the reversed list.

### 🔹 Example 1:
#### Input:
```plaintext
head = [1,2,3,4,5]
```
#### Output:
```plaintext
[5,4,3,2,1]
```

### 🔹 Example 2:
#### Input:
```plaintext
head = [1,2]
```
#### Output:
```plaintext
[2,1]
```

### 🔹 Example 3:
#### Input:
```plaintext
head = []
```
#### Output:
```plaintext
[]
```

## 🔍 Approaches

### 1. Iterative
We iterate through the list and change the `next` pointer of each node to point to the previous node.

### ✨ Intuition
- Use three pointers: `prev`, `curr`, `nextTemp`.
- `prev` tracks the confirmed reversed part (initially NULL).
- `curr` is the node we are currently reversing.
- `nextTemp` saves the rest of the list so we don't lose it when we overwrite `curr.next`.

### 🔥 Algorithm Steps
1. Initialize `prev = NULL`, `curr = head`.
2. While `curr` is not NULL:
   - Save `nextTemp = curr.next`.
   - Reverse: `curr.next = prev`.
   - Advance: `prev = curr`, `curr = nextTemp`.
3. Return `prev` (new head).

### 2. Recursive
We reverse the rest of the list first, then put the current node at the end of that reversed list.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, visit each node once.
- **Space Complexity:** $O(1)$ for iterative, $O(n)$ for recursive (stack depth).

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
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
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
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        prev = None
        curr = head
        while curr:
            tmp = curr.next
            curr.next = prev
            prev = curr
            curr = tmp
        return prev
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
    public ListNode reverseList(ListNode head) {
        ListNode prev = null;
        ListNode curr = head;
        while (curr != null) {
            ListNode nextTemp = curr.next;
            curr.next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }
}
```

## 🌍 Real-World Analogy
### **Turning a Train Around:**
Imagine a train where each car points to the next.
- To reverse it car by car:
- You uncouple the first car (engine) from the second.
- You make the first car point to "nothing" (new end).
- You take the second car, uncouple it from the third, and couple it to the first.
- Repeat until the last car (caboose) becomes the new engine.

## 🎯 Summary
✅ **O(1) Space:** Iterative is most efficient.
✅ **Foundation:** critical for many linked list problems.
