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
    public TreeNode addOneRow(TreeNode root, int val, int depth) {
        if (depth == 1) {
            TreeNode newRoot = new TreeNode(val);
            newRoot.left = root;
            return newRoot;
        }
        
        Queue<TreeNode> queue = new LinkedList<>();
        queue.offer(root);
        int currentDepth = 1;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            
            if (currentDepth == depth - 1) {
                for (int i = 0; i < size; i++) {
                    TreeNode node = queue.poll();
                    TreeNode oldLeft = node.left;
                    TreeNode oldRight = node.right;
                    
                    node.left = new TreeNode(val);
                    node.left.left = oldLeft;
                    
                    node.right = new TreeNode(val);
                    node.right.right = oldRight;
                }
                break;
            }
            
            for (int i = 0; i < size; i++) {
                TreeNode node = queue.poll();
                if (node.left != null) queue.offer(node.left);
                if (node.right != null) queue.offer(node.right);
            }
            currentDepth++;
        } 
        return root;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        TreeNode root = new TreeNode(4);
        root.left = new TreeNode(2);
        root.right = new TreeNode(6);
        root.left.left = new TreeNode(3);
        root.left.right = new TreeNode(1);
        root.right.left = new TreeNode(5);
        
        TreeNode res = sol.addOneRow(root, 1, 2);
        System.out.println("Test Case 1: Root=" + res.val + ", Left=" + res.left.val + ", Right=" + res.right.val + ", LeftLeft=" + res.left.left.val); // Expect 4, 1, 1, 2
    }
}
