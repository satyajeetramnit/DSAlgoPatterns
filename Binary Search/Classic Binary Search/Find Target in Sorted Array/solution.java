class Solution {
    public int search(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {-1, 0, 3, 5, 9, 12};
        System.out.println("Index of 9: " + sol.search(nums, 9)); // Expected: 4
        System.out.println("Index of 2: " + sol.search(nums, 2)); // Expected: -1
    }
}
