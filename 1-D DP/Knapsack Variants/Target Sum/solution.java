class Solution {
    public int findTargetSumWays(int[] nums, int target) {
        int totalSum = 0;
        for (int num : nums) totalSum += num;
        
        if ((totalSum + target) < 0 || (totalSum + target) % 2 != 0) {
            return 0;
        }
        
        int subsetTarget = (totalSum + target) / 2;
        int[] dp = new int[subsetTarget + 1];
        dp[0] = 1;
        
        for (int num : nums) {
            for (int j = subsetTarget; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        
        return dp[subsetTarget];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {1, 1, 1, 1, 1};
        System.out.println("Test Case 1 (Target 3): " + sol.findTargetSumWays(nums1, 3)); // 5
        
        int[] nums2 = {1};
        System.out.println("Test Case 2 (Target 1): " + sol.findTargetSumWays(nums2, 1)); // 1
    }
}
