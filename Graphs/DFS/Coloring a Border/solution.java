import java.util.ArrayList;
import java.util.List;
import java.util.Arrays;

class Solution {
    public int[][] colorBorder(int[][] grid, int row, int col, int color) {
        int oldColor = grid[row][col];
        int m = grid.length;
        int n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        List<int[]> borders = new ArrayList<>();
        
        dfs(grid, row, col, oldColor, visited, borders);
        
        for(int[] p : borders) {
            grid[p[0]][p[1]] = color;
        }
        return grid;
    }
    
    private void dfs(int[][] grid, int r, int c, int oldColor, 
                     boolean[][] visited, List<int[]> borders) {
        visited[r][c] = true;
        boolean isBorder = false;
        int[][] dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        for(int[] d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];
            
            if(nr < 0 || nr >= grid.length || nc < 0 || nc >= grid[0].length) {
                isBorder = true;
            } else if(grid[nr][nc] != oldColor) {
                isBorder = true;
            } else if(!visited[nr][nc]) {
                dfs(grid, nr, nc, oldColor, visited, borders);
            }
        }
        
        if(isBorder) {
            borders.add(new int[]{r, c});
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] grid1 = {{1,1},{1,2}};
        printGrid(sol.colorBorder(cloneGrid(grid1), 0, 0, 3));

        int[][] grid2 = {{1,2,2},{2,3,2}};
        printGrid(sol.colorBorder(cloneGrid(grid2), 0, 1, 3));
    }
    
    private static int[][] cloneGrid(int[][] grid) {
        int[][] newGrid = new int[grid.length][];
        for(int i = 0; i < grid.length; i++) {
            newGrid[i] = grid[i].clone();
        }
        return newGrid;
    }
    
    private static void printGrid(int[][] grid) {
        System.out.print("[");
        for(int i = 0; i < grid.length; i++) {
            System.out.print(Arrays.toString(grid[i]) + (i < grid.length - 1 ? "," : ""));
        }
        System.out.println("]");
    }
}
