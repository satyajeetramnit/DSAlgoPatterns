import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int shortestPathBinaryMatrix(int[][] grid) {
        int n = grid.length;
        if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
        
        Queue<int[]> q = new LinkedList<>();
        q.offer(new int[]{0, 0});
        grid[0][0] = 1; // Mark visited
        
        int[][] directions = {
            {-1,-1}, {-1,0}, {-1,1},
            {0,-1},          {0,1},
            {1,-1},  {1,0},  {1,1}
        };
        
        int pathLen = 1;
        
        while (!q.isEmpty()) {
            int size = q.size();
            while (size-- > 0) {
                int[] curr = q.poll();
                int r = curr[0];
                int c = curr[1];
                
                if (r == n - 1 && c == n - 1) return pathLen;
                
                for (int[] dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        q.offer(new int[]{nr, nc});
                        grid[nr][nc] = 1; // Mark visited
                    }
                }
            }
            pathLen++;
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] grid1 = {{0,1},{1,0}};
        System.out.println("Shortest Path 1: " + sol.shortestPathBinaryMatrix(cloneGrid(grid1)));

        int[][] grid2 = {{0,0,0},{1,1,0},{1,1,0}};
        System.out.println("Shortest Path 2: " + sol.shortestPathBinaryMatrix(cloneGrid(grid2)));
        
        int[][] grid3 = {{1,0,0},{1,1,0},{1,1,0}};
        System.out.println("Shortest Path 3: " + sol.shortestPathBinaryMatrix(cloneGrid(grid3)));
    }

    private static int[][] cloneGrid(int[][] grid) {
        int[][] newGrid = new int[grid.length][];
        for(int i = 0; i < grid.length; i++) {
            newGrid[i] = grid[i].clone();
        }
        return newGrid;
    }
}
