import java.util.*;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

class Solution {
    public TreeNode constructMaximumBinaryTree(int[] nums) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        for (int num : nums) {
            TreeNode curr = new TreeNode(num);
            while (!stack.isEmpty() && stack.peek().val < num) {
                curr.left = stack.pop();
            }
            if (!stack.isEmpty()) {
                stack.peek().right = curr;
            }
            stack.push(curr);
        }
        return stack.isEmpty() ? null : stack.peekLast();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {3,2,1,6,0,5};
        TreeNode root = sol.constructMaximumBinaryTree(nums);
        System.out.println("Test Case 1: Root=" + root.val + ", Left=" + root.left.val + ", Right=" + root.right.val); // Expect Root=6, Left=3, Right=5
    }
}
