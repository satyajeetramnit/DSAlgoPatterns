class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int left = 1;
        int right = 0;
        for (int p : piles) right = Math.max(right, p);
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long hours = 0;
            for (int p : piles) {
                // (p + mid - 1) / mid calculates ceil(p / mid)
                hours += (p + mid - 1) / mid;
            }
            
            if (hours <= h) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] piles1 = {3,6,7,11};
        int h1 = 8;
        System.out.println("Min Speed 1: " + sol.minEatingSpeed(piles1, h1)); // Expected: 4

        int[] piles2 = {30,11,23,4,20};
        int h2 = 5;
        System.out.println("Min Speed 2: " + sol.minEatingSpeed(piles2, h2)); // Expected: 30
    }
}
