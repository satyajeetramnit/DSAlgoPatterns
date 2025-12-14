class Solution {
    private int count = 0;

    public int totalNQueens(int n) {
        count = 0;
        solve(0, 0, 0, 0, n);
        return count;
    }

    private void solve(int row, int cols, int diag1, int diag2, int n) {
        if (row == n) {
            count++;
            return;
        }

        int availablePositions = ((1 << n) - 1) & ~(cols | diag1 | diag2);

        while (availablePositions != 0) {
            int position = availablePositions & -availablePositions;
            availablePositions &= availablePositions - 1;
            
            solve(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1, n);
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1 (n=4): " + sol.totalNQueens(4)); // 2
        System.out.println("Test Case 2 (n=1): " + sol.totalNQueens(1)); // 1
        System.out.println("Test Case 3 (n=8): " + sol.totalNQueens(8)); // 92
    }
}
