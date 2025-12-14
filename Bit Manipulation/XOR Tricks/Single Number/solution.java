import java.util.Arrays;

class Solution {
    // Single Number I
    public int singleNumber(int[] nums) {
        int res = 0;
        for (int n : nums) res ^= n;
        return res;
    }

    // Single Number II
    public int singleNumberII(int[] nums) {
        int ones = 0, twos = 0;
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }

    // Single Number III
    public int[] singleNumberIII(int[] nums) {
        int diff = 0;
        for (int n : nums) diff ^= n;
        
        diff &= -diff;
        
        int[] res = new int[2];
        for (int n : nums) {
            if ((n & diff) == 0) res[0] ^= n;
            else res[1] ^= n;
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        // I
        int[] nums1 = {2,2,1};
        System.out.println("Single Number I (2,2,1): " + sol.singleNumber(nums1)); // 1
        
        // II
        int[] nums2 = {2,2,3,2};
        System.out.println("Single Number II (2,2,3,2): " + sol.singleNumberII(nums2)); // 3
        
        // III
        int[] nums3 = {1,2,1,3,2,5};
        int[] res3 = sol.singleNumberIII(nums3);
        System.out.println("Single Number III (1,2,1,3,2,5): " + Arrays.toString(res3)); // [3, 5]
    }
}
