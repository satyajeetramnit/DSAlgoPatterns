class Solution {
    // treat n as an unsigned value
    public int reverseBits(int n) {
        int res = 0;
        for (int i = 0; i < 32; i++) {
            if (((n >> i) & 1) == 1) {
                res |= (1 << (31 - i));
            }
        }
        return res;
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        
        int n1 = 43261596;
        // Java prints signed integer by default, let's use Integer.toUnsignedString or just print the raw int value
        // 964176192 fits in positive signed int
        System.out.println("Test Case 1: " + sol.reverseBits(n1));
        
        int n2 = -3; // 1111...1101
        // Reverse should be 101111...1111 which is huge positive unsigned, but negative signed
        // 3221225471 is BFFFFFF in hex.
        // In signed int: -1073741825
        System.out.println("Test Case 2 (Unsigned): " + Integer.toUnsignedString(sol.reverseBits(n2)));
    }
}
