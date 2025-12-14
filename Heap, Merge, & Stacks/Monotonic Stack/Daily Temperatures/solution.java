import java.util.Stack;
import java.util.Arrays;

class Solution {
    public int[] dailyTemperatures(int[] temperatures) {
        int n = temperatures.length;
        int[] answer = new int[n];
        Stack<Integer> stack = new Stack<>(); // stores indices
        
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[i] > temperatures[stack.peek()]) {
                int prevIndex = stack.pop();
                answer[prevIndex] = i - prevIndex;
            }
            stack.push(i);
        }
        
        return answer;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] temps = {73,74,75,71,69,72,76,73};
        System.out.println("Test Case 1: " + Arrays.toString(sol.dailyTemperatures(temps))); // Expect [1, 1, 4, 2, 1, 1, 0, 0]
    }
}
