class ListNode {
    int val;
    ListNode next;
    ListNode(int x) {
        val = x;
        next = null;
    }
}

class Solution {
    public ListNode detectCycle(ListNode head) {
        ListNode slow = head, fast = head;
        
        while (fast != null && fast.next != null) {
            slow = slow.next;
            fast = fast.next.next;
            if (slow == fast) break;
        }
        
        if (fast == null || fast.next == null) return null;
        
        slow = head;
        while (slow != fast) {
            slow = slow.next;
            fast = fast.next;
        }
        return slow;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ListNode head = new ListNode(3);
        ListNode node2 = new ListNode(2);
        ListNode node3 = new ListNode(0);
        ListNode node4 = new ListNode(-4);
        
        head.next = node2;
        node2.next = node3;
        node3.next = node4;
        node4.next = node2; // Cycle
        
        ListNode res = sol.detectCycle(head);
        if (res != null) {
            System.out.println("Cycle detected at node with val: " + res.val);
        } else {
            System.out.println("No cycle detected");
        }
    }
}
