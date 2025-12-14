class Solution {
    public int findMaxForm(String[] strs, int m, int n) {
        int[][] dp = new int[m + 1][n + 1];
        
        for (String s : strs) {
            int zeros = 0;
            int ones = 0;
            for (char c : s.toCharArray()) {
                if (c == '0') zeros++;
                else ones++;
            }
            
            for (int i = m; i >= zeros; i--) {
                for (int j = n; j >= ones; j--) {
                    dp[i][j] = Math.max(dp[i][j], 1 + dp[i - zeros][j - ones]);
                }
            }
        }
        
        return dp[m][n];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        String[] strs1 = {"10","0001","111001","1","0"};
        System.out.println("Test Case 1: " + sol.findMaxForm(strs1, 5, 3)); // 4
        
        String[] strs2 = {"10","0","1"};
        System.out.println("Test Case 2: " + sol.findMaxForm(strs2, 1, 1)); // 2
    }
}
