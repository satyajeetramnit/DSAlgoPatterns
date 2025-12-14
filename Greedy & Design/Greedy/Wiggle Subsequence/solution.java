class Solution {
    public int wiggleMaxLength(int[] nums) {
        if (nums.length == 0) return 0;
        
        int up = 1;
        int down = 1;
        
        for (int i = 1; i < nums.length; i++) {
            if (nums[i] > nums[i-1]) {
                up = down + 1;
            } else if (nums[i] < nums[i-1]) {
                down = up + 1;
            }
        }
        return Math.max(up, down);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1: " + sol.wiggleMaxLength(new int[]{1,7,4,9,2,5})); // Expect 6
        System.out.println("Test Case 2: " + sol.wiggleMaxLength(new int[]{1,17,5,10,13,15,10,5,16,8})); // Expect 7
        System.out.println("Test Case 3: " + sol.wiggleMaxLength(new int[]{1,2,3,4,5,6,7,8,9})); // Expect 2
    }
}
