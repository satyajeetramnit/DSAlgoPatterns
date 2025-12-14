import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

class Solution {
    public int lengthOfLIS(int[] nums) {
        if (nums.length == 0) return 0;
        
        List<Integer> tails = new ArrayList<>();
        
        for (int num : nums) {
            int idx = Collections.binarySearch(tails, num);
            if (idx < 0) idx = -(idx + 1); 
            
            if (idx == tails.size()) {
                tails.add(num);
            } else {
                tails.set(idx, num);
            }
        }
        
        return tails.size();
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int[] nums1 = {10,9,2,5,3,7,101,18};
        System.out.println("Test Case 1: " + sol.lengthOfLIS(nums1)); // 4
        
        int[] nums2 = {0,1,0,3,2,3};
        System.out.println("Test Case 2: " + sol.lengthOfLIS(nums2)); // 4
        
        int[] nums3 = {7,7,7,7,7,7,7};
        System.out.println("Test Case 3: " + sol.lengthOfLIS(nums3)); // 1
    }
}
