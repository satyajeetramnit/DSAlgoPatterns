class Solution {
    public int minPathSum(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;
                else if (i == 0) grid[i][j] += grid[i][j-1];
                else if (j == 0) grid[i][j] += grid[i-1][j];
                else grid[i][j] += Math.min(grid[i-1][j], grid[i][j-1]);
            }
        }
        return grid[m-1][n-1];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] grid1 = {{1,3,1},{1,5,1},{4,2,1}};
        System.out.println("Test Case 1: " + sol.minPathSum(grid1)); // 7
        
        int[][] grid2 = {{1,2,3},{4,5,6}};
        System.out.println("Test Case 2: " + sol.minPathSum(grid2)); // 12
    }
}
