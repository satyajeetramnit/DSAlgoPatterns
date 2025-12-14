import java.util.Stack;
import java.util.Arrays;

class Solution {
    public int[] nextGreaterElements(int[] nums) {
        int n = nums.length;
        int[] res = new int[n];
        Arrays.fill(res, -1);
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < 2 * n; i++) {
            int idx = i % n;
            while (!stack.isEmpty() && nums[idx] > nums[stack.peek()]) {
                res[stack.pop()] = nums[idx];
            }
            if (i < n) stack.push(idx);
        }
        
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1, 2, 1};
        System.out.println("Test Case 1: " + Arrays.toString(sol.nextGreaterElements(nums))); // Expect [2, -1, 2]
    }
}
