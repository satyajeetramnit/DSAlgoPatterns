import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    // Permutatios I
    public List<List<Integer>> permute(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack(nums, new ArrayList<>(), new boolean[nums.length], res);
        return res;
    }
    
    private void backtrack(int[] nums, List<Integer> path, boolean[] used, List<List<Integer>> res) {
        if (path.size() == nums.length) {
            res.add(new ArrayList<>(path));
            return;
        }
        
        for (int i = 0; i < nums.length; i++) {
            if (used[i]) continue;
            
            used[i] = true;
            path.add(nums[i]);
            backtrack(nums, path, used, res);
            path.remove(path.size() - 1);
            used[i] = false;
        }
    }

    // Permutations II
    public List<List<Integer>> permuteUnique(int[] nums) {
        Arrays.sort(nums); // Key step
        List<List<Integer>> res = new ArrayList<>();
        backtrackUnique(nums, new ArrayList<>(), new boolean[nums.length], res);
        return res;
    }
    
    private void backtrackUnique(int[] nums, List<Integer> path, boolean[] used, List<List<Integer>> res) {
        if (path.size() == nums.length) {
            res.add(new ArrayList<>(path));
            return;
        }
        
        for (int i = 0; i < nums.length; i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            
            used[i] = true;
            path.add(nums[i]);
            backtrackUnique(nums, path, used, res);
            path.remove(path.size() - 1);
            used[i] = false;
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();

        int[] nums1 = {1, 2, 3};
        System.out.println("Permute [1,2,3]: " + sol.permute(nums1));

        int[] nums2 = {1, 1, 2};
        System.out.println("PermuteUnique [1,1,2]: " + sol.permuteUnique(nums2));
    }
}
