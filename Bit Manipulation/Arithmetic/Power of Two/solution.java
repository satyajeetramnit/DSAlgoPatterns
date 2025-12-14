class Solution {
    public boolean isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1 (1): " + sol.isPowerOfTwo(1)); // true
        System.out.println("Test Case 2 (16): " + sol.isPowerOfTwo(16)); // true
        System.out.println("Test Case 3 (3): " + sol.isPowerOfTwo(3)); // false
    }
}
