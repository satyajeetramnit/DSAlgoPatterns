from typing import List

class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        if not grid: return 0
        m, n = len(grid), len(grid[0])
        
        # We process a copy or careful modify to avoid testing issues if re-run, 
        # but problem allows modification usually. Here we modify in-place.
        # Note: Test case runner re-initializes usually.
        
        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                elif i == 0:
                    grid[i][j] += grid[i][j-1]
                elif j == 0:
                    grid[i][j] += grid[i-1][j]
                else:
                    grid[i][j] += min(grid[i-1][j], grid[i][j-1])
                    
        return grid[m-1][n-1]

if __name__ == "__main__":
    sol = Solution()
    
    grid1 = [[1,3,1],[1,5,1],[4,2,1]]
    print(f"Test Case 1: {sol.minPathSum(grid1)}") # 7
    
    grid2 = [[1,2,3],[4,5,6]]
    print(f"Test Case 2: {sol.minPathSum(grid2)}") # 12
