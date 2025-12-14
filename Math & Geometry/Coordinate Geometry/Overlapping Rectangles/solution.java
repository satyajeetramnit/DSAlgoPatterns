class Solution {
    public boolean isRectangleOverlap(int[] rec1, int[] rec2) {
        return (Math.max(rec1[0], rec2[0]) < Math.min(rec1[2], rec2[2]) &&
                Math.max(rec1[1], rec2[1]) < Math.min(rec1[3], rec2[3]));
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        int[] r1 = {0,0,2,2};
        int[] r2 = {1,1,3,3};
        System.out.println("Test Case 1 (Overlap): " + sol.isRectangleOverlap(r1, r2)); // true
        
        int[] r3 = {0,0,1,1};
        int[] r4 = {1,0,2,1};
        System.out.println("Test Case 2 (Touch): " + sol.isRectangleOverlap(r3, r4)); // false
    }
}
