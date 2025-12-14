import java.util.Arrays;

class Solution {
    public int[] findArray(int[] pref) {
        int n = pref.length;
        int[] arr = new int[n];
        arr[0] = pref[0];
        
        for (int i = 1; i < n; i++) {
            arr[i] = pref[i] ^ pref[i-1];
        }
        return arr;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] pref1 = {5,2,0,3,1};
        System.out.println("Test Case 1: " + Arrays.toString(sol.findArray(pref1))); // [5, 7, 2, 3, 2]
        
        int[] pref2 = {13};
        System.out.println("Test Case 2: " + Arrays.toString(sol.findArray(pref2))); // [13]
    }
}
