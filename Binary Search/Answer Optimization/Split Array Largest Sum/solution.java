class Solution {
    public int splitArray(int[] nums, int k) {
        long left = 0, right = 0;
        for (int n : nums) {
            left = Math.max(left, n);
            right += n;
        }

        while (left <= right) {
            long mid = left + (right - left) / 2;
            if (canSplit(nums, k, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return (int)left;
    }

    private boolean canSplit(int[] nums, int k, long maxSum) {
        int subarrays = 1;
        long currentSum = 0;
        
        for (int n : nums) {
            if (currentSum + n > maxSum) {
                subarrays++;
                currentSum = n;
            } else {
                currentSum += n;
            }
        }
        return subarrays <= k;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {7,2,5,10,8};
        int k1 = 2;
        System.out.println("Min Largest Sum 1: " + sol.splitArray(nums1, k1)); // Expected: 18

        int[] nums2 = {1,2,3,4,5};
        int k2 = 2;
        System.out.println("Min Largest Sum 2: " + sol.splitArray(nums2, k2)); // Expected: 9
    }
}
