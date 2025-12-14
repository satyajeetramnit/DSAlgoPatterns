class Solution {
    public boolean isInterleave(String s1, String s2, String s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        
        int m = s1.length();
        int n = s2.length();
        boolean[] dp = new boolean[n + 1];
        dp[0] = true;
        
        for (int j = 1; j <= n; j++) {
            dp[j] = dp[j-1] && s2.charAt(j-1) == s3.charAt(j-1);
        }
        
        for (int i = 1; i <= m; i++) {
            dp[0] = dp[0] && s1.charAt(i-1) == s3.charAt(i-1);
            for (int j = 1; j <= n; j++) {
                boolean fromTop = dp[j] && s1.charAt(i-1) == s3.charAt(i+j-1);
                boolean fromLeft = dp[j-1] && s2.charAt(j-1) == s3.charAt(i+j-1);
                dp[j] = fromTop || fromLeft;
            }
        }
        
        return dp[n];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1: " + sol.isInterleave("aabcc", "dbbca", "aadbbcbcac")); // True
        System.out.println("Test Case 2: " + sol.isInterleave("aabcc", "dbbca", "aadbbbaccc")); // False
    }
}
