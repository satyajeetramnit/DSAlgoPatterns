import java.util.Arrays;

class Solution {
    static class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n + 1];
            for(int i=0; i<=n; i++) parent[i] = i;
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

    public int[] findRedundantConnection(int[][] edges) {
        int n = edges.length;
        DSU dsu = new DSU(n);
        
        for(int[] edge : edges) {
            if(!dsu.union(edge[0], edge[1])) {
                return edge;
            }
        }
        return new int[0];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] edges1 = {{1,2}, {1,3}, {2,3}};
        System.out.println("Redundant 1: " + Arrays.toString(sol.findRedundantConnection(edges1)));

        int[][] edges2 = {{1,2}, {2,3}, {3,4}, {1,4}, {1,5}};
        System.out.println("Redundant 2: " + Arrays.toString(sol.findRedundantConnection(edges2)));
    }
}
