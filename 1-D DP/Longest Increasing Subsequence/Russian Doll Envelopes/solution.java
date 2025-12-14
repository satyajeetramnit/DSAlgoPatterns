import java.util.Arrays;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

class Solution {
    public int maxEnvelopes(int[][] envelopes) {
        // Sort: width ascending, height descending
        Arrays.sort(envelopes, (a, b) -> {
            if (a[0] == b[0]) return b[1] - a[1];
            return a[0] - b[0];
        });
        
        List<Integer> tails = new ArrayList<>();
        
        for (int[] env : envelopes) {
            int h = env[1];
            int idx = Collections.binarySearch(tails, h);
            if (idx < 0) idx = -(idx + 1);
            
            if (idx == tails.size()) {
                tails.add(h);
            } else {
                tails.set(idx, h);
            }
        }
        
        return tails.size();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[][] envelopes1 = {{5,4},{6,4},{6,7},{2,3}};
        System.out.println("Test Case 1: " + sol.maxEnvelopes(envelopes1)); // 3
        
        int[][] envelopes2 = {{1,1},{1,1},{1,1}};
        System.out.println("Test Case 2: " + sol.maxEnvelopes(envelopes2)); // 1
    }
}
