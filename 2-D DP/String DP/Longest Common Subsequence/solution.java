class Solution {
    public int longestCommonSubsequence(String text1, String text2) {
        if (text1.length() < text2.length()) {
            return longestCommonSubsequence(text2, text1);
        }
        
        int m = text1.length();
        int n = text2.length();
        int[] dp = new int[n + 1];
        
        for (int i = 1; i <= m; i++) {
            int prev = 0;
            for (int j = 1; j <= n; j++) {
                int temp = dp[j];
                if (text1.charAt(i-1) == text2.charAt(j-1)) {
                    dp[j] = 1 + prev;
                } else {
                    dp[j] = Math.max(dp[j], dp[j-1]);
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1: " + sol.longestCommonSubsequence("abcde", "ace")); // 3
        System.out.println("Test Case 2: " + sol.longestCommonSubsequence("abc", "abc")); // 3
        System.out.println("Test Case 3: " + sol.longestCommonSubsequence("abc", "def")); // 0
    }
}
