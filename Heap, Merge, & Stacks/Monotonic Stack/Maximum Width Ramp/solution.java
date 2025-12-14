import java.util.Stack;

class Solution {
    public int maxWidthRamp(int[] nums) {
        int n = nums.length;
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < n; i++) {
            if (stack.isEmpty() || nums[stack.peek()] > nums[i]) {
                stack.push(i);
            }
        }
        
        int maxWidth = 0;
        for (int j = n - 1; j >= 0; j--) {
            while (!stack.isEmpty() && nums[stack.peek()] <= nums[j]) {
                maxWidth = Math.max(maxWidth, j - stack.pop());
            }
        }
        
        return maxWidth;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {6,0,8,2,1,5};
        System.out.println("Test Case 1: " + sol.maxWidthRamp(nums)); // Expect 4
    }
}
