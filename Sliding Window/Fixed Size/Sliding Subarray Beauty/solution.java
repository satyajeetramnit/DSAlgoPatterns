import java.util.Arrays;

class Solution {
    public int[] getSubarrayBeauty(int[] nums, int k, int x) {
        int[] count = new int[101]; // -50 to 50
        int n = nums.length;
        int[] result = new int[n - k + 1];
        
        for (int i = 0; i < k; i++) {
            count[nums[i] + 50]++;
        }
        
        result[0] = findXth(count, x);
        
        for (int i = k; i < n; i++) {
            count[nums[i] + 50]++;
            count[nums[i - k] + 50]--;
            result[i - k + 1] = findXth(count, x);
        }
        return result;
    }
    
    private int findXth(int[] count, int x) {
        int currentCount = 0;
        // Check -50 to -1 (indices 0 to 49)
        for (int i = 0; i < 50; i++) {
            currentCount += count[i];
            if (currentCount >= x) {
                return i - 50;
            }
        }
        return 0;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {1, -1, -3, -2, 3};
        int k1 = 3, x1 = 2;
        int[] res1 = sol.getSubarrayBeauty(nums1, k1, x1);
        System.out.println("Beauty 1: " + Arrays.toString(res1)); // Expected: [-1, -2, -2]

        int[] nums2 = {-1, -2, -3};
        int k2 = 2, x2 = 1;
        int[] res2 = sol.getSubarrayBeauty(nums2, k2, x2);
        System.out.println("Beauty 2: " + Arrays.toString(res2)); // Expected: [-2, -3]
    }
}
