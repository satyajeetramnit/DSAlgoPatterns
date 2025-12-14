# Reverse Nodes in k-Group

## 🧩 Problem Statement
Given the `head` of a linked list, reverse the nodes of the list `k` at a time, and return the modified list.

`k` is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of `k` then left-out nodes, in the end, should remain as it is.

You may not alter the values in the list's nodes, only nodes themselves may be changed.

### 🔹 Example 1:
#### Input:
```plaintext
head = [1,2,3,4,5], k = 2
```
#### Output:
```plaintext
[2,1,4,3,5]
```

### 🔹 Example 2:
#### Input:
```plaintext
head = [1,2,3,4,5], k = 3
```
#### Output:
```plaintext
[3,2,1,4,5]
```

## 🔍 Approaches

### 1. Iterative with Group Reversal
We process the list in chunks of size `k`. For each chunk, we reverse it and link it back to the previous and next chunks.

### ✨ Intuition
- Use a `dummy` node to handle the new head easily.
- Navigate `k` steps to check if there are enough nodes to reverse.
- If yes, reverse the `k` nodes.
- Maintain `groupPrev` (end of previous reversed group) and connect it to the new start of current group.
- Update `groupPrev` to the end of the current group (which was the start before reversal).

### 🔥 Algorithm Steps
1. Create `dummy` node pointing to `head`. `groupPrev = dummy`.
2. Find the `kth` node from `groupPrev`. If not found (less than k nodes), stop.
3. Save `groupNext = kth.next`.
4. Reverse the list from `groupPrev.next` to `kth`.
5. Connect `groupPrev.next` to the new head of reversed group (`kth`).
6. Connect the new tail of reversed group (original `start`) to `groupNext`.
7. Update `groupPrev` to the new tail.
8. Repeat until end of list.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(n)$, we visit each node twice (once to find range, once to reverse).
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummy = new ListNode(0, head);
        ListNode* groupPrev = dummy;
        
        while (true) {
            ListNode* kth = getKth(groupPrev, k);
            if (!kth) break;
            ListNode* groupNext = kth->next;
            
            // Reverse group
            ListNode* prev = kth->next;
            ListNode* curr = groupPrev->next;
            
            while (curr != groupNext) {
                ListNode* tmp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = tmp;
            }
            
            ListNode* tmp = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = tmp;
        }
        return dummy->next;
    }
    
    ListNode* getKth(ListNode* curr, int k) {
        while (curr && k > 0) {
            curr = curr->next;
            k--;
        }
        return curr;
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
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        groupPrev = dummy
        
        while True:
            kth = self.getKth(groupPrev, k)
            if not kth:
                break
            groupNext = kth.next
            
            # reverse group
            prev, curr = kth.next, groupPrev.next
            
            while curr != groupNext:
                tmp = curr.next
                curr.next = prev
                prev = curr
                curr = tmp
            
            tmp = groupPrev.next
            groupPrev.next = kth
            groupPrev = tmp
            
        return dummy.next
    
    def getKth(self, curr, k):
        while curr and k > 0:
            curr = curr.next
            k -= 1
        return curr
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
    public ListNode reverseKGroup(ListNode head, int k) {
        ListNode dummy = new ListNode(0, head);
        ListNode groupPrev = dummy;
        
        while (true) {
            ListNode kth = getKth(groupPrev, k);
            if (kth == null) break;
            ListNode groupNext = kth.next;
            
            // Reverse group
            ListNode prev = kth.next;
            ListNode curr = groupPrev.next;
            
            while (curr != groupNext) {
                ListNode tmp = curr.next;
                curr.next = prev;
                prev = curr;
                curr = tmp;
            }
            
            ListNode tmp = groupPrev.next;
            groupPrev.next = kth;
            groupPrev = tmp;
        }
        return dummy.next;
    }
    
    private ListNode getKth(ListNode curr, int k) {
        while (curr != null && k > 0) {
            curr = curr.next;
            k--;
        }
        return curr;
    }
}
```

## 🌍 Real-World Analogy
### **Flipping Pancakes in Batches:**
Imagine a stack of pancakes. You want to flip them in batches of 3.
- You slide a spatula under the 3rd pancake.
- You lift the top 3 and flip them over onto the plate.
- Then you slide the spatula under the 6th pancake (relative to original order) and flip the next batch of 3.
- If fewer than 3 remain, you leave them as is.

## 🎯 Summary
✅ **Complex Pointer Manipulation:** Good practice for interview scenarios.
✅ **Modular Logic:** Breaking it down into "get kth" and "reverse logic" simplifies implementation.
