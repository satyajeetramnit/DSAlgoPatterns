class Solution {
    public boolean canPartition(int[] nums) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;
        
        if (totalSum % 2 != 0) return false;
        
        int target = totalSum / 2;
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;
        
        for (int num : nums) {
            for (int j = target; j >= num; j--) {
                if (dp[j - num]) {
                    dp[j] = true;
                }
            }
        }
        
        return dp[target];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {1, 5, 11, 5};
        System.out.println("Test Case 1: " + sol.canPartition(nums1)); // True
        
        int[] nums2 = {1, 2, 3, 5};
        System.out.println("Test Case 2: " + sol.canPartition(nums2)); // False
    }
}
