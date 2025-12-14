import java.util.Arrays;
import java.util.Comparator;

class Solution {
    static class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n];
            for(int i=0; i<n; i++) parent[i] = i;
        }
        int find(int x) {
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        boolean union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
                return true;
            }
            return false;
        }
    }

    public int minSpanningTree(int V, int[][] edges) {
        Arrays.sort(edges, (a, b) -> Integer.compare(a[2], b[2]));
        
        DSU dsu = new DSU(V);
        int mstWeight = 0;
        
        for(int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            
            if(dsu.union(u, v)) {
                mstWeight += w;
            }
        }
        return mstWeight;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] edges1 = {{0,1,5}, {1,2,3}, {0,2,1}};
        System.out.println("MST 1: " + sol.minSpanningTree(3, edges1));

        int[][] edges2 = {{0,1,5}};
        System.out.println("MST 2: " + sol.minSpanningTree(2, edges2));
    }
}
