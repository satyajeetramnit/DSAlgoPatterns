import java.util.PriorityQueue;
import java.util.Arrays;
import java.util.Comparator;

class Solution {
    public int findMaximizedCapital(int k, int w, int[] profits, int[] capital) {
        int n = profits.length;
        int[][] projects = new int[n][2];
        for (int i = 0; i < n; i++) {
            projects[i][0] = capital[i];
            projects[i][1] = profits[i];
        }
        
        // Sort by capital increasing
        Arrays.sort(projects, Comparator.comparingInt(a -> a[0]));
        
        PriorityQueue<Integer> maxProfit = new PriorityQueue<>((a, b) -> b - a);
        int i = 0;
        
        while (k-- > 0) {
            while (i < n && projects[i][0] <= w) {
                maxProfit.add(projects[i][1]);
                i++;
            }
            
            if (maxProfit.isEmpty()) break;
            
            w += maxProfit.poll();
        }
        
        return w;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int k = 2;
        int w = 0;
        int[] profits = {1, 2, 3};
        int[] capital = {0, 1, 1};
        System.out.println("Test Case 1: " + sol.findMaximizedCapital(k, w, profits, capital)); // Expect 4
    }
}
