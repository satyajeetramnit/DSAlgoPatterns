class Solution {
    static class DSU {
        int[] parent;
        int count;
        
        DSU(int n) {
            parent = new int[n];
            for(int i=0; i<n; i++) parent[i] = i;
            count = n;
        }
        int find(int x) {
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void union(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if(rootX != rootY) {
                parent[rootX] = rootY;
                count--;
            }
        }
    }

    public int findCircleNum(int[][] isConnected) {
        int n = isConnected.length;
        DSU dsu = new DSU(n);
        
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(isConnected[i][j] == 1) {
                    dsu.union(i, j);
                }
            }
        }
        return dsu.count;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[][] isConnected1 = {{1,1,0},{1,1,0},{0,0,1}};
        System.out.println("Provinces 1: " + sol.findCircleNum(isConnected1));

        int[][] isConnected2 = {{1,0,0},{0,1,0},{0,0,1}};
        System.out.println("Provinces 2: " + sol.findCircleNum(isConnected2));
    }
}
