import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

class Solution {
    // Subsets I
    public List<List<Integer>> subsets(int[] nums) {
        List<List<Integer>> res = new ArrayList<>();
        backtrack(nums, 0, new ArrayList<>(), res);
        return res;
    }
    
    private void backtrack(int[] nums, int start, List<Integer> path, List<List<Integer>> res) {
        res.add(new ArrayList<>(path));
        
        for (int i = start; i < nums.length; i++) {
            path.add(nums[i]);
            backtrack(nums, i + 1, path, res);
            path.remove(path.size() - 1);
        }
    }

    // Subsets II
    public List<List<Integer>> subsetsWithDup(int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> res = new ArrayList<>();
        backtrackWithDup(nums, 0, new ArrayList<>(), res);
        return res;
    }
    
    private void backtrackWithDup(int[] nums, int start, List<Integer> path, List<List<Integer>> res) {
        res.add(new ArrayList<>(path));
        
        for (int i = start; i < nums.length; i++) {
            if (i > start && nums[i] == nums[i-1]) continue;
            
            path.add(nums[i]);
            backtrackWithDup(nums, i + 1, path, res);
            path.remove(path.size() - 1);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {1, 2, 3};
        System.out.println("Subsets [1,2,3]: " + sol.subsets(nums1));

        int[] nums2 = {1, 2, 2};
        System.out.println("SubsetsWithDup [1,2,2]: " + sol.subsetsWithDup(nums2));
    }
}
