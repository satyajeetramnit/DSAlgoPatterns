from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0, head)
        prev = dummy
        curr = head
        
        while curr and curr.next:
            # save
            nextPair = curr.next.next
            second = curr.next
            
            # reverse
            second.next = curr
            curr.next = nextPair
            prev.next = second
            
            # update
            prev = curr
            curr = nextPair
            
        return dummy.next

def print_list(head):
    vals = []
    while head:
        vals.append(str(head.val))
        head = head.next
    print("->".join(vals))

if __name__ == "__main__":
    sol = Solution()
    head = ListNode(1, ListNode(2, ListNode(3, ListNode(4))))
    print("Original: ", end="")
    print_list(head)
    
    head = sol.swapPairs(head)
    
    print("Swapped: ", end="")
    print_list(head)
