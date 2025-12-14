class Solution {
    public int findDuplicate(int[] nums) {
        int slow = 0;
        int fast = 0;
        
        while (true) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if (slow == fast) break;
        }
        
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
    
    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1, 3, 4, 2, 2};
        System.out.println("Duplicate: " + sol.findDuplicate(nums));
    }
}
