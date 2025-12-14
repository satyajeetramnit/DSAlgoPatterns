import java.util.Arrays;

class Solution {
    public int[] xorQueries(int[] arr, int[][] queries) {
        // Clone to keep pure if needed, but standard solutions modify in-place or use prefix array
        int[] P = arr.clone();
        int n = P.length;
        for (int i = 1; i < n; i++) {
            P[i] ^= P[i-1];
        }
        
        int[] res = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int L = queries[i][0];
            int R = queries[i][1];
            if (L > 0) res[i] = P[R] ^ P[L-1];
            else res[i] = P[R];
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] arr1 = {1,3,4,8};
        int[][] q1 = {{0,1},{1,2},{0,3},{3,3}};
        System.out.println("Test Case 1: " + Arrays.toString(sol.xorQueries(arr1, q1))); // [2, 7, 14, 8]
        
        int[] arr2 = {4,8,2,10};
        int[][] q2 = {{2,3},{1,3},{0,0},{0,3}};
        System.out.println("Test Case 2: " + Arrays.toString(sol.xorQueries(arr2, q2))); // [8, 0, 4, 4]
    }
}
