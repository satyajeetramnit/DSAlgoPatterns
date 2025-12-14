class Solution {
    public int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public long lcm(int a, int b) {
        if (a == 0 || b == 0) return 0;
        return (long) Math.abs(a) / gcd(a, b) * Math.abs(b);
    }

    public static void main(String[] args) {
        Solution sol = new Solution();
        System.out.println("Test Case 1 (12, 18): GCD=" + sol.gcd(12, 18) + ", LCM=" + sol.lcm(12, 18)); // 6, 36
        System.out.println("Test Case 2 (5, 7): GCD=" + sol.gcd(5, 7) + ", LCM=" + sol.lcm(5, 7)); // 1, 35
    }
}
