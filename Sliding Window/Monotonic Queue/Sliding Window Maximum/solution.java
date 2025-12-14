import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Deque;

class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        if (nums == null || k <= 0) {
            return new int[0];
        }
        int[] res = new int[nums.length - k + 1];
        int ri = 0;
        Deque<Integer> dq = new ArrayDeque<>();
        
        for (int i = 0; i < nums.length; i++) {
            if (!dq.isEmpty() && dq.peekFirst() == i - k) {
                dq.pollFirst();
            }
            while (!dq.isEmpty() && nums[dq.peekLast()] < nums[i]) {
                dq.pollLast();
            }
            dq.offerLast(i);
            
            if (i >= k - 1) {
                res[ri++] = nums[dq.peekFirst()];
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {1,3,-1,-3,5,3,6,7};
        int k1 = 3;
        int[] res1 = sol.maxSlidingWindow(nums1, k1);
        System.out.println("Max Window 1: " + Arrays.toString(res1)); // Expected: [3, 3, 5, 5, 6, 7]

        int[] nums2 = {1};
        int k2 = 1;
        int[] res2 = sol.maxSlidingWindow(nums2, k2);
        System.out.println("Max Window 2: " + Arrays.toString(res2)); // Expected: [1]
    }
}
