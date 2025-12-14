import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int orangesRotting(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        
        Queue<int[]> q = new LinkedList<>();
        int freshCount = 0;
        
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 2) {
                    q.offer(new int[]{i, j});
                } else if(grid[i][j] == 1) {
                    freshCount++;
                }
            }
        }
        
        if(freshCount == 0) return 0;
        
        int minutes = 0;
        int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        while(!q.isEmpty() && freshCount > 0) {
            int size = q.size();
            while(size-- > 0) {
                int[] curr = q.poll();
                int r = curr[0];
                int c = curr[1];
                
                for(int[] dir : directions) {
                    int nr = r + dir[0];
                    int nc = c + dir[1];
                    
                    if(nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                        grid[nr][nc] = 2; // Rot it
                        freshCount--;
                        q.offer(new int[]{nr, nc});
                    }
                }
            }
            minutes++;
        }
        
        return freshCount == 0 ? minutes : -1;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] grid1 = {{2,1,1},{1,1,0},{0,1,1}};
        System.out.println("Rotten Oranges 1: " + sol.orangesRotting(cloneGrid(grid1)));

        int[][] grid2 = {{2,1,1},{0,1,1},{1,0,1}};
        System.out.println("Rotten Oranges 2: " + sol.orangesRotting(cloneGrid(grid2)));

        int[][] grid3 = {{0,2}};
        System.out.println("Rotten Oranges 3: " + sol.orangesRotting(cloneGrid(grid3)));
    }

    private static int[][] cloneGrid(int[][] grid) {
        int[][] newGrid = new int[grid.length][];
        for(int i = 0; i < grid.length; i++) {
            newGrid[i] = grid[i].clone();
        }
        return newGrid;
    }
}
