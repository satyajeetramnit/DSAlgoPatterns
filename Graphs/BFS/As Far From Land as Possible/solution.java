import java.util.LinkedList;
import java.util.Queue;

class Solution {
    public int maxDistance(int[][] grid) {
        int n = grid.length;
        Queue<int[]> q = new LinkedList<>();
        
        // Add all land cells to queue
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    q.offer(new int[]{i, j});
                }
            }
        }
        
        if(q.isEmpty() || q.size() == n * n) return -1;
        
        int dist = -1;
        int[][] dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        while(!q.isEmpty()) {
            int size = q.size();
            dist++;
            
            while(size-- > 0) {
                int[] curr = q.poll();
                
                for(int[] d : dirs) {
                    int nr = curr[0] + d[0];
                    int nc = curr[1] + d[1];
                    
                    if(nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 0) {
                        grid[nr][nc] = 1; // Mark visited
                        q.offer(new int[]{nr, nc});
                    }
                }
            }
        }
        return dist;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] grid1 = {{1,0,1},{0,0,0},{1,0,1}};
        System.out.println("Max Distance 1: " + sol.maxDistance(cloneGrid(grid1)));

        int[][] grid2 = {{1,0,0},{0,0,0},{0,0,0}};
        System.out.println("Max Distance 2: " + sol.maxDistance(cloneGrid(grid2)));
        
        int[][] grid3 = {{0,0,0}};
        System.out.println("Max Distance 3: " + sol.maxDistance(cloneGrid(grid3)));
    }

    private static int[][] cloneGrid(int[][] grid) {
        int[][] newGrid = new int[grid.length][];
        for(int i = 0; i < grid.length; i++) {
            newGrid[i] = grid[i].clone();
        }
        return newGrid;
    }
}
