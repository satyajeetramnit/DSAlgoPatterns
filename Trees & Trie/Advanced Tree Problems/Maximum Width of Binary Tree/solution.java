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
    public int widthOfBinaryTree(TreeNode root) {
        if (root == null) return 0;
        
        Queue<Pair<TreeNode, Integer>> queue = new LinkedList<>();
        queue.offer(new Pair<>(root, 0));
        int maxWidth = 0;
        
        while (!queue.isEmpty()) {
            int size = queue.size();
            int minIndex = queue.peek().getValue(); // Normalize indices
            int firstIndex = 0, lastIndex = 0;
            
            for (int i = 0; i < size; i++) {
                Pair<TreeNode, Integer> pair = queue.poll();
                TreeNode node = pair.getKey();
                int curIndex = pair.getValue() - minIndex;
                
                if (i == 0) firstIndex = curIndex;
                if (i == size - 1) lastIndex = curIndex;
                
                if (node.left != null) queue.offer(new Pair<>(node.left, 2 * curIndex));
                if (node.right != null) queue.offer(new Pair<>(node.right, 2 * curIndex + 1));
            }
            maxWidth = Math.max(maxWidth, lastIndex - firstIndex + 1);
        }
        return maxWidth;
    }
    
    // Simple Pair class
    static class Pair<K, V> {
        K key; V value;
        public Pair(K key, V value) { this.key = key; this.value = value; }
        public K getKey() { return key; }
        public V getValue() { return value; }
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(3);
        root.right = new TreeNode(2);
        root.left.left = new TreeNode(5);
        root.left.right = new TreeNode(3);
        root.right.right = new TreeNode(9);
        
        System.out.println("Test Case 1: " + sol.widthOfBinaryTree(root)); // Expect 4
    }
}
