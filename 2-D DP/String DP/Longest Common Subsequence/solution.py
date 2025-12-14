class Solution:
    def longestCommonSubsequence(self, text1: str, text2: str) -> int:
        if len(text1) < len(text2):
            text1, text2 = text2, text1
            
        m, n = len(text1), len(text2)
        dp = [0] * (n + 1)
        
        for i in range(1, m + 1):
            prev = 0
            for j in range(1, n + 1):
                temp = dp[j]
                if text1[i-1] == text2[j-1]:
                    dp[j] = 1 + prev
                else:
                    dp[j] = max(dp[j], dp[j-1])
                prev = temp
                
        return dp[n]

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.longestCommonSubsequence('abcde', 'ace')}") # 3
    print(f"Test Case 2: {sol.longestCommonSubsequence('abc', 'abc')}") # 3
    print(f"Test Case 3: {sol.longestCommonSubsequence('abc', 'def')}") # 0
