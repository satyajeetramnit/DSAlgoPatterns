import java.util.*;

class Solution {
    int[] bit;
    int n;

    private void update(int idx, int val) {
        while (idx <= n) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    private int query(int idx) {
        int sum = 0;
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    public List<Integer> countSmaller(int[] nums) {
        int[] sorted = nums.clone();
        Arrays.sort(sorted);
        
        Map<Integer, Integer> ranks = new HashMap<>();
        int rank = 1;
        for (int num : sorted) {
            if (!ranks.containsKey(num)) {
                ranks.put(num, rank++);
            }
        }
        
        n = ranks.size();
        bit = new int[n + 1];
        List<Integer> res = new ArrayList<>();
        
        for (int i = nums.length - 1; i >= 0; i--) {
            int r = ranks.get(nums[i]);
            res.add(query(r - 1));
            update(r, 1);
        }
        
        Collections.reverse(res);
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        // Test 1
        int[] nums1 = {5, 2, 6, 1};
        List<Integer> expected1 = Arrays.asList(2, 1, 1, 0);
        List<Integer> result1 = sol.countSmaller(nums1);
        assert result1.equals(expected1) : "Test 1 Failed: " + result1;
        System.out.println("Test 1 Passed");
        
        // Test 2
        int[] nums2 = {-1};
        List<Integer> expected2 = Arrays.asList(0);
        List<Integer> result2 = sol.countSmaller(nums2);
        assert result2.equals(expected2) : "Test 2 Failed";
        System.out.println("Test 2 Passed");
    }
}
