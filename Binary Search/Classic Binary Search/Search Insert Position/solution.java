class Solution {
    public int searchInsert(int[] nums, int target) {
        int left = 0, right = nums.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return mid;
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return left;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] nums = {1, 3, 5, 6};
        System.out.println("Insert 5: " + sol.searchInsert(nums, 5)); // Expected: 2
        System.out.println("Insert 2: " + sol.searchInsert(nums, 2)); // Expected: 1
        System.out.println("Insert 7: " + sol.searchInsert(nums, 7)); // Expected: 4
    }
}
