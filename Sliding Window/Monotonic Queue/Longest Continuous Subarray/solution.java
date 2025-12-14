import java.util.ArrayDeque;
import java.util.Deque;

class Solution {
    public int longestSubarray(int[] nums, int limit) {
        Deque<Integer> maxD = new ArrayDeque<>();
        Deque<Integer> minD = new ArrayDeque<>();
        int left = 0;
        int res = 0;
        
        for (int right = 0; right < nums.length; right++) {
            while (!maxD.isEmpty() && nums[maxD.peekLast()] <= nums[right]) {
                maxD.pollLast();
            }
            while (!minD.isEmpty() && nums[minD.peekLast()] >= nums[right]) {
                minD.pollLast();
            }
            
            maxD.offerLast(right);
            minD.offerLast(right);
            
            while (nums[maxD.peekFirst()] - nums[minD.peekFirst()] > limit) {
                left++;
                if (maxD.peekFirst() < left) maxD.pollFirst();
                if (minD.peekFirst() < left) minD.pollFirst();
            }
            
            res = Math.max(res, right - left + 1);
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {8,2,4,7};
        int limit1 = 4;
        System.out.println("Longest 1: " + sol.longestSubarray(nums1, limit1)); // Expected: 2

        int[] nums2 = {10,1,2,4,7,2};
        int limit2 = 5;
        System.out.println("Longest 2: " + sol.longestSubarray(nums2, limit2)); // Expected: 4
    }
}
