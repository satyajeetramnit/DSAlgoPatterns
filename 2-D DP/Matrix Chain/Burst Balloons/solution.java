class Solution {
    public int maxCoins(int[] nums) {
        int n = nums.length;
        int[] paddedNums = new int[n + 2];
        paddedNums[0] = 1;
        paddedNums[n + 1] = 1;
        for (int i = 0; i < n; i++) paddedNums[i + 1] = nums[i];
        
        int[][] dp = new int[n + 2][n + 2];
        
        for (int len = 1; len <= n; len++) {
            for (int left = 0; left < n + 2 - len - 1; left++) {
                int right = left + len + 1;
                for (int k = left + 1; k < right; k++) {
                    dp[left][right] = Math.max(dp[left][right], 
                        paddedNums[left] * paddedNums[k] * paddedNums[right] + dp[left][k] + dp[k][right]);
                }
            }
        }
        
        return dp[0][n + 1];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {3,1,5,8};
        System.out.println("Test Case 1: " + sol.maxCoins(nums1)); // 167
        int[] nums2 = {1,5};
        System.out.println("Test Case 2: " + sol.maxCoins(nums2)); // 10
    }
}
