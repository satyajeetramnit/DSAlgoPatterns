class Solution {
    public int uniquePaths(int m, int n) {
        int[] dp = new int[n];
        for(int i=0; i<n; i++) dp[i] = 1;
        
        for(int i=1; i<m; i++) {
            for(int j=1; j<n; j++) {
                dp[j] += dp[j-1];
            }
        }
        return dp[n-1];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1 (m=3, n=7): " + sol.uniquePaths(3, 7)); // 28
        System.out.println("Test Case 2 (m=3, n=2): " + sol.uniquePaths(3, 2)); // 3
        System.out.println("Test Case 3 (m=7, n=3): " + sol.uniquePaths(7, 3)); // 28
        System.out.println("Test Case 4 (m=1, n=1): " + sol.uniquePaths(1, 1)); // 1
    }
}
