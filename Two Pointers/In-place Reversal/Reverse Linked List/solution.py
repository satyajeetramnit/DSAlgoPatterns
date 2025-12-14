from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

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

def print_list(head):
    vals = []
    while head:
        vals.append(str(head.val))
        head = head.next
    print("->".join(vals))

if __name__ == "__main__":
    sol = Solution()
    head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    print("Original: ", end="")
    print_list(head)
    
    head = sol.reverseList(head)
    
    print("Reversed: ", end="")
    print_list(head)
