class Solution {
    public int getSum(int a, int b) {
        while (b != 0) {
            int carry = (a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        return a;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1 (1 + 2): " + sol.getSum(1, 2)); // 3
        System.out.println("Test Case 2 (-2 + 3): " + sol.getSum(-2, 3)); // 1
    }
}
