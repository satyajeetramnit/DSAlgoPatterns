class Solution {
    public int robLinear(int[] nums, int start, int end) {
        int prev2 = 0, prev1 = 0;
        for (int i = start; i <= end; i++) {
            int current = Math.max(prev1, prev2 + nums[i]);
            prev2 = prev1;
            prev1 = current;
        }
        return prev1;
    }

    public int rob1(int[] nums) {
        if (nums.length == 0) return 0;
        return robLinear(nums, 0, nums.length - 1);
    }

    public int rob2(int[] nums) {
        int n = nums.length;
        if (n == 0) return 0;
        if (n == 1) return nums[0];
        return Math.max(robLinear(nums, 0, n - 2), robLinear(nums, 1, n - 1));
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {1, 2, 3, 1};
        System.out.println("Robber I - Test 1: " + sol.rob1(nums1)); // 4
        int[] nums2 = {2, 7, 9, 3, 1};
        System.out.println("Robber I - Test 2: " + sol.rob1(nums2)); // 12
        
        int[] nums3 = {2, 3, 2};
        System.out.println("Robber II - Test 3: " + sol.rob2(nums3)); // 3
        int[] nums4 = {1, 2, 3, 1};
        System.out.println("Robber II - Test 4: " + sol.rob2(nums4)); // 4
    }
}
