class Solution {
    public int jump(int[] nums) {
        if (nums.length <= 1) return 0;
        
        int jumps = 0;
        int currentEnd = 0;
        int farthest = 0;
        
        for (int i = 0; i < nums.length - 1; i++) {
            farthest = Math.max(farthest, i + nums[i]);
            
            if (i == currentEnd) {
                jumps++;
                currentEnd = farthest;
                
                if (currentEnd >= nums.length - 1) break;
            }
        }
        return jumps;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1: " + sol.jump(new int[]{2,3,1,1,4})); // Expect 2
        System.out.println("Test Case 2: " + sol.jump(new int[]{2,3,0,1,4})); // Expect 2
    }
}
