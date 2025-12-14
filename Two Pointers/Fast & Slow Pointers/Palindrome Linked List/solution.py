from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

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

if __name__ == "__main__":
    sol = Solution()
    
    # 1 -> 2 -> 2 -> 1
    head = ListNode(1, ListNode(2, ListNode(2, ListNode(1))))
    print(f"Is Palindrome (1->2->2->1): {sol.isPalindrome(head)}")

    # 1 -> 2
    head2 = ListNode(1, ListNode(2))
    print(f"Is Palindrome (1->2): {sol.isPalindrome(head2)}")
