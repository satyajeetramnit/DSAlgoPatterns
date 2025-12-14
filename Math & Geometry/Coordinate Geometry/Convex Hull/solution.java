import java.util.*;

class Solution {
    public int crossProduct(int[] o, int[] a, int[] b) {
        return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
    }

    public int[][] outerTrees(int[][] trees) {
        if (trees.length <= 1) return trees;
        
        Arrays.sort(trees, (a, b) -> (a[0] == b[0]) ? a[1] - b[1] : a[0] - b[0]);
        
        List<int[]> result = new ArrayList<>();
        
        for(int[] p : trees) {
            while(result.size() >= 2 && crossProduct(result.get(result.size()-2), result.get(result.size()-1), p) < 0) {
                result.remove(result.size()-1); 
            }
            result.add(p);
        }
        
        int lowerSize = result.size();
        for(int i = trees.length - 2; i >= 0; i--) {
            while(result.size() > lowerSize && crossProduct(result.get(result.size()-2), result.get(result.size()-1), trees[i]) < 0) {
                result.remove(result.size()-1);
            }
            result.add(trees[i]);
        }
        
        if (result.size() > 1) result.remove(result.size() - 1);
        
        Set<String> unique = new HashSet<>();
        List<int[]> finalHull = new ArrayList<>();
        for(int[] p : result) {
            String key = p[0] + "," + p[1];
            if(unique.add(key)) finalHull.add(p);
        }
        
        // Sorting for consistent string output in main
        finalHull.sort((a,b) -> a[0] == b[0] ? a[1] - b[1] : a[0] - b[0]);
        
        return finalHull.toArray(new int[finalHull.size()][]);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] points = {{1,1},{2,2},{2,0},{2,4},{3,3},{4,2}};
        int[][] hull = sol.outerTrees(points);
        
        System.out.println("Test Case 1 Output:");
        for (int[] p : hull) {
            System.out.print("[" + p[0] + "," + p[1] + "] ");
        }
        System.out.println();
    }
}
