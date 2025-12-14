# Palindrome Linked List

## 🧩 Problem Statement
Given the `head` of a singly linked list, return `true` if it is a palindrome.

### 🔹 Example 1:
#### Input:
```plaintext
head = [1,2,2,1]
```
#### Output:
```plaintext
true
```

### 🔹 Example 2:
#### Input:
```plaintext
head = [1,2]
```
#### Output:
```plaintext
false
```

## 🔍 Approaches

### 1. Fast & Slow Pointers (Reverse Second Half)
Using a stack or array takes $O(n)$ space. To do it in $O(1)$ space, we can modify the list structure.
We find the middle, reverse the second half, compare it with the first half, and (optionally) restore the list.

### ✨ Intuition
- **Find Middle:** Use slow/fast pointers. When fast reaches end, slow is at middle.
- **Reverse:** Reverse the list starting from `slow.next`.
- **Compare:** Iterate from `head` and the new start of the reversed half. If values differ, not a palindrome.
- **Restore (Optional):** Reverse the second half again to restore original structure.

### 🔥 Algorithm Steps
1. Find the end of the first half using fast/slow pointers.
2. Reverse the second half of the list.
3. Compare the first half and the second half.
4. Return `true` if they match, `false` otherwise.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$. Middle find is $O(n)$, reverse is $O(n)$, compare is $O(n)$.
- **Space Complexity:** $O(1)$, modification is in-place.

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
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        // Find middle
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // Reverse second half
        ListNode *secondHalf = reverseList(slow->next);
        ListNode *firstHalf = head;
        
        // Check palindrome
        ListNode *p1 = firstHalf;
        ListNode *p2 = secondHalf;
        bool result = true;
        while (result && p2) {
            if (p1->val != p2->val) result = false;
            p1 = p1->next;
            p2 = p2->next;
        }
        
        // Restore list (Optional but good practice)
        slow->next = reverseList(secondHalf);
        
        return result;
    }
    
    ListNode* reverseList(ListNode* head) {
        ListNode *prev = nullptr, *curr = head;
        while (curr) {
            ListNode *nextTemp = curr->next;
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
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        if not head: return True
        
        # Find middle
        slow = fast = head
        while fast and fast.next:
            fast = fast.next.next
            slow = slow.next
            
        # Reverse second half
        prev = None
        while slow:
            tmp = slow.next
            slow.next = prev
            prev = slow
            slow = tmp
            
        # Check palindrome
        left, right = head, prev
        while right:
            if left.val != right.val:
                return False
            left = left.next
            right = right.next
        return True
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
    public boolean isPalindrome(ListNode head) {
        if (head == null) return true;

        // Find middle
        ListNode firstHalfEnd = endOfFirstHalf(head);
        ListNode secondHalfStart = reverseList(firstHalfEnd.next);

        // Check palindrome
        ListNode p1 = head;
        ListNode p2 = secondHalfStart;
        boolean result = true;
        while (result && p2 != null) {
            if (p1.val != p2.val) result = false;
            p1 = p1.next;
            p2 = p2.next;
        }

        // Restore list
        firstHalfEnd.next = reverseList(secondHalfStart);
        return result;
    }

    private ListNode reverseList(ListNode head) {
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

    private ListNode endOfFirstHalf(ListNode head) {
        ListNode slow = head;
        ListNode fast = head;
        while (fast.next != null && fast.next.next != null) {
            slow = slow.next;
            fast = fast.next.next;
        }
        return slow;
    }
}
```

## 🌍 Real-World Analogy
### **Reading a DNA Sequence:**
You have a long DNA strand. You want to check if the sequence of bases reads the same forwards and backwards.
- You find the midpoint.
- You take the second half and "read it backwards" (reverse it).
- You compare it base-by-base with the first half.

## 🎯 Summary
✅ **O(1) Space:** No extra storage like stack/array.
✅ **Reversal:** Key technique for palindrome checks in linked lists.
