class Solution {
    public boolean isSubsetSum(int[] nums, int target) {
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;
        
        for(int num : nums) {
            for(int j = target; j >= num; j--) {
                if(dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        return dp[target];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {3, 34, 4, 12, 5, 2};
        System.out.println("Test Case 1 (Target 9): " + sol.isSubsetSum(nums1, 9)); // True
        System.out.println("Test Case 2 (Target 30): " + sol.isSubsetSum(nums1, 30)); // False
        
        int[] nums2 = {1, 2, 3};
        System.out.println("Test Case 3 (Target 6): " + sol.isSubsetSum(nums2, 6)); // True
    }
}
