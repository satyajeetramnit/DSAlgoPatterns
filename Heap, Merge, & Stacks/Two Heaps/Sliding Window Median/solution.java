import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Arrays;

class Solution {
    PriorityQueue<Integer> left;
    PriorityQueue<Integer> right;

    public Solution() {
        left = new PriorityQueue<>(Collections.reverseOrder());
        right = new PriorityQueue<>();
    }

    public double[] medianSlidingWindow(int[] nums, int k) {
        int n = nums.length;
        double[] result = new double[n - k + 1];

        for (int i = 0; i < k; i++) add(nums[i]);
        result[0] = getMedian();

        for (int i = k; i < n; i++) {
            remove(nums[i - k]);
            add(nums[i]);
            result[i - k + 1] = getMedian();
        }

        return result;
    }

    private void add(int num) {
        if (left.isEmpty() || num <= left.peek()) {
            left.add(num);
        } else {
            right.add(num);
        }
        rebalance();
    }

    private void remove(int num) {
        if (num <= left.peek()) left.remove(num); 
        else right.remove(num);
        rebalance();
    }

    private void rebalance() {
        if (left.size() < right.size()) left.add(right.poll());
        if (left.size() > right.size() + 1) right.add(left.poll());
    }

    private double getMedian() {
        if (left.size() == right.size()) return ((double)left.peek() + right.peek()) / 2.0;
        return (double)left.peek();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1,3,-1,-3,5,3,6,7};
        int k = 3;
        System.out.println("Test Case 1: " + Arrays.toString(sol.medianSlidingWindow(nums, k))); // Expect [1.0, -1.0, -1.0, 3.0, 5.0, 6.0]
    }
}
