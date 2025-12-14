class Solution {
    public int maxProduct(int[] nums) {
        int res = nums[0];
        int curMin = 1, curMax = 1;
        
        for (int n : nums) {
            int tmp = curMax * n;
            curMax = Math.max(Math.max(n * curMax, n * curMin), n);
            curMin = Math.min(Math.min(tmp, n * curMin), n);
            res = Math.max(res, curMax);
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {2, 3, -2, 4};
        System.out.println(sol.maxProduct(nums));
    }
}
