class Solution {
    public int maxSubArray(int[] nums) {
        int maxSum = nums[0], currentSum = 0;
        int start = 0, end = 0, tempStart = 0;
        
        for (int i = 0; i < nums.length; i++) {
            currentSum += nums[i];
            
            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;
                end = i;
            }
            
            if (currentSum < 0) {
                currentSum = 0;
                tempStart = i + 1;
            }
        }
        System.out.println("Subarray: " + java.util.Arrays.toString(java.util.Arrays.copyOfRange(nums, start, end + 1)));
        return maxSum;
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {-2,1,-3,4,-1,2,1,-5,4};
        System.out.println("Maximum Subarray Sum: " + sol.maxSubArray(nums));
    }
}