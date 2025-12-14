from typing import List

class Solution:
    def findMaxForm(self, strs: List[str], m: int, n: int) -> int:
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        
        for s in strs:
            zeros = s.count('0')
            ones = s.count('1')
            
            for i in range(m, zeros - 1, -1):
                for j in range(n, ones - 1, -1):
                    dp[i][j] = max(dp[i][j], 1 + dp[i - zeros][j - ones])
                    
        return dp[m][n]

if __name__ == "__main__":
    sol = Solution()
    
    strs1 = ["10","0001","111001","1","0"]
    print(f"Test Case 1: {sol.findMaxForm(strs1, 5, 3)}") # 4
    
    strs2 = ["10","0","1"]
    print(f"Test Case 2: {sol.findMaxForm(strs2, 1, 1)}") # 2
