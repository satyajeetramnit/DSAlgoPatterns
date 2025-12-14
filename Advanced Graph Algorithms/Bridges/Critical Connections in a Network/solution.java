import java.util.*;

class Solution {
    private List<List<Integer>> adj;
    private int[] disc;
    private int[] low;
    private int time;
    private List<List<Integer>> bridges;

    public List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        adj = new ArrayList<>();
        for (int i = 0; i < n; i++) adj.add(new ArrayList<>());
        for (List<Integer> edge : connections) {
            adj.get(edge.get(0)).add(edge.get(1));
            adj.get(edge.get(1)).add(edge.get(0));
        }
        
        disc = new int[n];
        Arrays.fill(disc, -1);
        low = new int[n];
        time = 0;
        bridges = new ArrayList<>();
        
        dfs(0, -1);
        return bridges;
    }
    
    private void dfs(int u, int p) {
        disc[u] = low[u] = time++;
        
        for (int v : adj.get(u)) {
            if (v == p) continue;
            
            if (disc[v] != -1) {
                low[u] = Math.min(low[u], disc[v]);
            } else {
                dfs(v, u);
                low[u] = Math.min(low[u], low[v]);
                if (low[v] > disc[u]) {
                    List<Integer> bridge = new ArrayList<>();
                    if (u < v) { bridge.add(u); bridge.add(v); }
                    else { bridge.add(v); bridge.add(u); }
                    bridges.add(bridge);
                }
            }
        }
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        // Test 1
        List<List<Integer>> conn1 = new ArrayList<>();
        conn1.add(Arrays.asList(0, 1));
        conn1.add(Arrays.asList(1, 2));
        conn1.add(Arrays.asList(2, 0));
        conn1.add(Arrays.asList(1, 3));
        
        List<List<Integer>> res1 = sol.criticalConnections(4, conn1);
        assert res1.size() == 1;
        assert res1.get(0).get(0) == 1 && res1.get(0).get(1) == 3 : "Test 1 Failed: " + res1;
        System.out.println("Test 1 Passed");
        
        // Test 2
        List<List<Integer>> conn2 = new ArrayList<>();
        conn2.add(Arrays.asList(0, 1));
        List<List<Integer>> res2 = sol.criticalConnections(2, conn2);
        assert res2.size() == 1;
        assert res2.get(0).get(0) == 0 && res2.get(0).get(1) == 1 : "Test 2 Failed";
        System.out.println("Test 2 Passed");
    }
}
