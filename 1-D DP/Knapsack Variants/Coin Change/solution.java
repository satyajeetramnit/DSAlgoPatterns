import java.util.Arrays;

class Solution {
    public int coinChange(int[] coins, int amount) {
        int max = amount + 1;
        int[] dp = new int[amount + 1];
        Arrays.fill(dp, max);
        dp[0] = 0;
        
        for (int i = 1; i <= amount; i++) {
            for (int coin : coins) {
                if (i - coin >= 0) {
                    dp[i] = Math.min(dp[i], dp[i - coin] + 1);
                }
            }
        }
        return (dp[amount] > amount) ? -1 : dp[amount];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] coins1 = {1, 2, 5};
        System.out.println("Test Case 1 (Amt 11): " + sol.coinChange(coins1, 11)); // 3
        
        int[] coins2 = {2};
        System.out.println("Test Case 2 (Amt 3): " + sol.coinChange(coins2, 3)); // -1
        
        int[] coins3 = {1};
        System.out.println("Test Case 3 (Amt 0): " + sol.coinChange(coins3, 0)); // 0
    }
}
