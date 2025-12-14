class ListNode {
    int val;
    ListNode next;
    ListNode() {}
    ListNode(int val) { this.val = val; }
    ListNode(int val, ListNode next) { this.val = val; this.next = next; }
}

class Solution {
    public ListNode swapPairs(ListNode head) {
        ListNode dummy = new ListNode(0, head);
        ListNode prev = dummy;
        ListNode curr = head;
        
        while (curr != null && curr.next != null) {
            ListNode nextPair = curr.next.next;
            ListNode second = curr.next;
            
            // Swap
            second.next = curr;
            curr.next = nextPair;
            prev.next = second;
            
            // Advance
            prev = curr;
            curr = nextPair;
        }
        return dummy.next;
    }

    public static void printList(ListNode head) {
        while (head != null) {
            System.out.print(head.val + (head.next != null ? "->" : ""));
            head = head.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ListNode head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
        System.out.print("Original: ");
        printList(head);
        
        head = sol.swapPairs(head);
        
        System.out.print("Swapped: ");
        printList(head);
    }
}
