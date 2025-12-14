class Solution {
    public int minSubArrayLen(int target, int[] nums) {
        int left = 0;
        int currentSum = 0;
        int minLen = Integer.MAX_VALUE;
        
        for (int right = 0; right < nums.length; right++) {
            currentSum += nums[right];
            
            while (currentSum >= target) {
                minLen = Math.min(minLen, right - left + 1);
                currentSum -= nums[left];
                left++;
            }
        }
        
        return (minLen == Integer.MAX_VALUE) ? 0 : minLen;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int target1 = 7;
        int[] nums1 = {2,3,1,2,4,3};
        System.out.println("Min Length 1: " + sol.minSubArrayLen(target1, nums1)); // Expected: 2

        int target2 = 4;
        int[] nums2 = {1,4,4};
        System.out.println("Min Length 2: " + sol.minSubArrayLen(target2, nums2)); // Expected: 1
        
        int target3 = 11;
        int[] nums3 = {1,1,1,1,1,1,1,1};
        System.out.println("Min Length 3: " + sol.minSubArrayLen(target3, nums3)); // Expected: 0
    }
}
