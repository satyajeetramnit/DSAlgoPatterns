class Solution:
    def nthUglyNumber(self, n: int) -> int:
        dp = [0] * n
        dp[0] = 1
        p2 = p3 = p5 = 0
        
        for i in range(1, n):
            next2 = dp[p2] * 2
            next3 = dp[p3] * 3
            next5 = dp[p5] * 5
            
            dp[i] = min(next2, next3, next5)
            
            if dp[i] == next2:
                p2 += 1
            if dp[i] == next3:
                p3 += 1
            if dp[i] == next5:
                p5 += 1
                
        return dp[n - 1]

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (n=10): {sol.nthUglyNumber(10)}") # Expect 12
    print(f"Test Case 2 (n=1): {sol.nthUglyNumber(1)}")   # Expect 1
