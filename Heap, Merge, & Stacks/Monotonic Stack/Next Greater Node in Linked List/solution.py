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

if __name__ == "__main__":
    sol = Solution()
    head = ListNode(2, ListNode(1, ListNode(5)))
    print(f"Test Case 1: {sol.nextLargerNodes(head)}") # Expect [5, 5, 0]
