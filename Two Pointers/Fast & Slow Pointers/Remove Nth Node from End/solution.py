from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

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
            
        left.next = left.next.next
        return dummy.next

def print_list(head):
    vals = []
    while head:
        vals.append(str(head.val))
        head = head.next
    print("->".join(vals))

if __name__ == "__main__":
    sol = Solution()
    # 1 -> 2 -> 3 -> 4 -> 5
    head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    print("Original: ", end="")
    print_list(head)
    
    head = sol.removeNthFromEnd(head, 2)
    
    print("After removing 2nd from end: ", end="")
    print_list(head)
