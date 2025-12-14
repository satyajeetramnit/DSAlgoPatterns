import java.util.*;

class ListNode {
    int val;
    ListNode next;
    ListNode(int x) { val = x; }
    ListNode(int x, ListNode next) { val = x; this.next = next; }
}

class Solution {
    public int[] nextLargerNodes(ListNode head) {
        List<Integer> vals = new ArrayList<>();
        while (head != null) {
            vals.add(head.val);
            head = head.next;
        }
        
        int[] res = new int[vals.size()];
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < vals.size(); i++) {
            while (!stack.isEmpty() && vals.get(i) > vals.get(stack.peek())) {
                res[stack.pop()] = vals.get(i);
            }
            stack.push(i);
        }
        
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        ListNode head = new ListNode(2, new ListNode(1, new ListNode(5)));
        System.out.println("Test Case 1: " + Arrays.toString(sol.nextLargerNodes(head))); // Expect [5, 5, 0]
    }
}
