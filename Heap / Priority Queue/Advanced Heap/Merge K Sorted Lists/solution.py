import heapq
from typing import List, Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
    def __repr__(self):
        return f"{self.val} -> {self.next}"

class Solution:
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        # Heap stores tuples: (val, index, node)
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

def print_list(node):
    res = []
    while node:
        res.append(str(node.val))
        node = node.next
    print(" ".join(res))

if __name__ == "__main__":
    sol = Solution()
    # 1->4->5
    l1 = ListNode(1, ListNode(4, ListNode(5)))
    # 1->3->4
    l2 = ListNode(1, ListNode(3, ListNode(4)))
    # 2->6
    l3 = ListNode(2, ListNode(6))
    
    merged = sol.mergeKLists([l1, l2, l3])
    print("Test Case 1: ", end="")
    print_list(merged) # 1 1 2 3 4 4 5 6
