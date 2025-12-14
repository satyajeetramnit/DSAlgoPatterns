class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        if len(s1) + len(s2) != len(s3):
            return False
            
        m, n = len(s1), len(s2)
        dp = [False] * (n + 1)
        dp[0] = True
        
        for j in range(1, n + 1):
            dp[j] = dp[j-1] and s2[j-1] == s3[j-1]
            
        for i in range(1, m + 1):
            dp[0] = dp[0] and s1[i-1] == s3[i-1]
            for j in range(1, n + 1):
                from_top = dp[j] and s1[i-1] == s3[i+j-1]
                from_left = dp[j-1] and s2[j-1] == s3[i+j-1]
                dp[j] = from_top or from_left
                
        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.isInterleave('aabcc', 'dbbca', 'aadbbcbcac')}") # True
    print(f"Test Case 2: {sol.isInterleave('aabcc', 'dbbca', 'aadbbbaccc')}") # False
