import java.util.ArrayList;
import java.util.Arrays;
import java.util.PriorityQueue;

class Solution {
    static class Node implements Comparable<Node> {
        int v, weight;
        Node(int v, int weight) { this.v = v; this.weight = weight; }
        public int compareTo(Node that) { return this.weight - that.weight; }
    }
    
    public int[] dijkstra(int V, ArrayList<ArrayList<ArrayList<Integer>>> adj, int S) {
        PriorityQueue<Node> pq = new PriorityQueue<>();
        int[] dist = new int[V];
        Arrays.fill(dist, Integer.MAX_VALUE);
        
        dist[S] = 0;
        pq.add(new Node(S, 0));
        
        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int u = node.v;
            int d = node.weight;
            
            if (d > dist[u]) continue;
            
            for (ArrayList<Integer> edge : adj.get(u)) {
                int v = edge.get(0);
                int w = edge.get(1);
                
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    pq.add(new Node(v, dist[v]));
                }
            }
        }
        return dist;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int V = 3;
        int S = 2;
        
        ArrayList<ArrayList<ArrayList<Integer>>> adj = new ArrayList<>();
        for(int i = 0; i < V; i++) adj.add(new ArrayList<>());
        
        // 2->1 w=1
        ArrayList<Integer> edge1 = new ArrayList<>(); edge1.add(1); edge1.add(1);
        adj.get(2).add(edge1);
        
        // 2->0 w=6
        ArrayList<Integer> edge2 = new ArrayList<>(); edge2.add(0); edge2.add(6);
        adj.get(2).add(edge2);
        
        // 1->0 w=3
        ArrayList<Integer> edge3 = new ArrayList<>(); edge3.add(0); edge3.add(3);
        adj.get(1).add(edge3);
        
        int[] res = sol.dijkstra(V, adj, S);
        System.out.print("Distances: ");
        for(int d : res) System.out.print(d + " ");
        System.out.println();
    }
}
