class Solution:
    def totalNQueens(self, n: int) -> int:
        self.count = 0
        self.solve(0, 0, 0, 0, n)
        return self.count

    def solve(self, row, cols, diag1, diag2, n):
        if (row == n):
            self.count += 1
            return
        
        available_positions = ((1 << n) - 1) & ~(cols | diag1 | diag2)
        
        while available_positions:
            position = available_positions & -available_positions
            available_positions &= available_positions - 1
            
            self.solve(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1, n)

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (n=4): {sol.totalNQueens(4)}") # 2
    print(f"Test Case 2 (n=1): {sol.totalNQueens(1)}") # 1
    print(f"Test Case 3 (n=8): {sol.totalNQueens(8)}") # 92
