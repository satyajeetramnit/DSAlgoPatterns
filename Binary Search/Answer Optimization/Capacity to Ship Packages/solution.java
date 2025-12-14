class Solution {
    public int shipWithinDays(int[] weights, int days) {
        int maxWeight = 0, totalWeight = 0;
        for (int w : weights) {
            maxWeight = Math.max(maxWeight, w);
            totalWeight += w;
        }

        int left = maxWeight, right = totalWeight;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canShip(weights, days, mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

    private boolean canShip(int[] weights, int days, int capacity) {
        int daysNeeded = 1;
        int currentLoad = 0;
        
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                daysNeeded++;
                currentLoad = 0;
            }
            currentLoad += w;
        }
        return daysNeeded <= days;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] weights1 = {1,2,3,4,5,6,7,8,9,10};
        int days1 = 5;
        System.out.println("Min Capacity 1: " + sol.shipWithinDays(weights1, days1)); // Expected: 15

        int[] weights2 = {3,2,2,4,1,4};
        int days2 = 3;
        System.out.println("Min Capacity 2: " + sol.shipWithinDays(weights2, days2)); // Expected: 6
    }
}
