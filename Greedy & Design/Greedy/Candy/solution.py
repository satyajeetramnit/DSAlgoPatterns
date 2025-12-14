from typing import List

class Solution:
    def candy(self, ratings: List[int]) -> int:
        n = len(ratings)
        candies = [1] * n
        
        # Left to Right
        for i in range(1, n):
            if ratings[i] > ratings[i-1]:
                candies[i] = candies[i-1] + 1
        
        # Right to Left
        for i in range(n - 2, -1, -1):
            if ratings[i] > ratings[i+1]:
                candies[i] = max(candies[i], candies[i+1] + 1)
                
        return sum(candies)

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1: {sol.candy([1,0,2])}") # Expect 5
    print(f"Test Case 2: {sol.candy([1,2,2])}") # Expect 4
