import java.util.Stack;

class Solution {
    public int mctFromLeafValues(int[] arr) {
        int res = 0;
        Stack<Integer> stack = new Stack<>();
        stack.push(Integer.MAX_VALUE);
        
        for (int num : arr) {
            while (stack.peek() <= num) {
                int mid = stack.pop();
                res += mid * Math.min(stack.peek(), num);
            }
            stack.push(num);
        }
        
        while (stack.size() > 2) {
            int mid = stack.pop();
            res += mid * stack.peek();
        }
        
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] arr1 = {6,2,4};
        System.out.println("Test Case 1: " + sol.mctFromLeafValues(arr1)); // 32
        int[] arr2 = {4,11};
        System.out.println("Test Case 2: " + sol.mctFromLeafValues(arr2)); // 44
    }
}
