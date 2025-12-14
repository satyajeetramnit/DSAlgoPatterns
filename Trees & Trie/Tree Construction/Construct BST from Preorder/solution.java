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
    int idx = 0;
    
    public TreeNode bstFromPreorder(int[] preorder) {
        idx = 0;
        return build(preorder, Integer.MAX_VALUE);
    }
    
    private TreeNode build(int[] preorder, int bound) {
        if (idx >= preorder.length || preorder[idx] > bound) {
            return null;
        }
        
        TreeNode root = new TreeNode(preorder[idx++]);
        root.left = build(preorder, root.val);
        root.right = build(preorder, bound);
        
        return root;
    }

    public static List<Integer> getPreorder(TreeNode root) {
        List<Integer> res = new ArrayList<>();
        if (root == null) return res;
        res.add(root.val);
        res.addAll(getPreorder(root.left));
        res.addAll(getPreorder(root.right));
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] preorder = {8,5,1,7,10,12};
        TreeNode root = sol.bstFromPreorder(preorder);
        System.out.println("Test Case 1 (Re-Preorder): " + getPreorder(root)); // Expect [8, 5, 1, 7, 10, 12]
    }
}
