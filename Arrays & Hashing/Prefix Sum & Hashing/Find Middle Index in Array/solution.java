class Solution {
    public int findMiddleIndex(int[] nums) {
        int totalSum = 0;
        for (int n : nums) totalSum += n;
        
        int leftSum = 0;
        for (int i = 0; i < nums.length; i++) {
            int rightSum = totalSum - leftSum - nums[i];
            if (leftSum == rightSum) return i;
            leftSum += nums[i];
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {2, 3, -1, 8, 4};
        System.out.println(sol.findMiddleIndex(nums));
    }
}
