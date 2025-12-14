import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.List;
import java.util.Arrays;

class Solution {
    public int[] findOrder(int numCourses, int[][] prerequisites) {
        List<List<Integer>> adj = new ArrayList<>();
        for(int i = 0; i < numCourses; i++) adj.add(new ArrayList<>());
        
        int[] inDegree = new int[numCourses];
        
        for(int[] edge : prerequisites) {
            adj.get(edge[1]).add(edge[0]);
            inDegree[edge[0]]++;
        }
        
        Queue<Integer> q = new LinkedList<>();
        for(int i = 0; i < numCourses; i++) {
            if(inDegree[i] == 0) q.offer(i);
        }
        
        int[] order = new int[numCourses];
        int idx = 0;
        
        while(!q.isEmpty()) {
            int u = q.poll();
            order[idx++] = u;
            
            for(int v : adj.get(u)) {
                inDegree[v]--;
                if(inDegree[v] == 0) q.offer(v);
            }
        }
        
        return idx == numCourses ? order : new int[0];
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] pre1 = {{1,0}};
        System.out.println("Order 1: " + Arrays.toString(sol.findOrder(2, pre1)));

        int[][] pre2 = {{1,0},{2,0},{3,1},{3,2}};
        System.out.println("Order 2: " + Arrays.toString(sol.findOrder(4, pre2)));
        
        int[][] pre3 = {{1,0},{0,1}};
        System.out.println("Order 3: " + Arrays.toString(sol.findOrder(2, pre3)));
    }
}
