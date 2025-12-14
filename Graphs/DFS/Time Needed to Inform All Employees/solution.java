import java.util.ArrayList;
import java.util.List;

class Solution {
    public int numOfMinutes(int n, int headID, int[] manager, int[] informTime) {
        List<List<Integer>> adj = new ArrayList<>();
        for(int i = 0; i < n; i++) adj.add(new ArrayList<>());
        
        for(int i = 0; i < n; i++) {
            if(manager[i] != -1) {
                adj.get(manager[i]).add(i);
            }
        }
        
        return dfs(headID, adj, informTime);
    }
    
    private int dfs(int u, List<List<Integer>> adj, int[] informTime) {
        int maxSubTime = 0;
        for(int v : adj.get(u)) {
            maxSubTime = Math.max(maxSubTime, dfs(v, adj, informTime));
        }
        return informTime[u] + maxSubTime;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] manager1 = {2,2,-1,2,2,2};
        int[] informTime1 = {0,0,1,0,0,0};
        System.out.println("Time 1: " + sol.numOfMinutes(6, 2, manager1, informTime1));

        int[] manager2 = {1,2,3,4,5,6,-1};
        int[] informTime2 = {0,6,5,4,3,2,1};
        System.out.println("Time 2: " + sol.numOfMinutes(7, 6, manager2, informTime2));
    }
}
