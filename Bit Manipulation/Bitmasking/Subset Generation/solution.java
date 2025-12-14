import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

class Solution {
    public List<List<Integer>> subsets(int[] nums) {
        int n = nums.length;
        int totalSubsets = 1 << n;
        List<List<Integer>> res = new ArrayList<>();
        
        for (int mask = 0; mask < totalSubsets; mask++) {
            List<Integer> subset = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (((mask >> i) & 1) == 1) {
                    subset.add(nums[i]);
                }
            }
            res.add(subset);
        }
        
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1,2,3};
        List<List<Integer>> res = sol.subsets(nums);
        System.out.println("Test Case 1 (Size should be 8): " + res.size());
        System.out.println(res);
    }
}
