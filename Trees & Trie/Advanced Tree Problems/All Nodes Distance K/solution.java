import java.util.*;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode(int x) { val = x; }
}

class Solution {
    Map<TreeNode, TreeNode> parents = new HashMap<>();
    
    public List<Integer> distanceK(TreeNode root, TreeNode target, int k) {
        buildParents(root, null);
        
        Queue<TreeNode> queue = new LinkedList<>();
        Set<TreeNode> visited = new HashSet<>();
        
        queue.offer(target);
        visited.add(target);
        
        int dist = 0;
        
        while (!queue.isEmpty()) {
            if (dist == k) {
                List<Integer> result = new ArrayList<>();
                for (TreeNode node : queue) {
                    result.add(node.val);
                }
                return result;
            }
            
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode curr = queue.poll();
                
                if (curr.left != null && !visited.contains(curr.left)) {
                    visited.add(curr.left);
                    queue.offer(curr.left);
                }
                if (curr.right != null && !visited.contains(curr.right)) {
                    visited.add(curr.right);
                    queue.offer(curr.right);
                }
                if (parents.containsKey(curr) && !visited.contains(parents.get(curr))) {
                    TreeNode parent = parents.get(curr);
                    if (parent != null) {
                        visited.add(parent);
                        queue.offer(parent);
                    }
                }
            }
            dist++;
        }
        
        return new ArrayList<>();
    }
    
    private void buildParents(TreeNode node, TreeNode parent) {
        if (node == null) return;
        parents.put(node, parent);
        buildParents(node.left, node);
        buildParents(node.right, node);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        TreeNode root = new TreeNode(3);
        root.left = new TreeNode(5);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(6);
        root.left.right = new TreeNode(2);
        root.right.left = new TreeNode(0);
        root.right.right = new TreeNode(8);
        root.left.right.left = new TreeNode(7);
        root.left.right.right = new TreeNode(4);
        
        TreeNode target = root.left; // 5
        
        List<Integer> result = sol.distanceK(root, target, 2);
        Collections.sort(result);
        System.out.println("Test Case 1: " + result); // Expect [1, 4, 7]
    }
}
