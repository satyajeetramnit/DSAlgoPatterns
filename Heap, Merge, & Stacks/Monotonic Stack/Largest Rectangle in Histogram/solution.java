import java.util.Stack;

class Solution {
    public int largestRectangleArea(int[] heights) {
        int n = heights.length;
        int maxArea = 0;
        Stack<Integer> stack = new Stack<>();
        
        // We iterate up to n, where i == n is treated as height 0
        for (int i = 0; i <= n; i++) {
            int h = (i == n) ? 0 : heights[i];
            
            while (!stack.isEmpty() && h < heights[stack.peek()]) {
                int height = heights[stack.pop()];
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }
        
        return maxArea;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] heights = {2, 1, 5, 6, 2, 3};
        System.out.println("Test Case 1: " + sol.largestRectangleArea(heights)); // Expect 10
    }
}
