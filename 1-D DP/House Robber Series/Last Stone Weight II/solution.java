class Solution {
    public int lastStoneWeightII(int[] stones) {
        int totalSum = 0;
        for (int s : stones) totalSum += s;
        int target = totalSum / 2;
        boolean[] dp = new boolean[target + 1];
        dp[0] = true;
        
        for (int stone : stones) {
            for (int j = target; j >= stone; j--) {
                if (dp[j - stone]) {
                    dp[j] = true;
                }
            }
        }
        
        for (int i = target; i >= 0; i--) {
            if (dp[i]) {
                return totalSum - 2 * i;
            }
        }
        return 0;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] stones1 = {2,7,4,1,8,1};
        System.out.println("Test Case 1: " + sol.lastStoneWeightII(stones1)); // 1
        
        int[] stones2 = {31,26,33,21,40};
        System.out.println("Test Case 2: " + sol.lastStoneWeightII(stones2)); // 5
    }
}
