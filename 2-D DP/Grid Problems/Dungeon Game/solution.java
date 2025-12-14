class Solution {
    public int calculateMinimumHP(int[][] dungeon) {
        int m = dungeon.length;
        int n = dungeon[0].length;
        
        int[][] dp = new int[m + 1][n + 1];
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = Integer.MAX_VALUE;
            }
        }
        
        dp[m][n-1] = 1;
        dp[m-1][n] = 1;
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                int need = Math.min(dp[i+1][j], dp[i][j+1]) - dungeon[i][j];
                dp[i][j] = Math.max(1, need);
            }
        }
        
        return dp[0][0];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] dungeon1 = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
        System.out.println("Test Case 1: " + sol.calculateMinimumHP(dungeon1)); // 7
        
        int[][] dungeon2 = {{0}};
        System.out.println("Test Case 2: " + sol.calculateMinimumHP(dungeon2)); // 1
    }
}
