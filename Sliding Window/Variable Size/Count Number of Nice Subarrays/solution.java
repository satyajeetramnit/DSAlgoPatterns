class Solution {
    public int numberOfSubarrays(int[] nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

    private int atMost(int[] nums, int k) {
        int left = 0, res = 0, count = 0;
        for (int right = 0; right < nums.length; right++) {
            if (nums[right] % 2 != 0) {
                count++;
            }
            while (count > k) {
                if (nums[left] % 2 != 0) {
                    count--;
                }
                left++;
            }
            res += right - left + 1;
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums1 = {1,1,2,1,1};
        int k1 = 3;
        System.out.println("Count 1: " + sol.numberOfSubarrays(nums1, k1)); // Expected: 2

        int[] nums2 = {2,4,6};
        int k2 = 1;
        System.out.println("Count 2: " + sol.numberOfSubarrays(nums2, k2)); // Expected: 0
    }
}
