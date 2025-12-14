class Solution {
    public int maxSumSubarray(int[] nums, int k) {
        if (nums.length < k) return -1;

        long currentSum = 0;
        for (int i = 0; i < k; i++) {
            currentSum += nums[i];
        }

        long maxSum = currentSum;
        for (int i = k; i < nums.length; i++) {
            currentSum += nums[i] - nums[i - k];
            maxSum = Math.max(maxSum, currentSum);
        }
        return (int)maxSum;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {2, 1, 5, 1, 3, 2};
        int k1 = 3;
        System.out.println("Max Sum 1: " + sol.maxSumSubarray(nums1, k1)); // Expected: 9

        int[] nums2 = {2, 3, 4, 1, 5};
        int k2 = 2;
        System.out.println("Max Sum 2: " + sol.maxSumSubarray(nums2, k2)); // Expected: 7
    }
}
