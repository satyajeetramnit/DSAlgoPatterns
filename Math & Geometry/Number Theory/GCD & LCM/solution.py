class Solution:
    def gcd(self, a: int, b: int) -> int:
        while b:
            a, b = b, a % b
        return a

    def lcm(self, a: int, b: int) -> int:
        if a == 0 or b == 0:
            return 0
        return abs(a * b) // self.gcd(a, b)

if __name__ == "__main__":
    sol = Solution()
    print(f"Test Case 1 (12, 18): GCD={sol.gcd(12, 18)}, LCM={sol.lcm(12, 18)}") # 6, 36
    print(f"Test Case 2 (5, 7): GCD={sol.gcd(5, 7)}, LCM={sol.lcm(5, 7)}") # 1, 35
