class Solution {
    public int closedIsland(int[][] grid) {
        if(grid == null || grid.length == 0) return 0;
        int m = grid.length;
        int n = grid[0].length;
        
        // 1. Flood fill boundaries
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if((i == 0 || j == 0 || i == m - 1 || j == n - 1) && grid[i][j] == 0) {
                    dfs(grid, i, j, m, n);
                }
            }
        }
        
        // 2. Count remaining
        int count = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    count++;
                    dfs(grid, i, j, m, n);
                }
            }
        }
        return count;
    }
    
    private void dfs(int[][] grid, int r, int c, int m, int n) {
        if(r < 0 || c < 0 || r >= m || c >= n || grid[r][c] == 1) return;
        
        grid[r][c] = 1; // Mark as visited
        
        dfs(grid, r + 1, c, m, n);
        dfs(grid, r - 1, c, m, n);
        dfs(grid, r, c + 1, m, n);
        dfs(grid, r, c - 1, m, n);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] grid1 = {
            {1,1,1,1,1,1,1,0},
            {1,0,0,0,0,1,1,0},
            {1,0,1,0,1,1,1,0},
            {1,0,0,0,0,1,0,1},
            {1,1,1,1,1,1,1,0}
        };
        System.out.println("Closed Islands 1: " + sol.closedIsland(cloneGrid(grid1)));

        int[][] grid2 = {
            {0,0,1,0,0},
            {0,1,0,1,0},
            {0,1,1,1,0}
        };
        System.out.println("Closed Islands 2: " + sol.closedIsland(cloneGrid(grid2)));
    }

    private static int[][] cloneGrid(int[][] grid) {
        int[][] newGrid = new int[grid.length][];
        for(int i = 0; i < grid.length; i++) {
            newGrid[i] = grid[i].clone();
        }
        return newGrid;
    }
}
