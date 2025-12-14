# Merge K Sorted Lists

## 🧩 Problem Statement
You are given an array of `k` linked-lists `lists`, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

### 🔹 Example 1:
#### Input:
```plaintext
lists = [[1,4,5],[1,3,4],[2,6]]
```
#### Output:
```plaintext
[1,1,2,3,4,4,5,6]
```
#### Explanation:
The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6

## 🔍 Approaches

### 1. Min-Heap ($O(N \log K)$)
- **Concept:** We need to repeatedly find the minimum element among the heads of the `k` lists. A Min-Heap is perfect for this.
- **Algorithm:**
  1. Push the head of each non-empty list into a Min-Heap.
  2. While Heap is not empty:
     - Pop the smallest node.
     - Add it to the result list.
     - If the popped node has a `next` node, push that `next` node into the Heap.
- **Complexity:**
  - $N$ total nodes.
  - Heap size is at most $K$.
  - Each insertion/deletion takes $O(\log K)$.
  - Total time: $O(N \log K)$.

### 2. Divide and Conquer ($O(N \log K)$)
- Merge pairs of lists. Then merge the results. Similar to Merge Sort.

## ⏳ Time & Space Complexity
- **Time Complexity:** $O(N \log K)$.
- **Space Complexity:** $O(K)$ for the heap.

## 🚀 Code Implementations

### C++
```cpp
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    struct compare {
        bool operator()(const ListNode* l, const ListNode* r) {
            return l->val > r->val;
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, compare> pq;
        for (auto l : lists) {
            if (l) pq.push(l);
        }
        
        ListNode dummy(0);
        ListNode* tail = &dummy;
        
        while (!pq.empty()) {
            ListNode* node = pq.top();
            pq.pop();
            tail->next = node;
            tail = tail->next;
            
            if (node->next) pq.push(node->next);
        }
        
        return dummy.next;
    }
};
```

### Python
```python
import heapq
from typing import List, Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # Heap stores tuples: (val, index, node) to verify sorting stability and handle ties
        # Using index as tie breaker because ListNode doesn't support comparison
        min_heap = []
        for i, l in enumerate(lists):
            if l:
                heapq.heappush(min_heap, (l.val, i, l))
        
        dummy = ListNode(0)
        curr = dummy
        
        while min_heap:
            val, i, node = heapq.heappop(min_heap)
            curr.next = node
            curr = curr.next
            if node.next:
                heapq.heappush(min_heap, (node.next.val, i, node.next))
                
        return dummy.next
```

### Java
```java
import java.util.PriorityQueue;

class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

class Solution {
    public ListNode mergeKLists(ListNode[] lists) {
        PriorityQueue<ListNode> pq = new PriorityQueue<>((a, b) -> a.val - b.val);
        for (ListNode l : lists) {
            if (l != null) pq.offer(l);
        }
        
        ListNode dummy = new ListNode(0);
        ListNode curr = dummy;
        
        while (!pq.isEmpty()) {
            ListNode node = pq.poll();
            curr.next = node;
            curr = curr.next;
            
            if (node.next != null) pq.offer(node.next);
        }
        
        return dummy.next;
    }
}
```

## 🌍 Real-World Analogy
### **Merging Lines:**
Imagine 5 different lines of people sorted by height. You want to form a single line sorted by height. You look at the front person of all 5 lines, pick the shortest one, and invoke them to the new line. Then you look at the new front of that specific line and repeat.

## 🎯 Summary
✅ **Min-Heap:** The best way to efficiently find the minimum among $K$ candidates repeatedly.
