import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    // Combination Sum I
    public List<List<Integer>> combinationSum(int[] candidates, int target) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack1(candidates, target, 0, new ArrayList<>(), res);
        return res;
    }

    private void backtrack1(int[] candidates, int target, int start, 
                            List<Integer> path, List<List<Integer>> res) {
        if (target == 0) {
            res.add(new ArrayList<>(path));
            return;
        }
        if (target < 0) return;

        for (int i = start; i < candidates.length; i++) {
            path.add(candidates[i]);
            // Reuse same element: i
            backtrack1(candidates, target - candidates[i], i, path, res);
            path.remove(path.size() - 1);
        }
    }

    // Combination Sum II
    public List<List<Integer>> combinationSum2(int[] candidates, int target) {
        Arrays.sort(candidates);
        List<List<Integer>> res = new ArrayList<>();
        backtrack2(candidates, target, 0, new ArrayList<>(), res);
        return res;
    }

    private void backtrack2(int[] candidates, int target, int start, 
                            List<Integer> path, List<List<Integer>> res) {
        if (target == 0) {
            res.add(new ArrayList<>(path));
            return;
        }
        if (target < 0) return;

        for (int i = start; i < candidates.length; i++) {
            if (i > start && candidates[i] == candidates[i-1]) continue;
            
            path.add(candidates[i]);
            // Next element: i + 1
            backtrack2(candidates, target - candidates[i], i + 1, path, res);
            path.remove(path.size() - 1);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] c1 = {2,3,6,7};
        int t1 = 7;
        System.out.println("Combination Sum I: " + sol.combinationSum(c1, t1));
        
        int[] c2 = {10,1,2,7,6,1,5};
        int t2 = 8;
        System.out.println("Combination Sum II: " + sol.combinationSum2(c2, t2));
    }
}
