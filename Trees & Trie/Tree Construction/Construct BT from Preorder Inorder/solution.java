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
    int pre_idx = 0;
    Map<Integer, Integer> map = new HashMap<>();
    
    public TreeNode buildTree(int[] preorder, int[] inorder) {
        pre_idx = 0;
        map.clear();
        for (int i = 0; i < inorder.length; i++) {
            map.put(inorder[i], i);
        }
        return build(preorder, 0, inorder.length - 1);
    }
    
    private TreeNode build(int[] preorder, int left, int right) {
        if (left > right) return null;
        
        int root_val = preorder[pre_idx++];
        TreeNode root = new TreeNode(root_val);
        
        int index = map.get(root_val);
        
        root.left = build(preorder, left, index - 1);
        root.right = build(preorder, index + 1, right);
        
        return root;
    }

    // Helper for printing
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
        int[] preorder = {3,9,20,15,7};
        int[] inorder = {9,3,15,20,7};
        TreeNode root = sol.buildTree(preorder, inorder);
        System.out.println("Test Case 1 (Re-Preorder): " + getPreorder(root)); // Expect [3, 9, 20, 15, 7]
    }
}
