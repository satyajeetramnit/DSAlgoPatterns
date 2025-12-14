class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        dp = [1] * n
        
        for i in range(1, m):
            for j in range(1, n):
                dp[j] += dp[j-1]
                
        return dp[n-1]

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (m=3, n=7): {sol.uniquePaths(3, 7)}") # 28
    print(f"Test Case 2 (m=3, n=2): {sol.uniquePaths(3, 2)}") # 3
    print(f"Test Case 3 (m=7, n=3): {sol.uniquePaths(7, 3)}") # 28
    print(f"Test Case 4 (m=1, n=1): {sol.uniquePaths(1, 1)}") # 1
